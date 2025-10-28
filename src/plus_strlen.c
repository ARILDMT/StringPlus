#include "string_plus.h"

plus_size_t plus_strlen(const char *str) {
  plus_size_t length = 0;
  for (; str[length]; length++);
  return length;
}