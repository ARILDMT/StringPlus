#include "string_plus.h"

void *plus_memset(void *str, int c, plus_size_t n) {
  unsigned char *p = str;
  for (plus_size_t i = 0; i < n; i++) {
    p[i] = (unsigned char)c;
  }
  return str;
}
