#include "string_plus.h"

const char *plus_skip_whitespace(const char *str) {
  const char *result = str;
  while (isspace(*result)) result++;
  return result;
}
