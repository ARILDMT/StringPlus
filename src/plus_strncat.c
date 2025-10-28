#include "string_plus.h"

char *plus_strncat(char *dest, const char *str1, plus_size_t n) {
  char *ptr = dest;
  plus_size_t len = plus_strlen(str1);
  if (len < n) {
    n = len;
  }
  while (*ptr != '\0') {
    ptr++;
  }
  for (plus_size_t i = 0; i < n; i++) {
    *ptr = *str1;
    ptr++;
    str1++;
  }
  *ptr = '\0';
  return dest;
}