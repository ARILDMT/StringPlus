#include <limits.h>

#include "string_plus.h"

const char *plus_scan_string(const char *str, format_spec_t *spec, va_list *args,
                            int *count) {
  const char *result = NULL;
  str = plus_skip_whitespace(str);
  int early_exit = 0;
  if (!*str) early_exit = 1;
  const char *start = str;
  int width = spec->width > 0 ? spec->width : INT_MAX;
  int len = 0;
  if (!early_exit) {
    while (*str && !isspace(*str) && len < width) {
      str++;
      len++;
    }
    if (len <= 0) early_exit = 1;
  }
  if (!early_exit && !spec->suppress) {
    plus_assign_string_value(args, start, len);
  }
  if (!early_exit) {
    *count = 1;
    result = str;
  }
  const char *ret = result;
  return ret;
}
