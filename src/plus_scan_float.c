#include "string_plus.h"

const char *plus_scan_float(const char *str, format_spec_t *spec, va_list *args,
                           int *count) {
  const char *result = NULL;
  str = plus_skip_whitespace(str);
  if (*str) {
    int parsed_chars = 0;
    long double value = plus_parse_float(&str, spec->width, &parsed_chars);
    if (parsed_chars > 0) {
      if (!spec->suppress) {
        plus_assign_float_value(args, spec, value);
      }
      *count = 1;
      result = str;
    }
  }
  const char *ret = result;
  return ret;
}
