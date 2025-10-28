#ifndef STRING_PLUS_H
#define STRING_PLUS_H

#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef PLUS_NULL
#define PLUS_NULL ((void *)0)
#endif

typedef unsigned long plus_size_t;

typedef struct {
  int suppress;
  int width;
  char length;
  char specifier;
} format_spec_t;

int plus_sscanf(const char *str, const char *format, ...);

// eldreday
int plus_handle_literal_match(const char **str_ptr, const char **fmt_ptr);
int plus_process_specifier(const char **str_ptr, const char **fmt_ptr,
                          va_list *args, int *successful_conversions,
                          const char *original_str);
const char *plus_parse_format_spec(const char *format, format_spec_t *spec);
const char *plus_skip_whitespace(const char *str);
void plus_assign_string_value(va_list *args, const char *start, int len);
const char *plus_scan_string(const char *str, format_spec_t *spec, va_list *args,
                            int *count);
void plus_assign_char_value(va_list *args, const char *str, int width);
const char *plus_scan_char(const char *str, format_spec_t *spec, va_list *args,
                          int *count);
void plus_assign_integer_value(va_list *args, format_spec_t *spec,
                              long long value);
const char *plus_scan_integer(const char *str, format_spec_t *spec,
                             va_list *args, int *count);
void plus_assign_float_value(va_list *args, format_spec_t *spec,
                            long double value);
const char *plus_scan_float(const char *str, format_spec_t *spec, va_list *args,
                           int *count);
void plus_assign_pointer_value(va_list *args, unsigned long long value);
const char *plus_scan_pointer(const char *str, format_spec_t *spec,
                             va_list *args, int *count);
int plus_char_to_digit(char c, int base);
long long plus_parse_integer(const char **str, int base, int width,
                            int *parsed_chars);
int plus_parse_sign(const char **ptr, int *chars_read, int max_width);
long double plus_parse_integer_part(const char **ptr, int *chars_read,
                                   int max_width, int *has_digits);
void plus_parse_fraction_part(const char **ptr, int *chars_read, int max_width,
                             long double *fraction, long double *divisor,
                             int *has_digits);
void plus_parse_exponent(const char **ptr, int *chars_read, int max_width,
                        long double *result);
long double plus_parse_float(const char **str, int width, int *parsed_chars);
void plus_process_percent(const char **str_ptr, const char **fmt_ptr,
                         va_list *args, int *successful_conversions,
                         int *continue_parsing, const char *str);

// mygeetoq
plus_size_t plus_strlen(const char *str);
char *plus_strncat(char *dest, const char *src, plus_size_t n);
int plus_strncmp(const char *str1, const char *str2, plus_size_t n);
char *plus_strncpy(char *dest, const char *src, plus_size_t n);
char *plus_strchr(const char *str, int c);
char *plus_strrchr(const char *str, int c);
plus_size_t plus_strcspn(const char *str1, const char *str2);
char *plus_strpbrk(const char *str1, const char *str2);
char *plus_strstr(const char *haystack, const char *needle);
char *plus_strerror(int errnum);
char *plus_strtok(char *str, const char *delim);

// fernaani
void *plus_memchr(const void *str, int c, plus_size_t n);
int plus_memcmp(const void *str1, const void *str2, plus_size_t n);
void *plus_memcpy(void *dest, const void *src, plus_size_t n);
void *plus_memset(void *str, int c, plus_size_t n);

// sprintf function
int plus_sprintf(char *str, const char *format, ...);

// special string functions
void *plus_to_upper(const char *str);
void *plus_to_lower(const char *str);
void *plus_insert(const char *src, const char *str, plus_size_t start_index);
void *plus_trim(const char *src, const char *trim_chars);

// utility functions
char *plus_strcpy(char *dest, const char *src);
char *plus_strcat(char *dest, const char *src);
plus_size_t plus_strspn(const char *str1, const char *str2);

#endif
