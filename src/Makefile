COMP_FLAGS = -Wall -Werror -Wextra
STANDART = -std=c++17
CC = gcc $(COMP_FLAGS) $(STANDART) -pthread -lpthread
GCOVFLAGS = -fprofile-arcs -ftest-coverage
DEBUG = -ggdb
OUT = ../lib/

OS := $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -I /usr/local/include/gtest -L /usr/local/lib -lgtest -lgtest_main -lrt -lm -lsubunit -lstdc++
else
	CHECK_FLAGS = -lgtest -lgtest_main -lstdc++
endif

all: clean clang-format valgrind

rebuild: clean all

matrix.a:
	mkdir -p ../lib
	$(CC) -c matrix.cc  $(CHECK_FLAGS)
	ar rcs $(OUT)libmatrix.a *.o
	$(CC) -shared -o $(OUT)libmatrix.so *.o $(CHECK_FLAGS)

test: matrix.a
	$(CC) ../tests/matrix_test.cc -o test $(OUT)libmatrix.a $(CHECK_FLAGS) $(DEBUG)
	./test

gcov_report: clean matrix.a
	$(CC) $(GCOVFLAGS) ../tests/matrix_test.cc matrix.cc -o test $(CHECK_FLAGS) $(DEBUG)
	./test
	gcov *.cc
	lcov --capture --directory . --output-file test.info
	genhtml test.info --output-directory report
	open report/index.html

valgrind: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test

leak: test


clang-format:
	clang-format -n *.cc *.h
	clang-format -i *.cc *.h

clean:
	rm -rf *.o *.gcov *.gcda *.gcno *.txt *.a test* test.info report
