#include "string_plus.h"

const char *plus_scan_pointer(const char *str, format_spec_t *spec,
                             va_list *args, int *count) {
  const char *result = NULL;
  str = plus_skip_whitespace(str);
  int early_exit = 0;
  if (!*str) early_exit = 1;
  if (!early_exit && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
    str += 2;
  }
  int parsed_chars = 0;
  unsigned long long value = 0;
  if (!early_exit) {
    value = (unsigned long long)plus_parse_integer(&str, 16, spec->width,
                                                  &parsed_chars);
    if (parsed_chars <= 0) early_exit = 1;
  }
  if (!early_exit && !spec->suppress) {
    plus_assign_pointer_value(args, value);
  }
  if (!early_exit) {
    *count = 1;
    result = str;
  }
  const char *ret = result;
  return ret;
}
