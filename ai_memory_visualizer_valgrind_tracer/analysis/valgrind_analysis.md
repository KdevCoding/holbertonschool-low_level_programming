# Valgrind Analysis

Companion to `analysis/memory_maps.md` (Task 1). That document tracks
*what the memory looks like at each point*; this one takes every
Valgrind warning Memcheck actually emitted and explains, precisely,
which memory object it's about and which lifetime rule was broken —
not just "Valgrind said X."

## Invocation

Same four binaries, same build as Task 1 (see that document's Build Note
for why `aliasing_example.c` needed a manual `gcc` invocation instead of
`make`). Every program was run under:

```
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./<binary>
```

Flag rationale:

| Flag | Why it's needed here |
|---|---|
| `--leak-check=full` | Without it Valgrind only prints a leak *summary count*, not the allocation stack trace for each lost block — and "which `malloc` call leaked" is exactly what this task needs answered. |
| `--show-leak-kinds=all` | Default leak-check only reports "definitely lost" + "indirectly lost". `crash_example` has a "still reachable" block that's worth explaining precisely *because* it's easy to misclassify as a leak (see the AI-error section below) — this flag makes Valgrind print it instead of hiding it. |
| `--track-origins=yes` | Needed to trace an uninitialized-value error back to where the value was born, not just where it was misused. None of the four programs triggered this class of error (see per-program notes), but the flag was kept on for all runs since it costs nothing when unused and would have mattered had one existed. |
| `-s` | Prints the full list of individual errors (not just the summary count), needed to attribute each of `aliasing_example`'s 3 errors to its own line. |

Full raw output for each run is included per-program below, trimmed only
of the banner/copyright lines.

---

## Program: `stack_example.c`

```
==474== HEAP SUMMARY:
==474==     in use at exit: 0 bytes in 0 blocks
==474==   total heap usage: 1 allocs, 1 frees, 4,096 bytes allocated
==474==
==474== All heap blocks were freed -- no leaks are possible
==474==
==474== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

**Result: zero warnings.** No leaks, no invalid access, no uninitialized
reads.

**Why:** the program never calls `malloc`/`free` from its own code —
the "1 allocs, 1 frees" is glibc's internal stdio buffer for `printf`,
allocated and freed automatically around process exit, not a program
object. All of the interesting behavior in this file (recursion, pointer
`p_local` aliasing a same-frame local) happens entirely on the **stack**,
and Memcheck's leak/invalid-access checks are heap- and
addressability-focused — a pointer like `p_local` going stale when its
frame pops is a real correctness hazard in general (it's used-after-scope
if dereferenced later), but this program never dereferences it after the
frame returns, so there's nothing for Memcheck to flag. This is a case
where "Valgrind is silent" is itself a data point worth recording, not
an absence of anything to say.

No table needed — there are no warnings to classify.

---

## Program: `heap_example.c`

```
==475== HEAP SUMMARY:
==475==     in use at exit: 6 bytes in 1 blocks
==475==   total heap usage: 5 allocs, 4 frees, 4,138 bytes allocated
==475==
==475== 6 bytes in 1 blocks are definitely lost in loss record 1 of 1
==475==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==475==    by 0x109211: person_new (heap_example.c:21)
==475==    by 0x1092FA: main (heap_example.c:51)
==475==
==475== LEAK SUMMARY:
==475==    definitely lost: 6 bytes in 1 blocks
==475==    indirectly lost: 0 bytes in 0 blocks
==475==      possibly lost: 0 bytes in 0 blocks
==475==    still reachable: 0 bytes in 0 blocks
==475==         suppressed: 0 bytes in 0 blocks
==475==
==475== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

### Classification

