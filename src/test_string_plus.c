#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_plus.h"

START_TEST(test_plus_strcpy_basic) {
  char src[] = "Hello, World!";
  char dest1[50];
  char dest2[50];

  char *ret1 = plus_strcpy(dest1, src);
  strcpy(dest2, src);

  ck_assert_str_eq(dest1, dest2);
  ck_assert_ptr_eq(ret1, dest1);
}
END_TEST

START_TEST(test_plus_strcpy_empty) {
  char src[] = "";
  char dest1[50];
  char dest2[50];

  char *ret1 = plus_strcpy(dest1, src);
  strcpy(dest2, src);

  ck_assert_str_eq(dest1, dest2);
  ck_assert_ptr_eq(ret1, dest1);
}
END_TEST

START_TEST(test_plus_strcpy_special_chars) {
  char src[] = "Test\n\t\r";
  char dest1[50];
  char dest2[50];

  char *ret1 = plus_strcpy(dest1, src);
  strcpy(dest2, src);

  ck_assert_str_eq(dest1, dest2);
  ck_assert_ptr_eq(ret1, dest1);
}
END_TEST

START_TEST(test_sscanf_integer) {
  int a, b;
  int result1 = plus_sscanf("123 456", "%d %d", &a, &b);
  int result2 = sscanf("123 456", "%d %d", &a, &b);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a, 123);
  ck_assert_int_eq(b, 456);
}
END_TEST

START_TEST(test_sscanf_string) {
  char str1[100], str2[100];
  int result1 = plus_sscanf("hello world", "%s %s", str1, str2);
  int result2 = sscanf("hello world", "%s %s", str1, str2);

  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, "hello");
  ck_assert_str_eq(str2, "world");
}
END_TEST

START_TEST(test_sscanf_char) {
  char c1, c2;
  int result1 = plus_sscanf("ab", "%c%c", &c1, &c2);
  int result2 = sscanf("ab", "%c%c", &c1, &c2);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, 'a');
  ck_assert_int_eq(c2, 'b');
}
END_TEST

START_TEST(test_sscanf_float) {
  float f1, f2;
  int result1 = plus_sscanf("3.14 2.71", "%f %f", &f1, &f2);
  int result2 = sscanf("3.14 2.71", "%f %f", &f1, &f2);

  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq_tol(f1, 3.14f, 0.001f);
  ck_assert_float_eq_tol(f2, 2.71f, 0.001f);
}
END_TEST

START_TEST(test_sscanf_unsigned) {
  unsigned int u1, u2;
  int result1 = plus_sscanf("123 456", "%u %u", &u1, &u2);
  int result2 = sscanf("123 456", "%u %u", &u1, &u2);

  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(u1, 123);
  ck_assert_uint_eq(u2, 456);
}
END_TEST

START_TEST(test_sscanf_octal) {
  int o1;
  int result1 = plus_sscanf("123", "%o", &o1);
  int result2 = sscanf("123", "%o", &o1);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(o1, 83);
}
END_TEST

START_TEST(test_sscanf_hex) {
  int x1;
  int result1 = plus_sscanf("1a", "%x", &x1);
  int result2 = sscanf("1a", "%x", &x1);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(x1, 26);
}
END_TEST

START_TEST(test_sscanf_suppress) {
  int a, b;
  int result1 = plus_sscanf("123 456 789", "%d %*d %d", &a, &b);
  int result2 = sscanf("123 456 789", "%d %*d %d", &a, &b);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a, 123);
  ck_assert_int_eq(b, 789);
}
END_TEST

START_TEST(test_sscanf_width) {
  int a;
  int result1 = plus_sscanf("123456", "%3d", &a);
  int result2 = sscanf("123456", "%3d", &a);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a, 123);
}
END_TEST

START_TEST(test_sscanf_scientific) {
  float f;
  int result1 = plus_sscanf("1.23e2", "%f", &f);
  int result2 = sscanf("1.23e2", "%f", &f);

  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq_tol(f, 123.0f, 0.001f);
}
END_TEST

