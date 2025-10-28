#include "string_plus.h"

void plus_process_percent(const char **str_ptr, const char **fmt_ptr,
                         va_list *args, int *successful_conversions,
                         int *continue_parsing, const char *str) {
  if (*((*fmt_ptr) + 1) == '%') {
    *continue_parsing = plus_handle_literal_match(str_ptr, fmt_ptr);
    if (*continue_parsing) (*fmt_ptr)++;
  } else {
    *continue_parsing = plus_process_specifier(str_ptr, fmt_ptr, args,
                                              successful_conversions, str);
  }
}
