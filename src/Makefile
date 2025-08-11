CMOCKA_DIR 			:= ./cmocka
CMOCKA_LIB_DIR 		:= $(CMOCKA_DIR)/build/src
CMOCKA_INCLUDE_DIR 	:= $(CMOCKA_DIR)/include

CC:=gcc
CFLAGS:=-Wall -Werror -Wextra -fPIE

all: main

test: add_test

cov: test_dependencies lcov.info coverage 

# Link the test binary with the CMocka library and coverage flags
add_test: add_test.o add.test.o
	$(CC) -o $@ $^ -L$(CMOCKA_LIB_DIR) -Wl,-rpath,$(CMOCKA_LIB_DIR) -lcmocka -fprofile-arcs -ftest-coverage 

# Generate the lcov.info file that the VS Code Coverage Gutters can use from the *.gcda files
lcov.info: add.test.gcda
	rm -f lcov.info
	lcov --capture --directory . --output-file lcov.info

# Generate html report from lcov.info file
coverage: lcov.info
	rm -rf coverage
	genhtml lcov.info --output-directory coverage

# Run the test binary to generate the .gcda files
add.test.gcda: add_test
	./add_test

# Create cmocka test object files
%_test.o: %_test.c
	$(CC) -o $@ -c $(CFLAGS) -I$(CMOCKA_INCLUDE_DIR) $^

# Create test object files with coverage flags
%.test.o: %.c
	# Compile the code we want code coverage on with -fprofile-arcs -ftest-coverage
	$(CC) -o $@ -c $(CFLAGS) -O0 -fprofile-arcs -ftest-coverage $^

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
	rm -f *.o *.a *.gcda *.gcno main add_test lcov.info
	rm -rf coverage

.PHONY: clean all test_dependencies test_run