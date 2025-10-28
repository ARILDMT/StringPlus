#include "string_plus.h"

char *plus_strcpy(char *dest, const char *src) {
  char *save = dest;
  while ((*dest++ = *src++) != '\0');
  return save;
}

char *plus_strcat(char *dest, const char *src) {
  char *rdest = dest;
  while (*dest) dest++;
  while ((*dest++ = *src++) != '\0');
  return rdest;
}

plus_size_t plus_strspn(const char *str1, const char *str2) {
  const char *p, *spanp;
  char c, sc;
  plus_size_t count = 0;

  for (p = str1;;) {
    c = *p++;
    spanp = str2;
    char flag = 1;
    do {
      if ((sc = *spanp++) == c) {
        count++;
        flag = 0;
      }
    } while (sc != 0 && flag);
    if (sc == 0) return count;
  }
}