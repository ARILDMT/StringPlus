#include "string_plus.h"

void *plus_trim(const char *src, const char *trim_chars) {
  char *result = PLUS_NULL;

  if (src != PLUS_NULL && trim_chars != PLUS_NULL) {
    plus_size_t src_len = plus_strlen(src);
    plus_size_t start = plus_strspn(src, trim_chars);

    plus_size_t end = src_len;
    while (end > start && plus_strrchr(trim_chars, src[end - 1])) {
      end--;
    }

    plus_size_t new_len = (end > start ? end - start : 0);

    result = malloc(new_len + 1);
    if (result != PLUS_NULL) {
      if (new_len > 0) {
        plus_strncpy(result, src + start, new_len);
      }
      result[new_len] = '\0';
    }
  }
  return result;
}
