#include <limits.h>

#include "string_plus.h"

long long plus_parse_integer(const char **str, int base, int width,
                            int *parsed_chars) {
  const char *ptr = *str;
  long long result = 0;
  int sign = 1;
  int chars_read = 0;
  int max_width = width > 0 ? width : INT_MAX;
  long long final_result = 0;
  char flag = 1;
  if (*ptr == '-') {
    sign = -1;
    ptr++;
    chars_read++;
  } else if (*ptr == '+') {
    ptr++;
    chars_read++;
  }
  if (base == 16 && chars_read < max_width - 1 && ptr[0] == '0' &&
      (ptr[1] == 'x' || ptr[1] == 'X')) {
    ptr += 2;
    chars_read += 2;
  }
  while (chars_read < max_width && *ptr && flag) {
    int digit = plus_char_to_digit(*ptr, base);
    if (digit == -1) flag = 0;

    if (result > LLONG_MAX / base) {
      flag = 0;
    } else if (flag) {
      result = result * base + digit;
      ptr++;
      chars_read++;
    }
  }
  if (chars_read == 0 ||
      (chars_read == 1 && (*(*str) == '+' || *(*str) == '-'))) {
    *parsed_chars = 0;
    final_result = 0;
  } else {
    *str = ptr;
    *parsed_chars = chars_read;
    final_result = result * sign;
  }
  return final_result;
}