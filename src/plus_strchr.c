#include "string_plus.h"

char *plus_strchr(const char *str, int c) {
  const char *ptr = PLUS_NULL;
  int flag = 0;
  if (str == PLUS_NULL) {
    flag = 1;
  }
  plus_size_t len = 0;
  if (flag == 0) {
    len = plus_strlen(str);
  }
  for (plus_size_t i = 0; i <= len && flag == 0; i++) {
    if (str[i] == (char)c) {
      ptr = (str + i);
      flag = 1;
    }
  }
  return (char *)ptr;
}