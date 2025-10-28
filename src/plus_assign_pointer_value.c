#include "string_plus.h"

void plus_assign_pointer_value(va_list *args, unsigned long long value) {
  void **ptr = va_arg(*args, void **);
  if (ptr) *ptr = (void *)(uintptr_t)value;
}
