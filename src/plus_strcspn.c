#include "string_plus.h"

plus_size_t plus_strcspn(const char *str1, const char *str2) {
  plus_size_t len = 0;
  int flag = 0;
  while (*str1 != '\0' && flag == 0) {
    if (plus_strchr(str2, *str1)) {
      flag = 1;
    } else {
      len++;
    }
    str1++;
  }
  return len;
}