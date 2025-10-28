#include "string_plus.h"

char *plus_strrchr(const char *str, int c) {
  const char *ptr = PLUS_NULL;
  if (str != PLUS_NULL) {
    plus_size_t len = plus_strlen(str);
    for (plus_size_t i = 0; i <= len; i++) {
      if (str[i] == c) {
        ptr = (str + i);
      }
    }
  }
  return (char *)ptr;
}