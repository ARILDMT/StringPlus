#include "string_plus.h"

const char *plus_scan_integer(const char *str, format_spec_t *spec,
                             va_list *args, int *count) {
  const char *result = NULL;
  str = plus_skip_whitespace(str);
  if (*str) {
    int base = 10;
    switch (spec->specifier) {
      case 'o':
        base = 8;
        break;
      case 'x':
      case 'X':
        base = 16;
        break;
      case 'i':
        if (*str == '0') {
          if (str[1] == 'x' || str[1] == 'X')
            base = 16;
          else
            base = 8;
        }
        break;
    }
    int parsed_chars = 0;
    long long value = plus_parse_integer(&str, base, spec->width, &parsed_chars);
    if (parsed_chars > 0) {
      if (!spec->suppress) {
        plus_assign_integer_value(args, spec, value);
      }
      *count = 1;
      result = str;
    }
  }
  const char *ret = result;
  return ret;
}
