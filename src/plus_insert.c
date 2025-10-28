#include "string_plus.h"

void *plus_insert(const char *src, const char *str, plus_size_t start_index) {
  char *result = PLUS_NULL;
  if (src != PLUS_NULL && str != PLUS_NULL) {
    plus_size_t src_len = plus_strlen(src);
    if (start_index <= src_len) {
      plus_size_t str_len = plus_strlen(str);
      result = malloc(src_len + str_len + 1);
      if (result != PLUS_NULL) {
        plus_strncpy(result, src, start_index);
        result[start_index] = '\0';
        plus_strcat(result, str);
        plus_strcat(result, src + start_index);
      }
    }
  }
  return result;
}
