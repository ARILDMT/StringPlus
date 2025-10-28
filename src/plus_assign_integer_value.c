#include "string_plus.h"

void plus_assign_integer_value(va_list *args, format_spec_t *spec,
                              long long value) {
  switch (spec->length) {
    case 'h':
      if (spec->specifier == 'u') {
        unsigned short *ptr = va_arg(*args, unsigned short *);
        if (ptr) *ptr = (unsigned short)value;
      } else {
        short *ptr = va_arg(*args, short *);
        if (ptr) *ptr = (short)value;
      }
      break;
    case 'l':
      if (spec->specifier == 'u') {
        unsigned long *ptr = va_arg(*args, unsigned long *);
        if (ptr) *ptr = (unsigned long)value;
      } else {
        long *ptr = va_arg(*args, long *);
        if (ptr) *ptr = (long)value;
      }
      break;
    default:
      if (spec->specifier == 'u') {
        unsigned int *ptr = va_arg(*args, unsigned int *);
        if (ptr) *ptr = (unsigned int)value;
      } else {
        int *ptr = va_arg(*args, int *);
        if (ptr) *ptr = (int)value;
      }
      break;
  }
}
