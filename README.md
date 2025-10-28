# StringPlus

A comprehensive C library implementing string manipulation functions with custom implementations of `sprintf` and `sscanf`.

## Overview

StringPlus is a feature-rich string processing library written in C11. It provides a complete reimplementation of the standard `string.h` library functions, along with custom implementations of `sprintf` and `sscanf` from `stdio.h`, plus additional utility functions inspired by C#'s String class.

## Features

### Standard String Functions
Complete implementation of standard C string manipulation functions:
- Memory operations: `memchr`, `memcmp`, `memcpy`, `memset`
- String operations: `strlen`, `strchr`, `strrchr`, `strcmp`, `strcpy`, `strcat`, `strncat`, `strncpy`, `strncmp`
- Search functions: `strstr`, `strpbrk`, `strcspn`, `strspn`, `strtok`
- Error handling: `strerror` with platform-specific error messages

### Custom Formatted I/O Functions
- **sprintf**: Full implementation supporting all standard format specifiers
  - Specifiers: `c`, `d`, `i`, `f`, `e`, `E`, `g`, `G`, `s`, `u`, `x`, `X`, `o`, `p`, `n`, `%`
  - Flags: `-`, `+`, ` ` (space), `#`, `0`
  - Width and precision modifiers
  - Length modifiers: `h`, `l`, `L`

- **sscanf**: Complete implementation for parsing formatted input
  - All standard format specifiers
  - Width and length modifiers
  - Suppression flag `*`

### Additional Utility Functions
Inspired by C# String class:
- `to_upper`: Convert string to uppercase
- `to_lower`: Convert string to lowercase
- `insert`: Insert substring at specified position
- `trim`: Remove leading and trailing characters

## Technical Details

- **Language**: C11 standard
- **Compiler**: GCC
- **Code Style**: Google C++ Style Guide adapted for C
- **Testing**: Unit tests with Check library
- **Test Coverage**: 80%+ for all functions
- **Platform Support**: Cross-platform (Linux, macOS)

## Building

```bash
# Build the library
make

# Run tests
make test

# Generate coverage report
make gcov_report

# Clean build artifacts
make clean
```

## Project Structure

```
StringPlus/
├── src/
│   ├── string_plus.h      # Main header file
│   ├── plus_sprintf.h     # sprintf implementation header
│   ├── plus_sprintf.c     # sprintf implementation
│   ├── plus_sscanf.c      # sscanf implementation
│   ├── plus_*.c           # Individual function implementations
│   ├── test_string_plus.c # Unit tests
│   └── utils.c            # Utility functions
├── LICENSE
└── README.md
```

## Implementation Highlights

### Memory Safety
All functions implement proper bounds checking and handle edge cases to prevent buffer overflows and undefined behavior.

### Platform Compatibility
Error message handling (`strerror`) includes platform-specific implementations for both macOS and Linux systems.

### Formatted Output Precision
The `sprintf` implementation matches the standard library's output precision (up to 1e-6 for floating-point numbers).

### Comprehensive Testing
Unit tests compare implementation results against the standard library to ensure correctness and compatibility.

## Skills Demonstrated

- **Low-level C programming**: Direct memory manipulation, pointer arithmetic
- **Standard library implementation**: Deep understanding of C standard library internals
- **Parsing and formatting**: Complex format string parsing and number formatting algorithms
- **Cross-platform development**: Platform-specific code with preprocessor directives
- **Testing and quality assurance**: Comprehensive unit testing with high code coverage
- **Software engineering practices**: Clean code, modular design, documentation

## License

MIT License - see [LICENSE](LICENSE) file for details.

