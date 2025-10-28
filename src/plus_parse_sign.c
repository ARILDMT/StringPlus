#include "string_plus.h"

int plus_parse_sign(const char **ptr, int *chars_read, int max_width) {
  int sign = 1;
  if (*chars_read < max_width && **ptr == '-') {
    sign = -1;
    (*ptr)++;
    (*chars_read)++;
  } else if (*chars_read < max_width && **ptr == '+') {
    (*ptr)++;
    (*chars_read)++;
  }
  return sign;
}
