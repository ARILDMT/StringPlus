#include "plus_sprintf.h"

#define BUFFER_SIZE 1024

typedef struct {
  int minus;
  int plus;
  int space;
  int zero;
  int width;
  int precision;
  int is_precision_set;
  char length;
  char specifier;
} FormatFlags;

static void parse_flags(const char **format, FormatFlags *flags) {
  while (1) {
    switch (**format) {
      case '-':
        flags->minus = 1;
        break;
      case '+':
        flags->plus = 1;
        break;
      case ' ':
        flags->space = 1;
        break;
      case '0':
        flags->zero = 1;
        break;
      default:
        return;
    }
    (*format)++;
  }
}

static void parse_width(const char **format, va_list *args,
                        FormatFlags *flags) {
  if (**format == '*') {
    flags->width = va_arg(*args, int);
    (*format)++;
  } else {
    flags->width = 0;
    char flag = 1;
    while (**format >= '0' && **format <= '9' && flag) {
      if (flags->width > INT_MAX / 10) {
        flags->width = INT_MAX / 10;
        flag = 0;
      } else {
        flags->width = flags->width * 10 + (**format - '0');
        (*format)++;
      }
    }
  }
}

static void parse_precision_processing(const char **format,
                                       FormatFlags *flags) {
  char flag = 1;
  while (**format >= '0' && **format <= '9' && flag) {
    if (flags->precision > 100000) {
      while (**format >= '0' && **format <= '9') {
        (*format)++;
      }
      flag = 0;
    } else {
      flags->precision = flags->precision * 10 + (**format - '0');
      (*format)++;
    }
  }
}

static void parse_precision(const char **format, va_list *args,
                            FormatFlags *flags) {
  if (**format == '.') {
    (*format)++;
    flags->is_precision_set = 1;
    if (**format == '*') {
      flags->precision = va_arg(*args, int);
      (*format)++;
    } else {
      flags->precision = 0;
      parse_precision_processing(format, flags);
    }
  }
}

static void parse_length(const char **format, FormatFlags *flags) {
  if (**format == 'h' || **format == 'l' || **format == 'L') {
    flags->length = **format;
    (*format)++;
  }
}

static void parse_specifier(const char **format, FormatFlags *flags) {
  flags->specifier = **format;
  (*format)++;
}

static void parse_format(const char **format, va_list *args,
                         FormatFlags *flags) {
  parse_flags(format, flags);
  parse_width(format, args, flags);
  parse_precision(format, args, flags);
  parse_length(format, flags);
  parse_specifier(format, flags);
}

static int handle_char(char *buffer, va_list *args, FormatFlags *flags) {
  char c = (char)va_arg(*args, int);
  int len = 1;
  int padding = flags->width > len ? flags->width - len : 0;
  int pos = 0;

  if (!flags->minus && padding) {
    for (int i = 0; i < padding; i++) {
      buffer[pos++] = ' ';
    }
  }

  buffer[pos++] = c;

  if (flags->minus && padding) {
    for (int i = 0; i < padding; i++) {
      buffer[pos++] = ' ';
    }
  }

  return pos;
}

static int handle_string(char *buffer, va_list *args, FormatFlags *flags) {
  char *s = va_arg(*args, char *);
  if (s == PLUS_NULL) {
    s = "(null)";
  }
  int len = (int)plus_strlen(s);
  if (flags->is_precision_set && flags->precision < len) {
    len = flags->precision;
  }
  int padding = flags->width > len ? flags->width - len : 0;
  int pos = 0;

  if (!flags->minus && padding) {
    for (int i = 0; i < padding; i++) {
      buffer[pos++] = ' ';
    }
  }

  for (int i = 0; i < len; i++) {
    buffer[pos++] = s[i];
  }
  if (flags->minus && padding) {
    for (int i = 0; i < padding; i++) {
      buffer[pos++] = ' ';
    }
  }

  return pos;
}

