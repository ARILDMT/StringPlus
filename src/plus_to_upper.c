#include "string_plus.h"

static void convert_to_uppercase(char *str) {
  char *buf = str;
  while (*buf != '\0') {
    if (*buf >= 'a' && *buf <= 'z') {
      (*buf) -= 32;
    }
    buf++;
  }
}

void *plus_to_upper(const char *str) {
  char *result = PLUS_NULL;
  if (str != PLUS_NULL) {
    plus_size_t len = plus_strlen(str);
    result = malloc(len + 1);
    if (result != PLUS_NULL) {
      plus_strncpy(result, str, len);
      result[len] = '\0';
      convert_to_uppercase(result);
    }
  }
  return result;
}