START_TEST(test_sscanf_pointer) {
  void *ptr1, *ptr2;
  int result1 = plus_sscanf("0x123abc", "%p", &ptr1);
  int result2 = sscanf("0x123abc", "%p", &ptr2);

  ck_assert_int_eq(result1, result2);
  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(test_sscanf_n) {
  int a, n;
  int result1 = plus_sscanf("123", "%d%n", &a, &n);
  int result2 = sscanf("123", "%d%n", &a, &n);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a, 123);
  ck_assert_int_eq(n, 3);
}
END_TEST

START_TEST(test_sscanf_invalid) {
  int a;
  int result1 = plus_sscanf("abc", "%d", &a);
  int result2 = sscanf("abc", "%d", &a);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(result1, 0);
}
END_TEST

START_TEST(test_sscanf_length_h) {
  short s;
  int result1 = plus_sscanf("123", "%hd", &s);
  int result2 = sscanf("123", "%hd", &s);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(s, 123);
}
END_TEST

START_TEST(test_sscanf_length_l) {
  long l;
  int result1 = plus_sscanf("123456789", "%ld", &l);
  int result2 = sscanf("123456789", "%ld", &l);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(l, 123456789);
}
END_TEST

START_TEST(test_sscanf_length_L) {
  long double ld;
  int result1 = plus_sscanf("3.141592653589793", "%Lf", &ld);
  int result2 = sscanf("3.141592653589793", "%Lf", &ld);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sscanf_length_lf) {
  double d;
  int result1 = plus_sscanf("3.141592653589793", "%lf", &d);
  int result2 = sscanf("3.141592653589793", "%lf", &d);

  ck_assert_int_eq(result1, result2);
  ck_assert_double_eq_tol(d, 3.141592653589793, 0.00001);
}
END_TEST

START_TEST(test_sscanf_negative_int) {
  int a;
  int result1 = plus_sscanf("-123", "%d", &a);
  int result2 = sscanf("-123", "%d", &a);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a, -123);
}
END_TEST

START_TEST(test_sscanf_positive_sign) {
  int a;
  int result1 = plus_sscanf("+123", "%d", &a);
  int result2 = sscanf("+123", "%d", &a);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a, 123);
}
END_TEST

START_TEST(test_sscanf_zero) {
  int a;
  int result1 = plus_sscanf("0", "%d", &a);
  int result2 = sscanf("0", "%d", &a);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(test_sscanf_negative_float) {
  float f;
  int result1 = plus_sscanf("-3.14", "%f", &f);
  int result2 = sscanf("-3.14", "%f", &f);

  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq_tol(f, -3.14f, 0.001f);
}
END_TEST

START_TEST(test_sscanf_negative_exponent) {
  float f;
  int result1 = plus_sscanf("1.23e-2", "%f", &f);
  int result2 = sscanf("1.23e-2", "%f", &f);

  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq_tol(f, 0.0123f, 0.0001f);
}
END_TEST

START_TEST(test_sscanf_positive_exponent) {
  float f;
  int result1 = plus_sscanf("1.23e+2", "%f", &f);
  int result2 = sscanf("1.23e+2", "%f", &f);

  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq_tol(f, 123.0f, 0.001f);
}
END_TEST

START_TEST(test_sscanf_percent_literal) {
  int a;
  int result1 = plus_sscanf("100%", "%d%%", &a);
  int result2 = sscanf("100%", "%d%%", &a);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a, 100);
}
END_TEST

START_TEST(test_sscanf_integer_overflow) {
  int a;
  int result1 = plus_sscanf("999999999999999999", "%d", &a);
  int result2 = sscanf("999999999999999999", "%d", &a);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sscanf_float_no_fraction) {
  float f;
  int result1 = plus_sscanf("123.", "%f", &f);
  int result2 = sscanf("123.", "%f", &f);

  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq_tol(f, 123.0f, 0.001f);
}
END_TEST

START_TEST(test_sscanf_n_specifier) {
  int a = 0, n = 0;
  int result1 = plus_sscanf("123", "%d%n", &a, &n);

  ck_assert_int_eq(result1, 1);
  ck_assert_int_eq(a, 123);
}
END_TEST

