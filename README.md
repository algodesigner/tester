# Tester: A Miniature C Testing Framework

Tester is a lightweight, single-file unit testing framework for C. It is designed to be simple to integrate and easy to use for both small projects and embedded systems.

## Key Features

- **Minimalist**: Minimal dependencies and small footprint.
- **Grouped Tests**: Organise your assertions into logical groups.
- **Flexible Output**: Control output verbosity and redirect logs to any file stream.
- **Easy Integration**: Just include `tester.h` and link with `tester.c`.

## Getting Started

### 1. Basic Example

Here is a quick look at how to use Tester:

```c
#include "tester.h"

int main() {
    // Create a tester instance (outputs to stdout, logs all tests)
    tester *t = tester_create(stdout, false);

    tester_new_group(t, "Arithmetic Tests");
    tester_assert(t, 1 + 1 == 2, "1 + 1 equals 2");
    tester_assert(t, 5 * 2 == 10, "5 * 2 equals 10");

    tester_new_group(t, "Logic Tests");
    tester_assert(t, true, "True is true");

    // Final result (returns true if all tests passed)
    bool success = tester_result(t);

    // Finalise and cleanup
    tester_destroy(t);

    return success ? 0 : 1;
}
```

### 2. Compilation

Compile your test file along with `tester.c`:

```bash
gcc -o my_tests main.c src/tester.c -Isrc
./my_tests
```

## API Reference

### Lifecycle Management

- `tester *tester_create(FILE *fp, bool only_failures)`
  Creates a new tester instance. `fp` is the output stream (e.g., `stdout` or a file). If `only_failures` is true, successful tests will not be logged.
- `void tester_destroy(tester *obj)`
  Finalises the report, flushes the output, and frees all memory associated with the tester.

### Running Tests

- `void tester_new_group(tester *obj, const char *name)`
  Starts a new group of tests. All subsequent assertions will be reported under this group.
- `tester_assert(obj, exp, name)`
  The primary macro for testing. `exp` is the expression to evaluate, and `name` is a descriptive name for the test.

### Results

- `bool tester_result(tester *obj)`
  Returns `true` if all tests performed so far have passed, `false` otherwise.

## Documentation and Examples

- [tester.h](file:///Users/vlad/.gemini/antigravity/scratch/tester/src/tester.h): Detailed interface definition.
- [example.c](file:///Users/vlad/.gemini/antigravity/scratch/tester/src/example.c): A more complex sample application showing advanced usage.

Enjoy! ☕
