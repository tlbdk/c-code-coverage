CMOCKA_DIR 			:= ./cmocka
CMOCKA_LIB_DIR 		:= $(CMOCKA_DIR)/build/src
CMOCKA_INCLUDE_DIR 	:= $(CMOCKA_DIR)/include

CC:=gcc
CFLAGS:=-Wall -Werror -Wextra -fPIE

all: main

test: add_test

lcov: test_dependencies lcov.info lcov_coverage 
kcov: kcov_coverage

# Generate html report from lcov.info file
lcov_coverage: lcov.info
	genhtml lcov.info --output-directory lcov_coverage

# Generate the lcov.info file that the VS Code Coverage Gutters can use from the *.gcda files
lcov.info: add.test.gcda
	lcov --capture --directory . --output-file lcov.info

# Run the test binary to generate the .gcda files
%.test.gcda: %_test_lcov
	./$^

# Link the test binary with the CMocka library and lcov/gcov coverage flags
%_test_lcov: %_test.o %.lcov.o
	$(CC) -o $@ $^ -L$(CMOCKA_LIB_DIR) -Wl,-rpath,$(CMOCKA_LIB_DIR) -lcmocka -fprofile-arcs -ftest-coverage

# Compile the code we want code coverage on with -fprofile-arcs -ftest-coverage
%.lcov.o: %.c
	$(CC) -o $@ -c $(CFLAGS) -O0 -fprofile-arcs -ftest-coverage $^

kcov_coverage: add_test_kcov
	kcov --dump-summary coverage_kcov/ ./add_test_kcov

# Add debugging symbols for kcov
%_test_kcov: %_test.o %.kcov.o
	$(CC) -o $@ $^ -L$(CMOCKA_LIB_DIR) -Wl,-rpath,$(CMOCKA_LIB_DIR) -lcmocka -g

# Compile the code we want code coverage on with debugging symbols for kcov
%.kcov.o: %.c
	$(CC) -o $@ -c $(CFLAGS) -O0 -g $^

# Create cmocka test object files
%_test.o: %_test.c
	$(CC) -o $@ -c $(CFLAGS) -I$(CMOCKA_INCLUDE_DIR) $^

# Create object files
%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) -Os $^

main: main.o add.o
	$(CC) -o $@ $(CFLAGS) add.o $<

# Dependencies
test_dependencies: $(CMOCKA_LIB_DIR)

$(CMOCKA_LIB_DIR):
	curl -O https://cmocka.org/files/1.1/cmocka-1.1.8.tar.xz
	mkdir -p cmocka
	tar -xf cmocka-1.1.8.tar.xz -C cmocka --strip-components=1
	rm -f cmocka-1.1.8.tar.xz
	cd cmocka && mkdir build && cd build && cmake .. && make

clean:
	rm -f *.o *.a *.gcda *.gcno main add_test_lcov lcov.info add_test_kcov 
	rm -rf coverage_lcov coverage_kcov

# Don't delete intermediate .o files as we need them for debug on mac
.PRECIOUS: %_test.o %.lcov.o %.kcov.o

.PHONY: clean all test_dependencies test_run