#include "string_plus.h"

void *plus_memchr(const void *str, int c, plus_size_t n) {
  const unsigned char *p = str;
  void *result = PLUS_NULL;

  for (plus_size_t i = 0; i < n; i++) {
    if (p[i] == (unsigned char)c) {
      result = (void *)(p + i);
      i = n;
    }
  }

  return result;
}