static long int get_int_value(va_list *args, FormatFlags *flags) {
  long int num;
  if (flags->length == 'l') {
    num = va_arg(*args, long int);
  } else if (flags->length == 'h') {
    num = (short int)va_arg(*args, int);
  } else {
    num = va_arg(*args, int);
  }
  return num;
}

static int convert_int_to_str(long int num, char *num_str, FormatFlags *flags) {
  int i = 0;
  do {
    if (i >= BUFFER_SIZE - 1) break;
    num_str[i++] = '0' + (num % 10);
    num /= 10;
  } while (num > 0);

  if (flags->is_precision_set && flags->precision > i) {
    while (i < flags->precision && i < BUFFER_SIZE - 1) {
      num_str[i++] = '0';
    }
  }
  return i;
}

static int add_sign(char *buffer, int is_negative, FormatFlags *flags) {
  int pos = 0;
  if (is_negative) {
    buffer[pos++] = '-';
  } else if (flags->plus) {
    buffer[pos++] = '+';
  } else if (flags->space) {
    buffer[pos++] = ' ';
  }
  return pos;
}

static int handle_int(char *buffer, va_list *args, FormatFlags *flags) {
  long int num = get_int_value(args, flags);
  char num_str[BUFFER_SIZE];
  int is_negative = num < 0;
  if (is_negative) {
    num = -num;
  }

  int i = convert_int_to_str(num, num_str, flags);
  int len = i;
  if (is_negative || flags->plus || flags->space) {
    len++;
  }

  int padding = flags->width > len ? flags->width - len : 0;
  int pos = 0;

  if (!flags->minus && !flags->zero && padding) {
    for (int j = 0; j < padding; j++) {
      buffer[pos++] = ' ';
    }
  }

  pos += add_sign(buffer + pos, is_negative, flags);

  if (!flags->minus && flags->zero && padding) {
    for (int j = 0; j < padding; j++) {
      buffer[pos++] = '0';
    }
  }

  for (int j = i - 1; j >= 0; j--) {
    buffer[pos++] = num_str[j];
  }

  if (flags->minus && padding) {
    for (int j = 0; j < padding; j++) {
      buffer[pos++] = ' ';
    }
  }

  return pos;
}

static int handle_unsigned(char *buffer, va_list *args, FormatFlags *flags) {
  unsigned long int num;
  if (flags->length == 'l') {
    num = va_arg(*args, unsigned long int);
  } else if (flags->length == 'h') {
    num = (unsigned short int)va_arg(*args, unsigned int);
  } else {
    num = va_arg(*args, unsigned int);
  }

  char num_str[BUFFER_SIZE];
  int i = 0;
  do {
    num_str[i++] = '0' + (num % 10);
    num /= 10;
  } while (num > 0);

  if (flags->is_precision_set && flags->precision > i) {
    while (i < flags->precision) {
      num_str[i++] = '0';
    }
  }

  int len = i;
  int padding = flags->width > len ? flags->width - len : 0;
  int pos = 0;

  if (!flags->minus && !flags->zero && padding) {
    for (int j = 0; j < padding; j++) {
      buffer[pos++] = ' ';
    }
  }

  if (!flags->minus && flags->zero && padding) {
    for (int j = 0; j < padding; j++) {
      buffer[pos++] = '0';
    }
  }

  for (int j = i - 1; j >= 0; j--) {
    buffer[pos++] = num_str[j];
  }

  if (flags->minus && padding) {
    for (int j = 0; j < padding; j++) {
      buffer[pos++] = ' ';
    }
  }

  return pos;
}

static double get_float_value(va_list *args, FormatFlags *flags) {
  double num;
  if (flags->length == 'L') {
    num = va_arg(*args, long double);
  } else {
    num = va_arg(*args, double);
  }
  return num;
}

static int convert_int_part(long int int_part, char *num_str) {
  int i = 0;
  do {
    num_str[i++] = '0' + (int_part % 10);
    int_part /= 10;
  } while (int_part > 0);
  return i;
}

