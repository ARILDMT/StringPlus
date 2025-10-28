#include "string_plus.h"

int plus_memcmp(const void *str1, const void *str2, plus_size_t n) {
  const unsigned char *p1 = str1;
  const unsigned char *p2 = str2;
  int result = 0;
  for (plus_size_t i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      result = p1[i] - p2[i];
      i = n;
    }
  }
  return result;
}