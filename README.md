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
├── .gitignore
├── LICENSE
├── README.md
└── src/
    ├── Makefile
    ├── string_plus.h               # Main header file
    ├── plus_sprintf.h              # sprintf header
    │
    ├── plus_memchr.c               # Memory functions
    ├── plus_memcmp.c
    ├── plus_memcpy.c
    ├── plus_memset.c
    │
    ├── plus_strlen.c               # String functions
    ├── plus_strchr.c
    ├── plus_strrchr.c
    ├── plus_strcmp.c
    ├── plus_strncmp.c
    ├── plus_strcpy.c
    ├── plus_strncpy.c
    ├── plus_strcat.c
    ├── plus_strncat.c
    ├── plus_strcspn.c
    ├── plus_strspn.c
    ├── plus_strpbrk.c
    ├── plus_strstr.c
    ├── plus_strtok.c
    ├── plus_strerror.c
    │
    ├── plus_sprintf.c              # Formatted output
    ├── plus_sscanf.c               # Formatted input
    │
    ├── plus_to_upper.c             # Utility functions
    ├── plus_to_lower.c
    ├── plus_insert.c
    ├── plus_trim.c
    │
    ├── plus_assign_char_value.c    # sscanf helpers
    ├── plus_assign_float_value.c
    ├── plus_assign_integer_value.c
    ├── plus_assign_pointer_value.c
    ├── plus_assign_string_value.c
    ├── plus_char_to_digit.c
    ├── plus_handle_literal_match.c
    ├── plus_parse_exponent.c
    ├── plus_parse_float.c
    ├── plus_parse_format_spec.c
    ├── plus_parse_fraction_part.c
    ├── plus_parse_integer.c
    ├── plus_parse_integer_part.c
    ├── plus_parse_sign.c
    ├── plus_process_percent.c
    ├── plus_process_specifier.c
    ├── plus_scan_char.c
    ├── plus_scan_float.c
    ├── plus_scan_integer.c
    ├── plus_scan_pointer.c
    ├── plus_scan_string.c
    ├── plus_skip_whitespace.c
    │
    ├── test_string_plus.c          # Unit tests
    └── utils.c                     # Utility functions
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

## Usage Example

```c
#include "string_plus.h"

int main() {
    // Using standard string functions with plus_ prefix
    char str[100] = "Hello, ";
    plus_strncat(str, "World!", 10);
    printf("Length: %zu\n", plus_strlen(str));

    // Using sprintf implementation
    char buffer[100];
    plus_sprintf(buffer, "Number: %d, Float: %.2f", 42, 3.14);

    // Using sscanf implementation
    int num;
    float flt;
    plus_sscanf("42 3.14", "%d %f", &num, &flt);

    // Using utility functions
    char *upper = plus_to_upper("hello");
    char *trimmed = plus_trim("  spaces  ", " ");

    free(upper);
    free(trimmed);

    return 0;
}
```

## API Reference

All functions use the `plus_` prefix to avoid naming conflicts with standard library functions.

### String Functions
- `plus_size_t plus_strlen(const char *str)` - Calculate string length
- `char *plus_strchr(const char *str, int c)` - Find first occurrence of character
- `char *plus_strstr(const char *haystack, const char *needle)` - Find substring
- `char *plus_strncpy(char *dest, const char *src, plus_size_t n)` - Copy string
- And many more...

### Memory Functions
- `void *plus_memchr(const void *str, int c, plus_size_t n)` - Find byte in memory
- `int plus_memcmp(const void *str1, const void *str2, plus_size_t n)` - Compare memory blocks
- `void *plus_memcpy(void *dest, const void *src, plus_size_t n)` - Copy memory
- `void *plus_memset(void *str, int c, plus_size_t n)` - Fill memory with byte

### Formatted I/O
- `int plus_sprintf(char *str, const char *format, ...)` - Format string output
- `int plus_sscanf(const char *str, const char *format, ...)` - Parse formatted input

### Utility Functions
- `void *plus_to_upper(const char *str)` - Convert to uppercase (allocates new string)
- `void *plus_to_lower(const char *str)` - Convert to lowercase (allocates new string)
- `void *plus_insert(const char *src, const char *str, plus_size_t start_index)` - Insert substring
- `void *plus_trim(const char *src, const char *trim_chars)` - Trim characters

## Testing

The project includes comprehensive unit tests covering:
- Boundary conditions and edge cases
- Comparison with standard library behavior
- Memory safety and error handling
- Format string parsing accuracy
- Cross-platform compatibility

Run tests with:
```bash
cd src
make test
```

Generate coverage report:
```bash
cd src
make gcov_report
```

## Contributing

This is a personal portfolio project demonstrating C programming skills. However, if you find bugs or have suggestions, feel free to open an issue.

## License

MIT License - see [LICENSE](LICENSE) file for details.

## Author

**Arsi Richter**

This project showcases advanced C programming capabilities including:
- Implementation of complex standard library functions from scratch
- Advanced format string parsing and number conversion algorithms
- Memory-safe string manipulation
- Cross-platform C development
- Test-driven development practices

---

*This project was developed as a comprehensive demonstration of C programming proficiency and software engineering best practices.*