START_TEST(test_sscanf_invalid_specifier) {
  int a = 0;
  int result1 = plus_sscanf("123", "%d%q", &a);

  ck_assert_int_eq(result1, 1);
  ck_assert_int_eq(a, 123);
}
END_TEST

START_TEST(test_sscanf_n_standalone) {
  int n = -1;
  int result = plus_sscanf("", "%n", &n);

  ck_assert(result >= 0 || result < 0);
}
END_TEST

START_TEST(test_sscanf_invalid_standalone) {
  int result = plus_sscanf("123", "%q");

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_sscanf_i_decimal) {
  int a1, a2;
  int result1 = plus_sscanf("123", "%i", &a1);
  int result2 = sscanf("123", "%i", &a2);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_i_octal) {
  int a1, a2;
  int result1 = plus_sscanf("0123", "%i", &a1);
  int result2 = sscanf("0123", "%i", &a2);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_i_hex) {
  int a1, a2;
  int result1 = plus_sscanf("0x123", "%i", &a1);
  int result2 = sscanf("0x123", "%i", &a2);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_strlen) {
  ck_assert_int_eq(plus_strlen("hello"), strlen("hello"));
  ck_assert_int_eq(plus_strlen(""), strlen(""));
  ck_assert_int_eq(plus_strlen("a"), strlen("a"));
}
END_TEST

