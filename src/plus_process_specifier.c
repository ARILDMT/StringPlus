#include <float.h>
#include <limits.h>
#include <math.h>

#include "string_plus.h"

int plus_process_specifier(const char **str_ptr, const char **fmt_ptr,
                          va_list *args, int *successful_conversions,
                          const char *original_str) {
  format_spec_t spec = {0};
  *fmt_ptr = plus_parse_format_spec(*fmt_ptr + 1, &spec);
  const char *new_str_ptr = NULL;
  int local_count = 0;
  int result = 1;
  if (spec.specifier == 'c') {
    new_str_ptr = plus_scan_char(*str_ptr, &spec, args, &local_count);
  } else if (spec.specifier == 'd' || spec.specifier == 'i' ||
             spec.specifier == 'o' || spec.specifier == 'u' ||
             spec.specifier == 'x' || spec.specifier == 'X') {
    new_str_ptr = plus_scan_integer(*str_ptr, &spec, args, &local_count);
  } else if (spec.specifier == 'f' || spec.specifier == 'F' ||
             spec.specifier == 'e' || spec.specifier == 'E' ||
             spec.specifier == 'g' || spec.specifier == 'G') {
    new_str_ptr = plus_scan_float(*str_ptr, &spec, args, &local_count);
  } else if (spec.specifier == 's') {
    new_str_ptr = plus_scan_string(*str_ptr, &spec, args, &local_count);
  } else if (spec.specifier == 'p') {
    new_str_ptr = plus_scan_pointer(*str_ptr, &spec, args, &local_count);
  } else if (spec.specifier == 'n') {
    new_str_ptr = *str_ptr;
    local_count = 1;
    if (!spec.suppress) {
      int *n_ptr = va_arg(*args, int *);
      if (n_ptr) *n_ptr = *str_ptr - original_str;
    }
  } else {
    result = 0;
  }
  if (new_str_ptr && result) {
    *str_ptr = new_str_ptr;
    if (!spec.suppress && local_count > 0) {
      (*successful_conversions)++;
    }
  } else {
    result = 0;
  }
  return result;
}
