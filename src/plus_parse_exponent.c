#include <math.h>

#include "string_plus.h"

void plus_parse_exponent(const char **ptr, int *chars_read, int max_width,
                        long double *result) {
  if (*chars_read < max_width && (**ptr == 'e' || **ptr == 'E')) {
    (*ptr)++;
    (*chars_read)++;
    int exp_sign = 1;
    int exponent = 0;
    if (*chars_read < max_width && **ptr == '-') {
      exp_sign = -1;
      (*ptr)++;
      (*chars_read)++;
    } else if (*chars_read < max_width && **ptr == '+') {
      (*ptr)++;
      (*chars_read)++;
    }
    int exp_has_digits = 0;
    while (*chars_read < max_width && isdigit(**ptr)) {
      exponent = exponent * 10 + (**ptr - '0');
      (*ptr)++;
      (*chars_read)++;
      exp_has_digits = 1;
    }
    if (exp_has_digits) {
      int limited_exp = exp_sign * exponent;
      if (limited_exp > 308) limited_exp = 308;
      if (limited_exp < -308) limited_exp = -308;
      *result *= powl(10.0L, limited_exp);
    }
  }
}
