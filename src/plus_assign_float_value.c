#include "string_plus.h"

void plus_assign_float_value(va_list *args, format_spec_t *spec,
                            long double value) {
  switch (spec->length) {
    case 'L': {
      long double *ptr = va_arg(*args, long double *);
      if (ptr) *ptr = value;
      break;
    }
    case 'l': {
      double *ptr = va_arg(*args, double *);
      if (ptr) *ptr = (double)value;
      break;
    }
    default: {
      float *ptr = va_arg(*args, float *);
      if (ptr) *ptr = (float)value;
      break;
    }
  }
}
