#include "string_plus.h"

int plus_strncmp(const char *str1, const char *str2, plus_size_t n) {
  plus_size_t count = 0;
  int result = 0;
  while (count < n && str1[count] && str2[count] && result == 0) {
    if (str1[count] != str2[count]) {
      result = (unsigned char)str1[count] - (unsigned char)str2[count];
    }
    count++;
  }
  if (count < n && result == 0) {
    result = (unsigned char)str1[count] - (unsigned char)str2[count];
  }
  return result;
}