| Field | Value |
|---|---|
| **Error type** | Memory leak — **definitely lost** (the strongest leak category: Valgrind found no pointer anywhere in the program, live or dead, that still references this block at exit) |
| **Memory object** | The 6-byte `char*` buffer allocated at `heap_example.c:21` (`p->name = malloc(len + 1)`) during the call `person_new("Alice", 30)` from `main:51` — this is Alice's name string, `"Alice\0"` |
| **Root allocation site** | `heap_example.c:21`, inside `person_new`, called specifically from `main:51` (the `alice = person_new(...)` call — Valgrind's stack trace pins it to *this* call site, not Bob's identical-looking call one line later, because the two calls produce two separate allocations and only Alice's survives unreferenced) |
| **Lifetime violation** | **Leak due to lost ownership.** `p->name` is the only pointer that ever refers to this block. Ownership of that pointer lives inside the `Person` struct at Alloc A (`heap_example.c:12`). When `person_free_partial(alice)` calls `free(p)` (`heap_example.c:34`), it frees the *struct* but never reads or frees `p->name` first — the struct holding the only reference to the name buffer is destroyed while the buffer itself is still live, so the reference is lost the instant the struct is freed. No code path exists afterward that could ever reach this block again; it is unreachable from that point until process exit. |

### Why this specific block and not Bob's

`bob`'s `name` (allocated at the same line, `heap_example.c:21`, from
`main`'s *other* call to `person_new`, at `main:52`/called before line
57) does **not** leak, because `main` frees it directly and explicitly
(`free(bob->name)` at `heap_example.c:57`, *before* `free(bob)` at
`heap_example.c:58` — reading `bob->name` to pass to `free` while the
struct is still alive, then freeing the struct). The only structural
difference between Alice and Bob's cleanup is which function does the
freeing (`person_free_partial` vs. inline code in `main`), and that
difference is exactly why one leaks and the other doesn't — confirming
what memory_maps.md's Task 1 analysis already predicted from reading the
source, now independently confirmed by Valgrind's runtime trace rather
than static reasoning alone.

No invalid reads/writes and no uninitialized-value warnings appeared for
this program — every byte written to `p->name` is written by the
character-copy loop (`heap_example.c:26-27`) before it's ever read, and
every heap pointer used is either freshly allocated or explicitly
checked against `NULL` before use.

---

## Program: `aliasing_example.c`

```
==476== Invalid read of size 4
==476==    at 0x1092F5: main (aliasing_example.c:42)
==476==  Address 0x4a7d088 is 8 bytes inside a block of size 20 free'd
==476==    at 0x484988F: free (in .../vgpreload_memcheck-amd64-linux.so)
==476==    by 0x1092D1: main (aliasing_example.c:38)
==476==  Block was alloc'd at
==476==    at 0x4846828: malloc (in .../vgpreload_memcheck-amd64-linux.so)
==476==    by 0x1091E4: make_numbers (aliasing_example.c:12)
==476==    by 0x109272: main (aliasing_example.c:30)
==476==
==476== Invalid write of size 4
==476==    at 0x109315: main (aliasing_example.c:44)
==476==  Address 0x4a7d08c is 12 bytes inside a block of size 20 free'd
==476==    at 0x484988F: free (...)
==476==    by 0x1092D1: main (aliasing_example.c:38)
==476==  Block was alloc'd at ... make_numbers (aliasing_example.c:12) / main (aliasing_example.c:30)
==476==
==476== Invalid read of size 4
==476==    at 0x109323: main (aliasing_example.c:45)
==476==  Address 0x4a7d08c is 12 bytes inside a block of size 20 free'd
==476==    at 0x484988F: free (...)
==476==    by 0x1092D1: main (aliasing_example.c:38)
==476==  Block was alloc'd at ... make_numbers (aliasing_example.c:12) / main (aliasing_example.c:30)
==476==
==476== HEAP SUMMARY:
==476==     in use at exit: 0 bytes in 0 blocks
==476==   total heap usage: 2 allocs, 2 frees, 4,116 bytes allocated
==476==
==476== All heap blocks were freed -- no leaks are possible
==476==
==476== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
```

### Classification

All three errors refer to the **same 20-byte block** (`int[5]`),
allocated once at `aliasing_example.c:12` (inside `make_numbers`, called
from `main:30`) and freed once at `aliasing_example.c:38` (`free(a)`).
There is no leak — `total heap usage: 2 allocs, 2 frees` and "All heap
blocks were freed" confirm the one block was allocated once and freed
exactly once. What's wrong is everything that happens to it *afterward*.

| # | Error type | Location | Memory object / offset | Lifetime violation |
|---|---|---|---|---|
| 1 | **Invalid read of size 4** (use-after-free read) | `aliasing_example.c:42` — `printf("  reading b[2]=%d\n", b[2]);` | Byte offset 8 into the 20-byte block → `8 / sizeof(int) = index 2` → this is `b[2]` | `b` is an alias of `a` (`b = a` at line 30); the block was freed via `a` at line 38. `b` was never re-pointed, so reading through it after the free reads memory whose lifetime has already ended. |
| 2 | **Invalid write of size 4** (use-after-free write) | `aliasing_example.c:44` — `b[3] = 1234;` | Byte offset 12 → `12 / 4 = index 3` → `b[3]` | Same freed block, same stale alias `b`. Writing to freed memory is worse than reading it: it can corrupt whatever the allocator has since done with that memory (e.g. free-list bookkeeping, or a different live allocation if the block had already been reused). |
| 3 | **Invalid read of size 4** (use-after-free read) | `aliasing_example.c:45` — `printf("  wrote b[3]=%d\n", b[3]);` | Byte offset 12 → index 3 → `b[3]` | Reads back the value just written in error #2 — this read is only "consistent" with what was written because nothing else has touched that byte range yet; it's still operating on a dead object, not proof the write was safe. |

