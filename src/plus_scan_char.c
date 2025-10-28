#include "string_plus.h"

const char *plus_scan_char(const char *str, format_spec_t *spec, va_list *args,
                          int *count) {
  const char *result = NULL;
  int early_exit = 0;
  if (!*str) early_exit = 1;

  int width = spec->width > 0 ? spec->width : 1;

  if (!early_exit) {
    plus_size_t str_len = plus_strlen(str);
    if (width > (int)str_len) {
      width = (int)str_len;
    }
  }

  if (!early_exit && !spec->suppress) {
    plus_assign_char_value(args, str, width);
  }
  if (!early_exit) {
    *count = 1;
    result = str + width;
  }
  const char *ret = result;
  return ret;
}
