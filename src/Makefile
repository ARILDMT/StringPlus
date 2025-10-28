CFLAGS = -Wall -Wextra -Werror -std=c11 -g
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	TEST_FLAGS = -lcheck -lm
	OPEN_CMD = open
	CC = gcc
	GCOV_CMD = gcov
else ifeq ($(UNAME_S), Linux)
	TEST_FLAGS = -lcheck -lm -lpthread
	OPEN_CMD = xdg-open
	CC = gcc
	GCOV_CMD = gcov
else
	TEST_FLAGS = -lcheck -lm -lpthread
	OPEN_CMD = start
	CC = gcc
	GCOV_CMD = gcov
endif

AR = ar
ARFLAGS = rcs

SOURCES = \
	plus_memchr.c \
	plus_memcmp.c \
	plus_memcpy.c \
	plus_memset.c \
	plus_strncat.c \
	plus_strchr.c \
	plus_strncmp.c \
	plus_strncpy.c \
	plus_strcspn.c \
	plus_strerror.c \
	plus_strlen.c \
	plus_strpbrk.c \
	plus_strrchr.c \
	plus_strstr.c \
	plus_strtok.c \
	plus_sprintf.c \
	plus_sscanf.c \
	plus_to_upper.c \
	plus_to_lower.c \
	plus_insert.c \
	plus_trim.c \
	plus_assign_char_value.c \
	plus_assign_float_value.c \
	plus_assign_integer_value.c \
	plus_assign_pointer_value.c \
	plus_assign_string_value.c \
	plus_char_to_digit.c \
	plus_handle_literal_match.c \
	plus_parse_exponent.c \
	plus_parse_float.c \
	plus_parse_format_spec.c \
	plus_parse_fraction_part.c \
	plus_parse_integer.c \
	plus_parse_integer_part.c \
	plus_parse_sign.c \
	plus_process_percent.c \
	plus_process_specifier.c \
	plus_scan_char.c \
	plus_scan_float.c \
	plus_scan_integer.c \
	plus_scan_pointer.c \
	plus_scan_string.c \
	plus_skip_whitespace.c \
	utils.c

OBJECTS = $(SOURCES:.c=.o)

TEST_SOURCES = test_string_plus.c
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

LIBRARY = string_plus.a

TEST_EXEC = test_string_plus
TEST_EXEC1 = test

.PHONY: all clean test gcov_report asan_test

all: string_plus.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

string_plus.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJECTS) $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(TEST_FLAGS)

gcov_report:
	@echo "Running tests with coverage flags"
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SOURCES) $(TEST_SOURCES) -o $(TEST_EXEC)_gcov $(TEST_FLAGS)
	-./$(TEST_EXEC)_gcov
	@echo "Generating coverage report"
	for file in $(SOURCES); do \
		base_name=$$(basename $$file .c); \
		if [ -f $(TEST_EXEC)_gcov-$$base_name.gcno ]; then \
			cp $(TEST_EXEC)_gcov-$$base_name.gcno $$base_name.gcno; \
		fi; \
		if [ -f $(TEST_EXEC)_gcov-$$base_name.gcda ]; then \
			cp $(TEST_EXEC)_gcov-$$base_name.gcda $$base_name.gcda; \
		fi; \
	done
	$(GCOV_CMD) $(SOURCES)
	lcov -t "string_plus" -o string_plus.info -c -d .
	genhtml -o report string_plus.info
	@echo "========================================"
	@echo "Coverage report successfully generated!"
	@echo "Open in browser: file://$(shell pwd)/report/index.html"
	@echo "========================================"
	@echo "Opening report in browser..."
	$(OPEN_CMD) report/index.html

clean:
	rm -f *.o *.a *.d *.gcno *.gcda *.gcov *.info $(TEST_EXEC) $(TEST_EXEC)_gcov
	rm -rf report