static int add_fractional_part(char *buffer, double fractional_part,
                               int precision) {
  int pos = 0;
  if (precision > 0) {
    buffer[pos++] = '.';
    for (int j = 0; j < precision; j++) {
      fractional_part *= 10;
      int digit = (int)fractional_part;
      buffer[pos++] = '0' + digit;
      fractional_part -= digit;
    }
  }
  return pos;
}

static void calculate_float_params(double num, int precision,
                                   long int *int_part,
                                   double *fractional_part) {
  *int_part = (long int)num;
  *fractional_part = num - *int_part;

  double round_factor = 0.5;
  for (int j = 0; j < precision; j++) {
    round_factor /= 10.0;
  }
  *fractional_part += round_factor;
}

static int add_float_padding(char *buffer, FormatFlags *flags, int padding,
                             int is_before_sign) {
  int pos = 0;
  if (is_before_sign && !flags->minus && !flags->zero && padding) {
    for (int j = 0; j < padding; j++) {
      buffer[pos++] = ' ';
    }
  } else if (!is_before_sign && !flags->minus && flags->zero && padding) {
    for (int j = 0; j < padding; j++) {
      buffer[pos++] = '0';
    }
  } else if (!is_before_sign && flags->minus && padding) {
    for (int j = 0; j < padding; j++) {
      buffer[pos++] = ' ';
    }
  }
  return pos;
}

static int handle_float(char *buffer, va_list *args, FormatFlags *flags) {
  double num = get_float_value(args, flags);
  int precision = flags->is_precision_set ? flags->precision : 6;
  char num_str[BUFFER_SIZE];
  int is_negative = num < 0;
  if (is_negative) {
    num = -num;
  }

  long int int_part;
  double fractional_part;
  calculate_float_params(num, precision, &int_part, &fractional_part);

  int int_len = convert_int_part(int_part, num_str);
  int total_len = int_len + precision + (precision > 0 ? 1 : 0);
  if (is_negative || flags->plus || flags->space) {
    total_len++;
  }

  int padding = flags->width > total_len ? flags->width - total_len : 0;
  int pos = 0;

  pos += add_float_padding(buffer + pos, flags, padding, 1);
  pos += add_sign(buffer + pos, is_negative, flags);
  pos += add_float_padding(buffer + pos, flags, padding, 0);

  for (int j = int_len - 1; j >= 0; j--) {
    buffer[pos++] = num_str[j];
  }

  pos += add_fractional_part(buffer + pos, fractional_part, precision);
  pos += add_float_padding(buffer + pos, flags, padding, 0);

  return pos;
}

static int handle_percent(char *buffer, FormatFlags *flags) {
  int len = 1;
  int padding = flags->width > len ? flags->width - len : 0;
  int pos = 0;

  if (!flags->minus && padding) {
    for (int i = 0; i < padding; i++) {
      buffer[pos++] = ' ';
    }
  }

  buffer[pos++] = '%';

  if (flags->minus && padding) {
    for (int i = 0; i < padding; i++) {
      buffer[pos++] = ' ';
    }
  }

  return pos;
}

int plus_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *start = str;
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
    } else {
      format++;
      FormatFlags flags = {0};
      parse_format(&format, &args, &flags);

      int written = 0;
      switch (flags.specifier) {
        case 'c':
          written = handle_char(str, &args, &flags);
          break;
        case 's':
          written = handle_string(str, &args, &flags);
          break;
        case 'd':
        case 'i':
          written = handle_int(str, &args, &flags);
          break;
        case 'u':
          written = handle_unsigned(str, &args, &flags);
          break;
        case 'f':
          written = handle_float(str, &args, &flags);
          break;
        case '%':
          written = handle_percent(str, &flags);
          break;
        default:
          break;
      }
      str += written;
    }
  }

  *str = '\0';
  va_end(args);
  return str - start;
}