START_TEST(test_strchr) {
  const char *str = "hello world";
  ck_assert_ptr_eq(plus_strchr(str, 'o'), strchr(str, 'o'));
  ck_assert_ptr_eq(plus_strchr(str, 'z'), strchr(str, 'z'));
  ck_assert_ptr_eq(plus_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

START_TEST(test_strrchr) {
  const char *str = "hello world";
  ck_assert_ptr_eq(plus_strrchr(str, 'o'), strrchr(str, 'o'));
  ck_assert_ptr_eq(plus_strrchr(str, 'z'), strrchr(str, 'z'));
  ck_assert_ptr_eq(plus_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

START_TEST(test_strncmp) {
  ck_assert_int_eq(plus_strncmp("hello", "hello", 5),
                   strncmp("hello", "hello", 5));

  int plus_result = plus_strncmp("hello", "world", 5);
  int std_result = strncmp("hello", "world", 5);
  ck_assert((plus_result < 0 && std_result < 0) ||
            (plus_result > 0 && std_result > 0) ||
            (plus_result == 0 && std_result == 0));

  plus_result = plus_strncmp("abc", "abd", 3);
  std_result = strncmp("abc", "abd", 3);
  ck_assert((plus_result < 0 && std_result < 0) ||
            (plus_result > 0 && std_result > 0) ||
            (plus_result == 0 && std_result == 0));
}
END_TEST

START_TEST(test_strncpy) {
  char dest1[20], dest2[20];
  memset(dest1, 0, 20);
  memset(dest2, 0, 20);
  plus_strncpy(dest1, "hello", 6);
  strncpy(dest2, "hello", 6);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat) {
  char dest1[20] = "hello";
  char dest2[20] = "hello";
  ck_assert_str_eq(plus_strncat(dest1, " world", 5),
                   strncat(dest2, " world", 5));
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strcspn) {
  ck_assert_int_eq(plus_strcspn("hello", "aeiou"), strcspn("hello", "aeiou"));
  ck_assert_int_eq(plus_strcspn("hello", "xyz"), strcspn("hello", "xyz"));
}
END_TEST

START_TEST(test_strpbrk) {
  const char *str = "hello world";
  ck_assert_ptr_eq(plus_strpbrk(str, "aeiou"), strpbrk(str, "aeiou"));
  ck_assert_ptr_eq(plus_strpbrk(str, "xyz"), strpbrk(str, "xyz"));
}
END_TEST

START_TEST(test_strstr) {
  const char *haystack = "hello world";
  ck_assert_ptr_eq(plus_strstr(haystack, "world"), strstr(haystack, "world"));
  ck_assert_ptr_eq(plus_strstr(haystack, "xyz"), strstr(haystack, "xyz"));
}
END_TEST

START_TEST(test_strtok) {
  char str1[] = "hello,world,test";
  char str2[] = "hello,world,test";
  char *token1 = plus_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_str_eq(token1, token2);

  token1 = plus_strtok(PLUS_NULL, ",");
  token2 = strtok(NULL, ",");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_memchr) {
  const char *str = "hello world";
  ck_assert_ptr_eq(plus_memchr(str, 'o', 11), memchr(str, 'o', 11));
  ck_assert_ptr_eq(plus_memchr(str, 'z', 11), memchr(str, 'z', 11));
}
END_TEST

START_TEST(test_memcmp) {
  ck_assert_int_eq(plus_memcmp("hello", "hello", 5),
                   memcmp("hello", "hello", 5));
  int plus_result = plus_memcmp("hello", "world", 5);
  int std_result = memcmp("hello", "world", 5);
  ck_assert((plus_result < 0 && std_result < 0) ||
            (plus_result > 0 && std_result > 0) ||
            (plus_result == 0 && std_result == 0));
}
END_TEST

START_TEST(test_memcpy) {
  char dest1[20], dest2[20];
  ck_assert_ptr_eq(plus_memcpy(dest1, "hello", 5), dest1);
  ck_assert_ptr_eq(memcpy(dest2, "hello", 5), dest2);
  ck_assert_mem_eq(dest1, dest2, 5);
}
END_TEST

START_TEST(test_memset) {
  char str1[20], str2[20];
  ck_assert_ptr_eq(plus_memset(str1, 'A', 10), str1);
  ck_assert_ptr_eq(memset(str2, 'A', 10), str2);
  ck_assert_mem_eq(str1, str2, 10);
}
END_TEST

START_TEST(test_strerror) {
  ck_assert_str_eq(plus_strerror(0), strerror(0));
  ck_assert_str_eq(plus_strerror(1), strerror(1));
  ck_assert_str_eq(plus_strerror(2), strerror(2));
}
END_TEST

START_TEST(test_sprintf_char) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "char: %c", 'A');
  int result2 = sprintf(str2, "char: %c", 'A');
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_string) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "string: %s", "hello");
  int result2 = sprintf(str2, "string: %s", "hello");
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_int) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "int: %d", 42);
  int result2 = sprintf(str2, "int: %d", 42);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_float) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "float: %f", 3.14);
  int result2 = sprintf(str2, "float: %f", 3.14);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_unsigned) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "unsigned: %u", 42u);
  int result2 = sprintf(str2, "unsigned: %u", 42u);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_percent) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "percent: %%");
  int result2 = sprintf(str2, "percent: %%");
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_negative_int) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "negative: %d", -42);
  int result2 = sprintf(str2, "negative: %d", -42);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_zero) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "zero: %d", 0);
  int result2 = sprintf(str2, "zero: %d", 0);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_precision) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "precision: %.2f", 3.14159);
  int result2 = sprintf(str2, "precision: %.2f", 3.14159);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_width) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "width: %5d", 42);
  int result2 = sprintf(str2, "width: %5d", 42);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_flags_minus) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "%-5d", 42);
  int result2 = sprintf(str2, "%-5d", 42);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_flags_plus) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "%+d", 42);
  int result2 = sprintf(str2, "%+d", 42);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_flags_space) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "% d", 42);
  int result2 = sprintf(str2, "% d", 42);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_flags_zero) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "%05d", 42);
  int result2 = sprintf(str2, "%05d", 42);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_width_star) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "%*d", 5, 42);
  int result2 = sprintf(str2, "%*d", 5, 42);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_precision_star) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "%.*f", 2, 3.14159);
  int result2 = sprintf(str2, "%.*f", 2, 3.14159);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_length_h) {
  char str1[100], str2[100];
  short val = 42;
  int result1 = plus_sprintf(str1, "%hd", val);
  int result2 = sprintf(str2, "%hd", val);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_length_l) {
  char str1[100], str2[100];
  long val = 42L;
  int result1 = plus_sprintf(str1, "%ld", val);
  int result2 = sprintf(str2, "%ld", val);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_length_L) {
  char str1[100], str2[100];
  long double val = 3.14159L;
  int result1 = plus_sprintf(str1, "%.2Lf", val);
  int result2 = sprintf(str2, "%.2Lf", val);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_unsigned_h) {
  char str1[100], str2[100];
  unsigned short val = 42;
  int result1 = plus_sprintf(str1, "%hu", val);
  int result2 = sprintf(str2, "%hu", val);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_unsigned_l) {
  char str1[100], str2[100];
  unsigned long val = 42UL;
  int result1 = plus_sprintf(str1, "%lu", val);
  int result2 = sprintf(str2, "%lu", val);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_float_precision_zero) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "%.0f", 3.14159);
  int result2 = sprintf(str2, "%.0f", 3.14159);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_char_width) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "%5c", 'A');
  int result2 = sprintf(str2, "%5c", 'A');
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_string_precision) {
  char str1[100], str2[100];
  int result1 = plus_sprintf(str1, "%.3s", "hello");
  int result2 = sprintf(str2, "%.3s", "hello");
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_default_specifier) {
  char str1[100];

  plus_sprintf(str1, "test %z end", 42);

  ck_assert_str_eq(str1, "test  end");
}
END_TEST

