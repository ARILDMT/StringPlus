#include "string_plus.h"

long double plus_parse_integer_part(const char **ptr, int *chars_read,
                                   int max_width, int *has_digits) {
  long double result = 0.0L;
  while (*chars_read < max_width && isdigit(**ptr)) {
    if (result > 1e100L) {
    } else {
      result = result * 10.0L + (**ptr - '0');
    }
    (*ptr)++;
    (*chars_read)++;
    *has_digits = 1;
  }
  return result;
}
