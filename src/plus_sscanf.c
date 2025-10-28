#include "string_plus.h"

int plus_sscanf(const char *str, const char *format, ...) {
  int result = -1;
  if (str && format) {
    va_list args;
    va_start(args, format);
    int successful_conversions = 0;
    const char *str_ptr = str;
    const char *fmt_ptr = format;
    int continue_parsing = 1;
    while (*fmt_ptr && *str_ptr && continue_parsing) {
      if (isspace(*fmt_ptr)) {
        while (isspace(*fmt_ptr)) fmt_ptr++;
        str_ptr = plus_skip_whitespace(str_ptr);
      } else if (*fmt_ptr == '%') {
        plus_process_percent(&str_ptr, &fmt_ptr, &args, &successful_conversions,
                            &continue_parsing, str);
      } else {
        continue_parsing = plus_handle_literal_match(&str_ptr, &fmt_ptr);
      }
    }
    va_end(args);
    result = successful_conversions;
  }
  return result;
}
