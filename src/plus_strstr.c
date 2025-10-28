#include "string_plus.h"

char *plus_strstr(const char *haystack, const char *needle) {
  char *result = PLUS_NULL;
  int flag = 0;

  if (haystack == PLUS_NULL || needle == PLUS_NULL) {
    return result;
  }

  if (*needle == '\0') {
    return (char *)(haystack);
  }

  plus_size_t needle_len = plus_strlen(needle);
  plus_size_t haystack_len = plus_strlen(haystack);

  if (haystack_len < needle_len) {
    return result;
  }

  for (plus_size_t i = 0; i <= haystack_len - needle_len && flag == 0; i++) {
    plus_size_t j;
    int not_found = 0;
    for (j = 0; j < needle_len && not_found == 0; j++) {
      if (haystack[i + j] != needle[j]) {
        not_found = 1;
      }
    }
    if (j == needle_len) {
      result = (char *)(haystack + i);
      flag = 1;
    }
  }

  return result;
}
