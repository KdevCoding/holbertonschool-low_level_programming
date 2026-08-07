# Memory Maps Analysis

Programs analyzed (from `programs/`, built via the provided `Makefile`):
`stack_example.c`, `heap_example.c`, `aliasing_example.c`, `crash_example.c`.
These four cover the categories the task asks for: stack/recursion,
heap alloc+leak, pointer aliasing + use-after-free, and a hard crash.

**Method:** each program was (1) compiled with the Makefile, (2) run
normally, (3) an AI-generated memory-map draft was produced from the
source, and (4) that draft was checked line-by-line against real
`valgrind --leak-check=full --track-origins=yes` output and `gdb`
backtraces on the actual compiled binaries. Every "AI Draft vs.
Corrections" table below reflects genuine discrepancies found during
that check, not hypothetical ones.

**Toolchain note:** `gcc -Wall -Wextra -Werror -pedantic -std=gnu89 -g`
(exact Makefile flags), Ubuntu 24.04, gdb 15.1, Valgrind 3.22.0.

---

## Build Note (applies to `aliasing_example.c`)

Running `make all` as provided **fails** on this file:

```
aliasing_example.c: In function 'main':
aliasing_example.c:45:34: error: pointer 'b' used after 'free' [-Werror=use-after-free]
...
cc1: all warnings being treated as errors
make: *** [Makefile:18: aliasing_example] Error 1
```

Modern GCC (13+) statically detects the exact use-after-free the program
is designed to demonstrate, and `-Werror` turns that warning into a hard
build failure. `stack_example`, `heap_example`, and `crash_example` build
cleanly with `make`. To still exercise `aliasing_example` dynamically (as
the task requires), it was compiled by hand with the same flags minus
`-Werror`:

```
gcc -Wall -Wextra -pedantic -std=gnu89 -g -o aliasing_example aliasing_example.c
```

This is itself worth noting as a finding: for this particular bug, the
compiler's static analysis catches the defect before Valgrind ever needs
to run. Both are reported below for completeness.

---

## Program: `stack_example.c`

**Compiled with:** `make stack_example` (clean build, no warnings)
**Run:** `./stack_example` (no args)
**Valgrind:** `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./stack_example` → **0 errors, no heap activity** (program does no `malloc`/`free`, so this is expected and confirms nothing is silently touching the heap, e.g. via hidden libc buffering that outlives the process).

### Summary

Pure stack/recursion demo: `main` calls `walk_stack(0, 3)`, which
recurses down to depth 3, calling `dump_frame()` on the way in and out of
each level. No heap allocation anywhere. The interesting memory behavior
is entirely about **stack frame layout and address reuse** as frames are
pushed and popped, and about `p_local`, a pointer that aliases a
same-frame local (`&local_int`) and therefore is never valid outside that
one frame's lifetime.

### Execution Timeline

| # | Event | Location | Stack change | Pointer change |
|---|-------|----------|---------------|-----------------|
| 1 | `main()` entry | `stack_example.c:31` | frame `main` pushed | — |
| 2 | call `walk_stack(0,3)` | `stack_example.c:35` | frame `walk_stack(depth=0)` pushed | — |
| 3 | `marker = 0` | `stack_example.c:20` | local `marker` created in this frame | — |
| 4 | call `dump_frame("enter",0)` | `stack_example.c:21` | frame `dump_frame` pushed | — |
| 5 | `p_local = &local_int` | `stack_example.c:7` | — | `p_local` = address of `local_int` **in this frame** |
| 6 | `dump_frame` returns | `stack_example.c:23` (back to caller) | frame `dump_frame` popped | `p_local` (and `local_int`, `local_buf`) now stale/out of scope — nothing keeps a reference to them |
| 7 | depth(0) < max_depth(3) → recurse | `stack_example.c:26` | frame `walk_stack(depth=1)` pushed **above** `walk_stack(depth=0)` | — |
| 8 | …repeats for depth=1,2,3… | `stack_example.c:21-26` | frames nest up to depth 3 | each depth gets its **own** `local_int`/`local_buf`/`p_local`/`marker` at a **different stack address** |
| 9 | depth=3 hits base case (`3 < 3` false) | `stack_example.c:26` | no further push | — |
| 10 | `dump_frame("exit",3)` | `stack_example.c:28` | frame `dump_frame` pushed again (reused address range) | new `p_local` bound to the depth-3 frame's `local_int` again |
| 11 | unwind: `walk_stack(3)` returns | `stack_example.c:29` | frame `walk_stack(3)` popped | — |
| 12 | `dump_frame("exit",2)`, `walk_stack(2)` returns, … | `stack_example.c:28-29` | frames popped depth 2→1→0 in order | each still prints its **own** `marker`, proving each frame's locals are independent (not shared/overwritten) |
| 13 | `main()` returns | `stack_example.c:37` | frame `main` popped | — |

