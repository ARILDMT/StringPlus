#include "string_plus.h"

void *plus_memcpy(void *dest, const void *src, plus_size_t n) {
  unsigned char *d = dest;
  const unsigned char *s = src;
  for (plus_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return dest;
}