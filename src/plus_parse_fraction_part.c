#include "string_plus.h"

void plus_parse_fraction_part(const char **ptr, int *chars_read, int max_width,
                             long double *fraction, long double *divisor,
                             int *has_digits) {
  if (*chars_read < max_width && **ptr == '.') {
    (*ptr)++;
    (*chars_read)++;
    while (*chars_read < max_width && isdigit(**ptr)) {
      if (*divisor > 1e100L) {
      } else {
        *fraction = *fraction * 10.0L + (**ptr - '0');
        *divisor *= 10.0L;
      }
      (*ptr)++;
      (*chars_read)++;
      *has_digits = 1;
    }
  }
}
