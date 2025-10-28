#include "string_plus.h"

char *plus_strpbrk(const char *str1, const char *str2) {
  int flag = 0;
  char *src = PLUS_NULL;
  while (*str1 != '\0' && flag == 0) {
    if (plus_strchr(str2, *str1)) {
      flag = 1;
      src = (char *)str1;
    } else {
      str1++;
    }
  }
  return src;
}