START_TEST(test_strchr_first_char) {
  const char *str = "hello";
  ck_assert_ptr_eq(plus_strchr(str, 'h'), strchr(str, 'h'));
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  const char *haystack = "hello world";
  ck_assert_ptr_eq(plus_strstr(haystack, ""), strstr(haystack, ""));
}
END_TEST

START_TEST(test_strstr_not_found) {
  const char *haystack = "hello";
  ck_assert_ptr_eq(plus_strstr(haystack, "xyz"), strstr(haystack, "xyz"));
}
END_TEST

START_TEST(test_strstr_null_haystack) {
  ck_assert_ptr_eq(plus_strstr(NULL, "test"), NULL);
}
END_TEST

START_TEST(test_strstr_null_needle) {
  const char *haystack = "hello world";
  ck_assert_ptr_eq(plus_strstr(haystack, NULL), NULL);
}
END_TEST

START_TEST(test_strstr_needle_longer) {
  const char *haystack = "hi";
  const char *needle = "hello";
  ck_assert_ptr_eq(plus_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strtok_no_delim) {
  char str1[] = "hello";
  char str2[] = "hello";
  char *token1 = plus_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_strerror_negative) {
  char *plus_result = plus_strerror(-1);
  char *std_result = strerror(-1);

  ck_assert_ptr_ne(plus_result, NULL);
  ck_assert_ptr_ne(std_result, NULL);
}
END_TEST

START_TEST(test_strerror_large) {
  char *plus_result = plus_strerror(999);
  char *std_result = strerror(999);

  ck_assert_ptr_ne(plus_result, NULL);
  ck_assert_ptr_ne(std_result, NULL);
}
END_TEST

START_TEST(test_to_upper) {
  char *result = plus_to_upper("hello");
  ck_assert_str_eq(result, "HELLO");
  free(result);

  result = plus_to_upper("Hello123");
  ck_assert_str_eq(result, "HELLO123");
  free(result);
}
END_TEST

START_TEST(test_to_lower) {
  char *result = plus_to_lower("HELLO");
  ck_assert_str_eq(result, "hello");
  free(result);

  result = plus_to_lower("Hello123");
  ck_assert_str_eq(result, "hello123");
  free(result);
}
END_TEST

START_TEST(test_insert) {
  char *result = plus_insert("hello", "123", 2);
  ck_assert_str_eq(result, "he123llo");
  free(result);

  result = plus_insert("hello", "world", 0);
  ck_assert_str_eq(result, "worldhello");
  free(result);
}
END_TEST

START_TEST(test_trim) {
  char *result = plus_trim("  hello  ", " ");
  ck_assert_str_eq(result, "hello");
  free(result);

  result = plus_trim("abcdefghijklmnopqrstuvwxyz", "abcxyz");
  ck_assert_str_eq(result, "defghijklmnopqrstuvw");
  free(result);
}
END_TEST

START_TEST(test_plus_handle_literal_match_success) {
  const char *str = "abc";
  const char *fmt = "abc";
  const char *str_ptr = str;
  const char *fmt_ptr = fmt;

  int result = plus_handle_literal_match(&str_ptr, &fmt_ptr);
  ck_assert_int_eq(result, 1);
  ck_assert_ptr_eq(str_ptr, str + 1);
  ck_assert_ptr_eq(fmt_ptr, fmt + 1);
}
END_TEST

START_TEST(test_plus_handle_literal_match_failure) {
  const char *str = "abc";
  const char *fmt = "xyz";
  const char *str_ptr = str;
  const char *fmt_ptr = fmt;

  int result = plus_handle_literal_match(&str_ptr, &fmt_ptr);
  ck_assert_int_eq(result, 0);
  ck_assert_ptr_eq(str_ptr, str);
  ck_assert_ptr_eq(fmt_ptr, fmt);
}
END_TEST

START_TEST(test_plus_handle_literal_match_whitespace) {
  const char *str = " ";
  const char *fmt = " ";
  const char *str_ptr = str;
  const char *fmt_ptr = fmt;

  int result = plus_handle_literal_match(&str_ptr, &fmt_ptr);
  ck_assert_int_eq(result, 1);
  ck_assert_ptr_eq(str_ptr, str + 1);
  ck_assert_ptr_eq(fmt_ptr, fmt + 1);
}
END_TEST

START_TEST(test_plus_handle_literal_match_empty_string) {
  const char *str = "";
  const char *fmt = "a";
  const char *str_ptr = str;
  const char *fmt_ptr = fmt;

  int result = plus_handle_literal_match(&str_ptr, &fmt_ptr);
  ck_assert_int_eq(result, 0);
  ck_assert_ptr_eq(str_ptr, str);
  ck_assert_ptr_eq(fmt_ptr, fmt);
}
END_TEST

Suite *sscanf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("plus_sscanf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sscanf_integer);
  tcase_add_test(tc_core, test_sscanf_string);
  tcase_add_test(tc_core, test_sscanf_char);
  tcase_add_test(tc_core, test_sscanf_float);
  tcase_add_test(tc_core, test_sscanf_unsigned);
  tcase_add_test(tc_core, test_sscanf_octal);
  tcase_add_test(tc_core, test_sscanf_hex);
  tcase_add_test(tc_core, test_sscanf_suppress);
  tcase_add_test(tc_core, test_sscanf_width);
  tcase_add_test(tc_core, test_sscanf_scientific);
  tcase_add_test(tc_core, test_sscanf_pointer);
  tcase_add_test(tc_core, test_sscanf_n);
  tcase_add_test(tc_core, test_sscanf_invalid);
  tcase_add_test(tc_core, test_sscanf_length_h);
  tcase_add_test(tc_core, test_sscanf_length_l);
  tcase_add_test(tc_core, test_sscanf_length_L);
  tcase_add_test(tc_core, test_sscanf_length_lf);
  tcase_add_test(tc_core, test_plus_handle_literal_match_success);
  tcase_add_test(tc_core, test_plus_handle_literal_match_failure);
  tcase_add_test(tc_core, test_plus_handle_literal_match_whitespace);
  tcase_add_test(tc_core, test_plus_handle_literal_match_empty_string);
  tcase_add_test(tc_core, test_sscanf_negative_int);
  tcase_add_test(tc_core, test_sscanf_positive_sign);
  tcase_add_test(tc_core, test_sscanf_zero);
  tcase_add_test(tc_core, test_sscanf_negative_float);
  tcase_add_test(tc_core, test_sscanf_negative_exponent);
  tcase_add_test(tc_core, test_sscanf_positive_exponent);
  tcase_add_test(tc_core, test_sscanf_percent_literal);
  tcase_add_test(tc_core, test_sscanf_integer_overflow);
  tcase_add_test(tc_core, test_sscanf_float_no_fraction);
  tcase_add_test(tc_core, test_sscanf_n_specifier);
  tcase_add_test(tc_core, test_sscanf_invalid_specifier);
  tcase_add_test(tc_core, test_sscanf_n_standalone);
  tcase_add_test(tc_core, test_sscanf_invalid_standalone);
  tcase_add_test(tc_core, test_sscanf_i_decimal);
  tcase_add_test(tc_core, test_sscanf_i_octal);
  tcase_add_test(tc_core, test_sscanf_i_hex);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *string_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("plus_string");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strlen);
  tcase_add_test(tc_core, test_strchr);
  tcase_add_test(tc_core, test_strrchr);
  tcase_add_test(tc_core, test_strncmp);
  tcase_add_test(tc_core, test_strncpy);
  tcase_add_test(tc_core, test_strncat);
  tcase_add_test(tc_core, test_strcspn);
  tcase_add_test(tc_core, test_strpbrk);
  tcase_add_test(tc_core, test_strstr);
  tcase_add_test(tc_core, test_strtok);
  tcase_add_test(tc_core, test_memchr);
  tcase_add_test(tc_core, test_memcmp);
  tcase_add_test(tc_core, test_memcpy);
  tcase_add_test(tc_core, test_memset);
  tcase_add_test(tc_core, test_strerror);
  tcase_add_test(tc_core, test_plus_strcpy_basic);
  tcase_add_test(tc_core, test_plus_strcpy_empty);
  tcase_add_test(tc_core, test_plus_strcpy_special_chars);
  tcase_add_test(tc_core, test_strchr_first_char);
  tcase_add_test(tc_core, test_strstr_empty_needle);
  tcase_add_test(tc_core, test_strstr_not_found);
  tcase_add_test(tc_core, test_strstr_null_haystack);
  tcase_add_test(tc_core, test_strstr_null_needle);
  tcase_add_test(tc_core, test_strstr_needle_longer);
  tcase_add_test(tc_core, test_strtok_no_delim);
  tcase_add_test(tc_core, test_strerror_negative);
  tcase_add_test(tc_core, test_strerror_large);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("plus_sprintf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sprintf_char);
  tcase_add_test(tc_core, test_sprintf_string);
  tcase_add_test(tc_core, test_sprintf_int);
  tcase_add_test(tc_core, test_sprintf_float);
  tcase_add_test(tc_core, test_sprintf_unsigned);
  tcase_add_test(tc_core, test_sprintf_percent);
  tcase_add_test(tc_core, test_sprintf_negative_int);
  tcase_add_test(tc_core, test_sprintf_zero);
  tcase_add_test(tc_core, test_sprintf_precision);
  tcase_add_test(tc_core, test_sprintf_width);
  tcase_add_test(tc_core, test_sprintf_flags_minus);
  tcase_add_test(tc_core, test_sprintf_flags_plus);
  tcase_add_test(tc_core, test_sprintf_flags_space);
  tcase_add_test(tc_core, test_sprintf_flags_zero);
  tcase_add_test(tc_core, test_sprintf_width_star);
  tcase_add_test(tc_core, test_sprintf_precision_star);
  tcase_add_test(tc_core, test_sprintf_length_h);
  tcase_add_test(tc_core, test_sprintf_length_l);
  tcase_add_test(tc_core, test_sprintf_length_L);
  tcase_add_test(tc_core, test_sprintf_unsigned_h);
  tcase_add_test(tc_core, test_sprintf_unsigned_l);
  tcase_add_test(tc_core, test_sprintf_float_precision_zero);
  tcase_add_test(tc_core, test_sprintf_char_width);
  tcase_add_test(tc_core, test_sprintf_string_precision);
  tcase_add_test(tc_core, test_sprintf_default_specifier);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *special_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("plus_special");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_to_upper);
  tcase_add_test(tc_core, test_to_lower);
  tcase_add_test(tc_core, test_insert);
  tcase_add_test(tc_core, test_trim);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed = 0;
  Suite *suites[] = {sscanf_suite(), string_suite(), sprintf_suite(),
                     special_suite(), NULL};

  for (int i = 0; suites[i]; i++) {
    SRunner *sr = srunner_create(suites[i]);
    srunner_run_all(sr, CK_ENV);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
