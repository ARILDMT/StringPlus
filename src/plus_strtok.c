#include "string_plus.h"

char *plus_strtok(char *str, const char *delim) {
  static char *last = PLUS_NULL;
  char *start = PLUS_NULL;

  if (str != PLUS_NULL) {
    last = str;
  } else if (last == PLUS_NULL) {
    return PLUS_NULL;
  }

  if (*last == '\0' || (*delim == '\0' && str == PLUS_NULL)) {
    start = PLUS_NULL;
  } else {
    char *curr_ch = last;
    while (*curr_ch != '\0' && plus_strchr(delim, *curr_ch)) {
      ++curr_ch;
    }

    if (*curr_ch == '\0') {
      start = PLUS_NULL;
    } else {
      start = curr_ch;
      while (*curr_ch && (plus_strchr(delim, *curr_ch) == PLUS_NULL)) {
        ++curr_ch;
      }

      if (*curr_ch == 0) {
        last = curr_ch;
      } else {
        *curr_ch = 0;
        last = curr_ch + 1;
      }
    }
  }

  return start;
}