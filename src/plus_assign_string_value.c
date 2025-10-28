#include "string_plus.h"

void plus_assign_string_value(va_list *args, const char *start, int len) {
  char *dest = va_arg(*args, char *);
  if (dest) {
    for (int i = 0; i < len; i++) {
      dest[i] = start[i];
    }
    dest[len] = '\0';
  }
}