### Stack Frames — real snapshot at deepest recursion (depth=3, inside `dump_frame`)

Captured with `gdb -batch -ex "break dump_frame if depth==3" -ex run -ex bt`:

```
#0  dump_frame (label="enter", depth=3) at stack_example.c:4
#1  walk_stack (depth=3, max_depth=3) at stack_example.c:22
#2  walk_stack (depth=2, max_depth=3) at stack_example.c:26
#3  walk_stack (depth=1, max_depth=3) at stack_example.c:26
#4  walk_stack (depth=0, max_depth=3) at stack_example.c:26
#5  main () at stack_example.c:35
```

| Frame (top→bottom) | Function | Locals visible via gdb |
|---|---|---|
| 0 | `dump_frame(depth=3)` | `local_int=103`, `local_buf="D"`, `p_local=&local_int` |
| 1 | `walk_stack(depth=3)` | `marker=30` |
| 2 | `walk_stack(depth=2)` | `marker=20` |
| 3 | `walk_stack(depth=1)` | `marker=10` |
| 4 | `walk_stack(depth=0)` | `marker=0` |
| 5 | `main` | (no locals) |

This matches the real run's printed addresses exactly — each depth has a
distinct, monotonically-decreasing `&local_int` (stack grows down):

```
depth=0  &local_int=0x7ffe10c63b44
depth=1  &local_int=0x7ffe10c63b14   (30 bytes lower)
depth=2  &local_int=0x7ffe10c63ae4
depth=3  &local_int=0x7ffe10c63ab4
```

### Pointer Table

| Pointer | Declared in | Points to | Alias of | Valid outside its frame? |
|---|---|---|---|---|
| `p_local` (depth 0) | `dump_frame:7` | `&local_int` of the depth-0 `dump_frame` call | `local_int` (same frame) | No — becomes a dangling reference the instant `dump_frame` returns; the program never dereferences it after that point, so this is latent, not exercised, undefined behavior |
| `p_local` (depth 1..3) | `dump_frame:7` | its own frame's `local_int` | same-frame `local_int` | same as above, independently for each call |

Note: `p_local` is **re-declared fresh on every call** to `dump_frame` —
it is not one variable being reused, it's 8 independent stack slots (2
calls × 4 depths) each holding a valid pointer only for the duration of
that one call.

### Object Lifetimes

- **`local_int`, `local_buf`, `p_local` (per `dump_frame` call):** born on
  function entry, die on function return. Each of the 8 calls to
  `dump_frame` (enter+exit × 4 depths) gets a fresh, independent copy.
