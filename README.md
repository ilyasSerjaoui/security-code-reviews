# security-code-reviews

## Overview
This repository analyzes a simple C program that echoes command-line arguments. The program contains several security vulnerabilities, including potential buffer overflows and unsafe function usage. This document details the identified issues and provides recommendations for secure coding practices.

## Identified Security Issues

### Buffer Overflow Risk in `sprintf(out, ...)`
#### Issue:
- `sprintf` does not perform bounds checking, which can cause memory corruption if an argument is too long.
#### Fix:
```c
snprintf(out, sizeof(out), "argument %d is %s\n", argc-1, argv[argc-1]);
```

### Potential Buffer Overflow in `strncat(buf, out, sizeof(buf)-len-1);`
#### Issue:
- `buf` is `N=1000`, and `out` is `S=100`. If many long arguments are passed, `buf` could overflow.
#### Fix:
```c
strncat(buf, out, sizeof(buf) - strlen(buf) - 1);
```

### Incorrect Use of `printf(msg);`
#### Issue:
- `printf(msg);` is dangerous because `msg` is not a format string. If `msg` contains format specifiers (e.g., `%s`), it could lead to format string vulnerabilities.
#### Fix:
```c
printf("%s", msg);
```

### Redundant `len` Calculation
#### Issue:
- `len = strlen(buf);` is recalculated in every loop iteration, which is unnecessary.
#### Fix:
- Remove `len` and replace it directly inside `strncat()`.


## Lessons Learned
1. **Avoid using `sprintf()`** – always prefer `snprintf()` to prevent buffer overflows.
2. **Ensure buffers do not overflow** – use `sizeof(buf) - strlen(buf) - 1` when concatenating strings.
3. **Use format strings explicitly in `printf()`** – never pass raw variables.
4. **Optimize redundant calculations** – unnecessary operations inside loops should be minimized.

## Contributing
If you find other potential issues or improvements, feel free to submit a pull request or open an issue.

---
This analysis serves as a practical exercise in code security review and best practices for writing secure C programs.

