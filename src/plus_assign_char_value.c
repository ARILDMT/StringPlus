#include "string_plus.h"

void plus_assign_char_value(va_list *args, const char *str, int width) {
  char *dest = va_arg(*args, char *);
  if (dest) {
    for (int i = 0; i < width && str[i]; i++) {
      dest[i] = str[i];
    }
  }
}
