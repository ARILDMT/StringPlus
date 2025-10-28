#include "string_plus.h"

int plus_handle_literal_match(const char **str_ptr, const char **fmt_ptr) {
  int result = 0;
  if (**str_ptr == **fmt_ptr) {
    (*str_ptr)++;
    (*fmt_ptr)++;
    result = 1;
  }
  return result;
}
