#include "string_plus.h"

int plus_char_to_digit(char c, int base) {
  int digit = -1;
  int result = -1;
  if (c >= '0' && c <= '9') {
    digit = c - '0';
  } else if (c >= 'a' && c <= 'z') {
    digit = c - 'a' + 10;
  } else if (c >= 'A' && c <= 'Z') {
    digit = c - 'A' + 10;
  }
  if (digit != -1 && digit < base) {
    result = digit;
  }
  return result;
}