### Root cause (shared across all three)

**Use-after-free via aliasing.** `a` and `b` are two names for the exact
same pointer *value* from the moment `b = a` executes — Valgrind's own
"Block was alloc'd at ... by main (aliasing_example.c:30)" trace shows
both errors resolving back to the identical allocation, confirming there
is only one block in play, referenced by two variables. `free(a)`
deallocates the block; it does not and cannot know that `b` also holds
that address. From that point, `b` is a dangling pointer, and every
subsequent access through it is undefined behavior — Memcheck catches it
because it shadow-tracks each byte's allocation state independently of
which *variable name* is used to reach it.

No leak-related warnings apply to this program at all; conflating "3
invalid-access errors" with "3 leaks" would be a category error (see the
AI-error case below, which is exactly this mistake).

---

## Program: `crash_example.c`

```
==477== Invalid write of size 4
==477==    at 0x10928A: main (crash_example.c:32)
==477==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==477==
==477== Process terminating with default action of signal 11 (SIGSEGV)
==477==  Access not within mapped region at address 0x0
==477==    at 0x10928A: main (crash_example.c:32)
==477==
==477== HEAP SUMMARY:
==477==     in use at exit: 4,096 bytes in 1 blocks
==477==   total heap usage: 1 allocs, 0 frees, 4,096 bytes allocated
==477==
==477== 4,096 bytes in 1 blocks are still reachable in loss record 1 of 1
==477==    at 0x4846828: malloc (in .../vgpreload_memcheck-amd64-linux.so)
==477==    by 0x48EC294: _IO_file_doallocate (filedoalloc.c:101)
==477==    by 0x48FC603: _IO_doallocbuf (genops.c:347)
==477==    by 0x48FA06F: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:745)
==477==    by 0x48FAB8E: _IO_new_file_xsputn (fileops.c:1244)
==477==    by 0x48EED3C: puts (ioputs.c:40)
==477==    by 0x10925E: main (crash_example.c:27)
==477==
==477== LEAK SUMMARY:
==477==    definitely lost: 0 bytes in 0 blocks
==477==    indirectly lost: 0 bytes in 0 blocks
==477==      possibly lost: 0 bytes in 0 blocks
==477==    still reachable: 4,096 bytes in 1 blocks
==477==         suppressed: 0 bytes in 0 blocks
==477==
==477== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

### Classification

| # | Error type | Location | Memory object | Lifetime violation |
|---|---|---|---|---|
| 1 | **Invalid write of size 4 → SIGSEGV** (NULL-pointer dereference, not use-after-free) | `crash_example.c:32` — `nums[0] = 42;` | Address `0x0` — the value of `nums`, which was assigned `NULL` by `allocate_numbers(0)`'s early-return path (`crash_example.c:9-10`) | This is **not** a lifetime violation on a heap object at all — Valgrind's own message is explicit: `"Address 0x0 is not stack'd, malloc'd or (recently) free'd"`, i.e. this address was *never part of any object's lifetime* to begin with. The bug is a missing NULL-check on a return value, not memory whose lifetime ended. |
| 2 | **"Still reachable" block, 4,096 bytes** | Allocated inside glibc's `puts` → `_IO_file_xsputn` → `_IO_file_overflow` → `_IO_doallocbuf` → `_IO_file_doallocate` call chain, triggered by the call at `crash_example.c:27` (`printf("  requesting n=%d\n", n)`, which gcc compiles to a plain `puts` since the format string has no substitutions) | glibc's internal `stdout` buffer | **Not a leak.** "Still reachable" is Valgrind's weakest/most benign leak category — it means a pointer chain *does* still exist to this block (glibc's own internal `FILE*` structure for `stdout` still references it) at the moment the process was killed by the signal; it simply never got the chance to `fflush`/`free` it because `main` never returned normally. This is standard, expected behavior for any C program killed by a signal mid-execution, not a defect in this program's logic. |

### Root cause

The real bug: `allocate_numbers(0)` correctly implements a guard clause
(`if (n <= 0) return NULL;`) and returns before ever reaching its
`malloc` call — confirmed by the heap summary showing only 1 allocation
total, and that allocation's stack trace leads to `puts`/stdio, not to
`allocate_numbers`. `main` then dereferences that `NULL` return value
without checking it, at `crash_example.c:32`. Because address `0x0` is
never mapped into the process's address space, the CPU itself raises a
protection fault on the write attempt — the OS delivers `SIGSEGV`, and
the process is killed before it can reach `free(nums)`, `return 0`, or
flush any remaining buffered output. There is no allocation to leak and
no freed object being reused; this is purely a missing-NULL-check bug.

---

## AI Explanation Errors (required per task instructions)

Two genuine misinterpretations were caught during review of an AI-drafted
first pass over this same Valgrind output, before cross-checking against
the code and the Task 1 memory maps:

### Error 1 — miscomputing an array index from a byte offset

**AI draft claim (on `aliasing_example`'s first error):**
> "Valgrind's message `Address 0x4a7d088 is 8 bytes inside a block of
> size 20 free'd` means the invalid read at line 42 is accessing array
> index 8 of the freed block."

