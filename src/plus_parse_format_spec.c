#include "string_plus.h"

const char *plus_parse_format_spec(const char *format, format_spec_t *spec) {
  const char *ptr = format;
  if (*ptr == '*') {
    spec->suppress = 1;
    ptr++;
  }
  if (isdigit(*ptr)) {
    spec->width = 0;
    int width_digits = 0;
    int overflow_detected = 0;

    while (isdigit(*ptr) && !overflow_detected) {
      if (width_digits <= 8 && spec->width <= 100000) {
        spec->width = spec->width * 10 + (*ptr - '0');
        ptr++;
        width_digits++;
      } else {
        overflow_detected = 1;
      }
    }

    if (overflow_detected) {
      while (isdigit(*ptr)) {
        ptr++;
      }
    }
  }
  if (*ptr == 'h' || *ptr == 'l' || *ptr == 'L') {
    spec->length = *ptr;
    ptr++;
  }
  spec->specifier = *ptr;
  ptr++;
  const char *result = ptr;
  return result;
}