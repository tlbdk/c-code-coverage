CMOCKA_DIR 			:= ./cmocka
CMOCKA_LIB_DIR 		:= $(CMOCKA_DIR)/build/src
CMOCKA_INCLUDE_DIR 	:= $(CMOCKA_DIR)/include

CC:=gcc
CFLAGS:=-Wall -Werror -Wextra -Os -fPIE -mmacosx-version-min=15.60 
LD:=ld
LDFLAGS:=-r
LPATH:=-L.


all: main

test: add_test

cov: lcov.info coverage

# Link the test binary with the CMocka library and coverage flags
add_test: add_test.o add.test.o	
	$(CC) -o $@ $(CFLAGS) -L$(CMOCKA_LIB_DIR) -lcmocka -Wl,-rpath,$(CMOCKA_LIB_DIR) -fprofile-arcs -ftest-coverage $^

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
	$(CC) -o $@ -c $(CFLAGS) -fprofile-arcs -ftest-coverage $^

# Create object files
%.o: %.c
	# Compile the code we want code coverage on with -fprofile-arcs -ftest-coverage
	$(CC) -o $@ -c $(CFLAGS) $^

main: main.o add.o
	$(CC) -o $@ $(CFLAGS) add.o $<

# Dependencies
test_dependencies: $(CMOCKA_LIB_DIR)/libcmocka.dylib

$(CMOCKA_LIB_DIR)/libcmocka.dylib:
	curl -O https://cmocka.org/files/1.1/cmocka-1.1.8.tar.xz
	tar -xf cmocka-1.1.8.tar.xz
	rm -f cmocka-1.1.8.tar.xz
	cd cmocka-1.1.8 && mkdir build && cd build && cmake .. && make
	mv cmocka-1.1.8 cmocka

clean:
	rm -f *.o *.a *.gcda *.gcno main add_test lcov.info
	rm -rf coverage

.PHONY: clean all test_dependencies test_run