**Why this is wrong:** the "8 bytes inside" figure is a **byte offset**,
not an element index. The block holds `int` elements (4 bytes each), so
converting requires dividing by the element size: `8 / sizeof(int) = 2`.
Index 8 wouldn't even fit — the block is only 20 bytes (5 ints, valid
indices 0–4); "index 8" would be reading 12 bytes past the end of even
the original allocation, which is a different bug (heap buffer overrun)
than the one actually present. Cross-checking against the source
confirms the correct reading: line 42 is literally `b[2]`, matching the
correctly-computed index 2, not 8.

**How this was caught:** by reading the source line Valgrind's own stack
trace points to (`aliasing_example.c:42`) instead of trusting the AI's
arithmetic — the source line and the corrected offset math agree with
each other (`b[2]` ↔ offset 8 ↔ index 2), while the AI's claim
(index 8) agrees with neither.

### Error 2 — conflating "still reachable" with "leaked"

**AI draft claim (on `crash_example`'s heap summary):**
> "Valgrind reports a memory leak of 4,096 bytes in `crash_example`,
> caused by the program crashing before it could call `free()`."

**Why this is wrong:** Valgrind's `LEAK SUMMARY` explicitly separates
this block into the **"still reachable"** category (`4,096 bytes in 1
blocks`) and reports **`definitely lost: 0 bytes`**. These are different
severities with different meanings: "definitely lost" means no pointer
to the block exists anywhere — genuinely unreachable memory, a real
leak. "Still reachable" means a pointer chain to the block still exists
at exit (here, glibc's own internal `FILE*` for `stdout` still points to
its buffer) — Valgrind reports it only because `--show-leak-kinds=all`
was passed, and by default many teams don't even treat "still reachable"
as an actionable finding, since it commonly comes from libc/runtime
internals rather than program logic. It is also not caused by "the
program crashing before calling `free()`" in the sense of a
program-logic bug — this block was never allocated by *this program's*
code at all (the allocation stack trace is entirely inside
glibc's `puts`/stdio internals, not inside `main` or
`allocate_numbers`), so there was never a `free()` call for this program
to have skipped.

**How this was caught:** by reading the full stack trace Valgrind
attaches to the "still reachable" entry (which points into
`_IO_file_doallocate`/`_IO_doallocbuf`, i.e., glibc internals) rather
than assuming every nonzero "in use at exit" number is a leak — and by
checking it against the "LEAK SUMMARY" block's own categorization, which
Valgrind prints specifically to prevent this kind of conflation.

---

## Cross-Program Summary

| Program | Errors | Leaks | Type of primary issue |
|---|---|---|---|
| `stack_example.c` | 0 | 0 | — (stack-only program, nothing for Memcheck to flag) |
| `heap_example.c` | 1 | 1 (6 B, definitely lost) | Leak due to lost ownership — struct freed before its owned string pointer was freed |
| `aliasing_example.c` | 3 | 0 | Use-after-free via aliasing (2 reads, 1 write, all on one block, all through a stale alias) |
| `crash_example.c` | 1 (+ 1 benign "still reachable" note) | 0 | NULL-pointer dereference — not a lifetime violation, since the accessed address was never part of any object's lifetime |

No program in this set triggered a genuine "use of uninitialized value"
warning under `--track-origins=yes` — every local and heap value that's
read is written before that read in all four programs' actual code
paths. This is stated explicitly rather than omitted, since the task
asked to capture that category if present, and its absence here is
itself a verified fact (confirmed by `--track-origins=yes` producing no
such warnings across all four runs), not an oversight.
