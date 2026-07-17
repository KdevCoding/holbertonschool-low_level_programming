# Simple C Calculator
 
A command-line calculator written in C that supports basic arithmetic
operations on integers, with input validation and a repeatable menu loop.

AI assisted in writing/formating this README, no AI was used in the making of the program
 
## Compile
 
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 calculator.c -o calculator
```
 
## Run
 
```bash
./calculator
```

## Supported Operations
 
| Choice | Operation      |
|--------|----------------|
| 1      | Addition       |
| 2      | Subtraction    |
| 3      | Multiplication |
| 4      | Division       |
| 0      | Quit           |

## Numeric Behavior
 
- All inputs and outputs are **integers** (`int`) — there is no support
  for decimal/floating-point numbers.
- Division (`4`) performs **integer division**, meaning any remainder is
  truncated (rounded toward zero), not rounded to the nearest whole
  number.
- Division by zero is explicitly checked for and will print an error
  message instead of attempting the operation.
- Non-numeric input (for the menu choice or for `A`/`B`) is detected
  and the user is re-prompted until a valid integer is entered.
- Entering a menu choice greater than `4` (and not `0`) is treated as
  invalid and re-prompts the menu.

## Known Limitations
 
- Integer overflow is not checked: results, or the `A`/`B` inputs
  themselves, that exceed the range of `int` will produce undefined
  or wrapped behavior.
- Only whole numbers are supported; there is no way to enter or
  calculate decimal values.
- The program does not support chained operations (e.g. `A + B * C`)
  — only a single operation between two numbers per pass through the
  menu.
- The four arithmetic branches (`+`, `-`, `*`, `/`) largely duplicate
  the same input-reading logic for `A` and `B`; this works correctly
  but could be refactored into a helper function to reduce repetition
  if extending the project.
- Similarly, the "invalid number, retry" error-handling loop used for
  `A` and `B` is duplicated across all four operations and could be
  extracted into its own function (e.g. `read_int(prompt)`) that
  prompts, validates, and retries in one place