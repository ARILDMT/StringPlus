#include "string_plus.h"

char *plus_strncpy(char *dest, const char *str1, plus_size_t n) {
  plus_size_t i;
  for (i = 0; i < n && str1[i] != '\0'; i++) {
    dest[i] = str1[i];
  }
  for (; i < n; i++) {
    dest[i] = '\0';
  }
  return dest;
}