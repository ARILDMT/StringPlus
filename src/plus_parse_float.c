#include <limits.h>

#include "string_plus.h"

long double plus_parse_float(const char **str, int width, int *parsed_chars) {
  const char *ptr = *str;
  long double result = 0.0L;
  long double fraction = 0.0L;
  long double divisor = 1.0L;
  int chars_read = 0;
  int max_width = width > 0 ? width : INT_MAX;
  int has_digits = 0;
  int sign = plus_parse_sign(&ptr, &chars_read, max_width);
  result = plus_parse_integer_part(&ptr, &chars_read, max_width, &has_digits);
  plus_parse_fraction_part(&ptr, &chars_read, max_width, &fraction, &divisor,
                          &has_digits);
  long double ret = 0.0L;
  if (!has_digits) {
    *parsed_chars = 0;
    ret = 0.0L;
  } else {
    result += fraction / divisor;
    plus_parse_exponent(&ptr, &chars_read, max_width, &result);
    *str = ptr;
    *parsed_chars = chars_read;
    ret = result * sign;
  }
  return ret;
}