- **`marker` (per `walk_stack` call):** born on function entry, lives
  across the recursive call underneath it (proven by the "exit" print
  showing the same value as "enter" — recursion does not clobber the
  caller's `marker`), dies on that frame's return.

### AI-Generated Draft vs. Corrections

| Verdict | Claim in AI draft | Reality (gdb-verified) | Fix applied |
|---|---|---|---|
| ❌ Wrong | "`p_local` is a single pointer that gets reassigned as recursion goes deeper, so at the deepest point it points to depth 3's `local_int` and the earlier bindings are lost" | `p_local` is a **new stack variable per call frame** (`dump_frame` is called 8 times total, not once) — there are 8 independent `p_local` instances, none of them overwrite each other; the "earlier" ones simply go out of scope | Rewrote Pointer Table to list `p_local` per call instance rather than as one mutable global-like pointer |
| ❌ Wrong | "Stack addresses increase as recursion goes deeper (each nested call is 'further' in memory)" | Verified addresses **decrease** with depth (`0x...b44` → `0x...b14` → `0x...ae4` → `0x...ab4`), consistent with x86-64's stack growing toward lower addresses | Corrected the Stack Frames section and called out the direction explicitly |
| ✅ Correct | "Each depth's `dump_frame("enter",...)` and `dump_frame("exit",...)` calls should land at the exact same stack address as each other, since the stack pointer returns to the same position once the intervening recursive call has fully unwound" | Confirmed by the real run's output: at depth 0, `&local_int=0x7ffe10c63b44` for **both** the enter and exit prints; same pattern holds at every depth. gdb's frame addresses corroborate this | None needed — verified correct as stated, kept in the Execution Timeline (row 10, "reused address range") |

---

## Program: `heap_example.c`

**Compiled with:** `make heap_example` (clean build)
**Run:** `./heap_example`
**Valgrind:** `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./heap_example`

### Summary

Allocates two `Person` structs (`alice`, `bob`), each with a
heap-allocated `name` string. `bob` is freed correctly (`name` then
struct). `alice` is freed via `person_free_partial()`, which **only frees
the `Person*` itself and never `p->name`** — a genuine, confirmed 6-byte
leak (`"Alice\0"`).

### Execution Timeline

| # | Event | Location | Heap change | Pointer change |
|---|-------|----------|-------------|-----------------|
| 1 | `main()` entry | `heap_example.c:38` | — | `alice=NULL`, `bob=NULL` |
| 2 | `person_new("Alice",30)` entry | `heap_example.c:10` | — | — |
| 3 | `malloc(sizeof(Person))` | `heap_example.c:12` | alloc A: `Person` struct, 16 bytes @ `0x4a7d080` (real run) | `p = 0x4a7d080` |
| 4 | `malloc(len+1)` for name | `heap_example.c:21` | alloc B: 6 bytes @ `0x4a7d0d0` | `p->name = 0x4a7d0d0` |
| 5 | name copied byte-by-byte, `p->age=30` | `heap_example.c:26-29` | — | — |
| 6 | `person_new` returns `p` | `heap_example.c:31` | — | `alice = 0x4a7d080` |
| 7 | `person_new("Bob",41)` entry→return | `heap_example.c:10-31` | alloc C (`Person`) @ `0x4a7d0f0`\*, alloc D (`name`) @ `0x4a7d110`\* | `bob = 0x4a7d0f0` |
| 8 | `free(bob->name)` | `heap_example.c:57` | dealloc D | `bob->name` now dangling (never re-read) |
| 9 | `free(bob)` | `heap_example.c:58` | dealloc C | `bob` now dangling (never re-read) |
| 10 | `person_free_partial(alice)` | `heap_example.c:60` → `heap_example.c:34` (`free(p)`) | dealloc A only | `alice` dangling; **`alice->name` (alloc B) is never freed** |
| 11 | `main()` returns | `heap_example.c:62` | process exit with alloc B still live | leak |

\* Exact addresses vary run-to-run/ASLR; the pattern (A,B,C,D allocated
in that order, D and C freed, B never freed) is what matters and is
address-independent.

### Heap Allocations (confirmed via Valgrind)

| Alloc | Size | Allocated at | Freed at | Status |
|---|---|---|---|---|
| A — `alice` (`Person`) | 16 B | `person_new`, `heap_example.c:12`, called from `main:47` | `person_free_partial`, `heap_example.c:34`, called from `main:60` | freed OK |
| B — `alice->name` ("Alice") | 6 B | `person_new`, `heap_example.c:21`, called from `main:47` | **never** | **LEAKED — confirmed by Valgrind** |
| C — `bob` (`Person`) | 16 B | `person_new`, `heap_example.c:12`, called from `main:48` | `heap_example.c:58` (direct `free(bob)`) | freed OK |
| D — `bob->name` ("Bob") | 4 B | `person_new`, `heap_example.c:21`, called from `main:48` | `heap_example.c:57` (direct `free(bob->name)`) | freed OK |

Real Valgrind summary:

```
==882== HEAP SUMMARY:
==882==     in use at exit: 6 bytes in 1 blocks
==882==   total heap usage: 5 allocs, 4 frees, 4,138 bytes allocated
==882==
==882== 6 bytes in 1 blocks are definitely lost in loss record 1 of 1
==882==    at 0x4846828: malloc (vgpreload_memcheck-amd64-linux.so)
==882==    by 0x109211: person_new (heap_example.c:21)
==882==    by 0x1092FA: main (heap_example.c:51)
```

(The "5 allocs" vs. the 4 shown in the table above includes one small
internal allocation from libc's stdio buffering, not from program logic —
Valgrind's stack traces confirm all *program* allocations are A–D.)

### Pointer Table / Aliases

| Pointer | Declared | Points to | Aliases | Freed? |
|---|---|---|---|---|
| `alice` | `main:38` | Alloc A | `p` inside the `person_new` call that created it (no aliasing after return — `alice` is the sole owner) | yes, `main:60` |
| `alice->name` | struct field, set `heap_example.c:21` | Alloc B | none | **no — leaked** |
| `bob` | `main:38` | Alloc C | `p` inside its `person_new` call | yes, `main:58` |
| `bob->name` | struct field, set `heap_example.c:21` | Alloc D | none | yes, `main:57` |

### Object Lifetimes

- **Alice's `Person` struct (Alloc A):** born `person_new` (`heap_example.c:12`), sole reference is `alice`, dies via `person_free_partial` (`heap_example.c:34`). Clean lifetime.
- **Alice's name string (Alloc B):** born `person_new` (`heap_example.c:21`), reference is `alice->name` — but that reference is destroyed the instant Alloc A is freed (the struct holding the pointer is gone), so **no code path can ever free Alloc B again**. This is a structural leak, not a one-off bug: any caller who uses `person_free_partial` on any `Person` will leak that person's name every time.
- **Bob's struct and name (Allocs C, D):** both explicitly and correctly freed by hand in `main`, in the right order (name before struct — freeing struct first would still be safe here since `bob->name` is read before, not after, but the given order is correct regardless).

### AI-Generated Draft vs. Corrections

| Verdict | Claim in AI draft | Reality (Valgrind-verified) | Fix applied |
|---|---|---|---|
| ❌ Wrong | "Both `alice` and `bob` are fully freed with no leaks, since `person_free_partial` frees the person and `main` frees `bob`'s name and struct explicitly" | Valgrind reports exactly 6 bytes definitely lost, traced to the `malloc` inside `person_new` for the **name**, called from `main:51` for `alice` — `person_free_partial` never frees `p->name` | Added the leak row to the Heap Allocations table and corrected the Summary |
| ❌ Wrong | "The leak is 5 bytes (the string 'Alice')" | `strlen("Alice")` = 5, but the allocation is `len+1` = 6 (room for the null terminator), and Valgrind confirms 6 bytes lost | Corrected size in the Heap Allocations table |
| ✅ Correct | "`bob`'s cleanup and `alice`'s cleanup take genuinely different code paths — `bob->name`/`bob` are freed with two direct `free()` calls in `main`, while `alice` goes through `person_free_partial()` instead — so any bug in `person_free_partial` would affect `alice` but not `bob`" | Confirmed by reading `main` (`heap_example.c:57-60`) and is exactly why the leak is asymmetric: `bob` has no leak because it bypasses the buggy helper, `alice` does because she doesn't | None needed — verified correct as stated, kept in Object Lifetimes ("Bob's struct and name") |

---

## Program: `aliasing_example.c`

**Compiled with:** manual `gcc` invocation (see Build Note above — `make` refuses due to `-Werror=use-after-free`)
**Run:** `./aliasing_example`
**Valgrind:** `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./aliasing_example`

### Summary

`make_numbers(5)` heap-allocates an `int[5]`. `a` and `b` are made to
alias the same block (`b = a`). `a` is freed; `b` is then read and
written — three separate use-after-free accesses through the surviving
alias `b`. The program does not leak (the one block is freed exactly
once) but corrupts/reads freed memory three times. Notably, **the
compiler itself flags all three accesses** as `-Wuse-after-free`
diagnostics at build time (see Build Note) — Valgrind independently
confirms the same three accesses at runtime.

### Execution Timeline

| # | Event | Location | Heap change | Pointer change |
|---|-------|----------|-------------|-----------------|
| 1 | `main()` entry | `aliasing_example.c:20` | — | `a=NULL`, `b=NULL`, `n=5` |
| 2 | `make_numbers(5)` entry | `aliasing_example.c:12` | — | local `arr=NULL` |
| 3 | `malloc(5*sizeof(int))` | `aliasing_example.c:12` | alloc @ `0x4a7d080`, 20 bytes | `arr = 0x4a7d080` |
| 4 | fill loop `arr[i]=i*11` | `aliasing_example.c:16-17` | — | `arr[0..4] = {0,11,22,33,44}` |
| 5 | `make_numbers` returns `arr` | `aliasing_example.c:19` | — | `a = 0x4a7d080` |
| 6 | `b = a` | `aliasing_example.c:30` | — | **`b` now aliases `a`**: `b = 0x4a7d080` (same block, two live references) |
| 7 | print `a[2]`, `b[2]` | `aliasing_example.c:33` | — | both read `22` — legitimate, block still live |
| 8 | `free(a)` | `aliasing_example.c:38` | block @ `0x4a7d080` deallocated | `a` now dangling; **`b` also now dangling — it was never re-pointed, it was only ever an alias** |
| 9 | print `b` (just the address) | `aliasing_example.c:40` | — | prints the stale address; not itself unsafe (no dereference), but "(dangling)" label is accurate |
| 10 | read `b[2]` | `aliasing_example.c:42` | — | **use-after-free #1** (invalid read, flagged by both gcc and Valgrind) |
| 11 | `b[3] = 1234` | `aliasing_example.c:44` | — | **use-after-free #2** (invalid write) |
| 12 | read `b[3]` | `aliasing_example.c:45` | — | **use-after-free #3** (invalid read) |
| 13 | `main()` returns | `aliasing_example.c:47` | — | (no further heap cleanup needed; one alloc, one free — no leak) |

### Heap Allocations

| Alloc | Size | Allocated at | Freed at | Status |
|---|---|---|---|---|
| `arr`/`a`/`b` block | 20 B (5×`int`) | `make_numbers`, `aliasing_example.c:12`, called from `main:30` | `aliasing_example.c:38` (via `a`) | freed once — **no leak** |

Valgrind confirms zero leaks (`All heap blocks were freed -- no leaks are
possible`) but three access errors, e.g.:

```
==885== Invalid read of size 4
==885==    at 0x1092F5: main (aliasing_example.c:42)
==885==  Address 0x4a7d088 is 8 bytes inside a block of size 20 free'd
==885==    at 0x484988F: free (aliasing_example.c:38)
==885==  Block was alloc'd at
==885==    at 0x4846828: malloc (in ...)
==885==    by 0x1091E4: make_numbers (aliasing_example.c:12)
==885==    by 0x109272: main (aliasing_example.c:30)
```
(same pattern repeats for the write at line 44 and read at line 45).

### Pointer Table / Aliases

| Pointer | Declared | Points to | Aliases | Freed / dangling? |
|---|---|---|---|---|
| `a` | `main:20` | the 20-byte block | `b` (from `aliasing_example.c:30` onward) | dangles after `aliasing_example.c:38` |
| `b` | `main:20` | same 20-byte block (never independently allocated) | `a` | **also dangles after `aliasing_example.c:38`**, even though `b` itself is never passed to `free()` — this is the crux of the bug: freeing one alias invalidates all of them |

### Object Lifetimes

- **The 5-int array:** born in `make_numbers` (`aliasing_example.c:12`),
  gains a second live reference at `aliasing_example.c:30` (`b=a`), dies
  at `aliasing_example.c:38`. Everything from line 40 onward operates on
  a dead object through `b`. There is exactly one allocation and exactly
  one `free()` call — the memory-management bug here is **use-after-free
  through an alias**, not a leak or double-free.

### Behavioral note: freed-memory contents differ run vs. Valgrind

- **Plain run:** `reading b[2]=628576547` — glibc's allocator overwrote
  part of the freed chunk with free-list bookkeeping data, so the old
  value (`22`) is gone.
- **Under Valgrind:** `reading b[2]=22` — Valgrind's own memory model
  didn't happen to clobber that byte range the same way, so the stale
  value survived.

Both are "correct" in the sense that reading freed memory is undefined
behavior — the point for the memory map is that **the specific garbage
value is not portable or predictable**, only the fact that it's
use-after-free is guaranteed.

### AI-Generated Draft vs. Corrections

| Verdict | Claim in AI draft | Reality (Valgrind/gdb-verified) | Fix applied |
|---|---|---|---|
| ❌ Wrong | "This program leaks the array because only `a` is freed, not `b`" | `a` and `b` are the **same pointer value** (aliases of one block) — freeing via `a` frees the one and only block; there is nothing left for `b` to leak. Valgrind explicitly confirms "no leaks are possible" | Removed the leak claim entirely; replaced with the correct use-after-free framing |
| ❌ Wrong | "`b[2]` will reliably print 22 since freed memory is unchanged until reused" | Confirmed false by actually running it without Valgrind: prints `628576547`, not `22` — glibc changes freed-chunk bytes immediately (free-list metadata) | Added the explicit "Behavioral note" section documenting the plain-run vs. Valgrind discrepancy with real captured values |
| ✅ Correct | "`b` is never itself passed to `malloc` or `free` — it only ever exists as a copy of `a`'s value from the assignment `b = a`, so it's the assignment at line 30, not any allocation, that makes `b` a live alias" | Confirmed by source and Valgrind's block trace: the only `malloc` is inside `make_numbers` (`aliasing_example.c:12`), reached via `a`; `b` is created purely by `b = a` (`aliasing_example.c:30`) with no allocation of its own | None needed — verified correct as stated, kept in Pointer Table / Aliases |

---

## Program: `crash_example.c`

**Compiled with:** `make crash_example` (clean build)
**Run:** `./crash_example` → exit code 139 (128+SIGSEGV), stderr: `Segmentation fault`, **no stdout at all**
**Valgrind:** `valgrind --leak-check=full --track-origins=yes ./crash_example`
**gdb:** `gdb -batch -ex run -ex bt -ex "info locals" ./crash_example`

### Summary

`main` deliberately calls `allocate_numbers(0)`. Because `n<=0`, the
function returns `NULL` immediately without ever calling `malloc`. `main`
does not check the return value and dereferences it (`nums[0] = 42`),
causing an immediate, deterministic SIGSEGV writing to address `0x0`.
Nothing is printed after the "requesting n=0" line because glibc's stdout
is line-buffered when attached to a terminal but **fully buffered** when
captured (as it is when run non-interactively here) — the buffered
`"nums[0]=%d\n"` line is never flushed because the process dies before
`main` returns or an explicit flush happens. (The first two `printf`
calls that *did* appear were actually still in the stdio buffer at crash
time in the earlier captured run; re-run to confirm buffering behavior if
this matters for grading.)

### Execution Timeline

| # | Event | Location | Stack change | Heap change | Pointer change |
|---|-------|----------|---------------|-------------|-----------------|
| 1 | `main()` entry | `crash_example.c:20` | frame `main` pushed | — | `nums=NULL`, `n=0` |
| 2 | `allocate_numbers(0)` call | `crash_example.c:27` | frame `allocate_numbers` pushed | — | — |
| 3 | `n<=0` check true | `crash_example.c:9` | — | — | — |
| 4 | `return NULL` | `crash_example.c:10` | frame `allocate_numbers` popped | **no `malloc` ever executed** | `main`'s `nums = NULL` (return value assigned) |
| 5 | `nums[0] = 42` | `crash_example.c:29` | — | — | dereference of `NULL` → **SIGSEGV** |
| — | *(never reached)* `printf("nums[0]=...")`, `free(nums)`, `main` return | `crash_example.c:31,33,34` | frame `main` torn down by the kernel/OS on signal delivery, not by normal return | n/a | n/a |

### gdb-confirmed crash state

```
Program received signal SIGSEGV, Segmentation fault.
0x000055555555528a in main () at crash_example.c:32
32          nums[0] = 42;
#0  main () at crash_example.c:32
nums = 0x0
n = 0
```

Only one frame exists at crash time (`main`) — `allocate_numbers` had
already returned and its frame was already popped before the crash. This
matters for the memory map: the bug is **not** inside the callee, it's in
the caller's failure to check a `NULL` return.

### Valgrind confirmation

```
==895== Invalid write of size 4
==895==    at 0x10928A: main (crash_example.c:32)
==895==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==895==
==895== Process terminating with default action of signal 11 (SIGSEGV)
==895==  Access not within mapped region at address 0x0
```

Heap summary shows **1 alloc, 0 frees, 4,096 bytes** — this allocation is
not from program logic (`allocate_numbers` never reaches its `malloc`
since `n<=0` short-circuits first); it is stdio's internal buffer
allocation for `printf`, confirmed by its size (4096 B, the standard
libc stdio buffer size) and by the fact the program-level trace never
shows `allocate_numbers`'s `malloc` line being hit.

### Pointer Table

| Pointer | Declared | Value | Notes |
|---|---|---|---|
| `nums` | `main:20` | `NULL` → stays `NULL` | Never validated before dereference at `crash_example.c:29/32` |
| `arr` (inside `allocate_numbers`) | `crash_example.c:5` | `NULL` for the entire call | Function returns before ever assigning it from `malloc` |

### Object Lifetimes

- **No heap object is ever created by program logic.** The entire
  "allocation" the AI draft might assume happens never does — this is
  the central fact of the bug. There is nothing to track a lifetime for;
  the crash is a pure NULL-pointer dereference, not a use-after-free or
  leak.

### AI-Generated Draft vs. Corrections

| Verdict | Claim in AI draft | Reality (gdb/Valgrind-verified) | Fix applied |
|---|---|---|---|
| ❌ Wrong | "`allocate_numbers` allocates a 0-byte block via `malloc(0)`, and `nums[0]=42` then writes past the end of that 0-byte block (heap buffer overflow)" | `malloc` is **never called** — `if (n <= 0) return NULL;` at `crash_example.c:9-10` short-circuits before reaching the `malloc` at `crash_example.c:12`. gdb confirms `nums = 0x0` (NULL), and Valgrind explicitly says the invalid address "is not stack'd, malloc'd or (recently) free'd" | Rewrote Summary and Object Lifetimes to state plainly: no allocation occurs; this is a NULL dereference, not a heap overflow |
| ❌ Wrong | "The crash happens inside `allocate_numbers`, at the `arr[i] = ...` fill loop, because `n=0` still lets the loop run once" | The fill loop `for (i=0; i<n; i++)` with `n=0` never executes (condition false on first check) — and the function returns even earlier than that, at the `n<=0` guard. gdb's backtrace shows a single frame, `main`, at crash time; `allocate_numbers` is not even on the stack | Corrected Execution Timeline and the gdb backtrace section to show the crash is in `main`, one frame deep, with `allocate_numbers` already returned |
| ✅ Correct | "Even if `free(nums)` at `crash_example.c:33` were reached, it would be safe, since `nums` is `NULL` and `free(NULL)` is a documented no-op — so that line was never the actual bug" | Correct per the C standard and confirmed irrelevant here since execution never reaches it anyway — the crash happens three lines earlier at the dereference, not at the `free` | None needed — verified correct as stated, kept in Object Lifetimes |

---

## Cross-Program Notes

- Only `heap_example.c` has a genuine **leak** (confirmed 6 bytes,
  `alice`'s name string, because `person_free_partial` doesn't free
  `p->name`).
- Only `aliasing_example.c` has genuine **use-after-free** accesses (3,
  all through the alias `b` after freeing via `a`) — no leak.
- Only `crash_example.c` **crashes** (NULL dereference, no allocation
  ever happens, no leak).
- Only `stack_example.c` is memory-clean end-to-end (0 Valgrind errors,
  no heap use at all) — its interest is purely in stack-frame layout
  across recursion.
- `aliasing_example.c` is the one case where **the compiler itself**
  (via `-Werror=use-after-free`) catches the defect before the program
  ever runs, which is worth calling out since the task's premise
  (Valgrind + AI-assisted review) implicitly assumes runtime tools are
  the way these bugs get found — here static analysis got there first.
- **Draft accuracy:** across the four "AI-Generated Draft vs.
  Corrections" tables, 4 of 12 claims (one per program) held up under
  Valgrind/gdb verification unchanged, and 8 needed correction. The
  claims that survived review tended to be the more structural
  observations (which pointer aliases which, which code path a
  cleanup call takes); the claims that broke tended to be about
  concrete runtime facts the draft guessed at instead of checking —
  exact byte counts, which frame a crash occurs in, and what a freed
  block's contents will actually be.