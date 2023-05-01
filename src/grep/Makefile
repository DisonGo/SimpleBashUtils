SHELL := /bin/bash

Flags 		= -Werror -Wall -Wextra
gcc 		= gcc $(Flags)
cmnPath		= ../common/
cmn			= $(cmnPath)utils.c $(cmnPath)flagReader.c $(cmnPath)vector/types/*.c
OS 			:= $(shell uname -s)
clang_path	= ../../materials/build/scripts/

ifeq ($(OS), Darwin)
 gcc += -D OS_MAC
endif
ifeq ($(OS), Linux)
 gcc += -D OS_LINUX
endif

all: clean s21_grep
clear:
	clear
clean: clean_testing
	rm -rf ./tests/s21_grep ./tests/*.out s21_grep *.out .clang-format
clean_testing:
	rm -rf ./tests/*.c ./tests/*.h ./tests/Make* ./tests/s21_grep
testing: clear all
	cp s21_grep s21_grep.c s21_grep.h Makefile ./tests
	cd ./tests; chmod u=rwx test_func_grep.sh ;./test_func_grep.sh
	make clean_testing
testing_l: clear all
	cp s21_grep s21_grep.c s21_grep.h Makefile ./tests
	cd ./tests; chmod u=rwx test_ERROR_VALGRIND.sh ;./test_ERROR_VALGRIND.sh
	make clean_testing
clang:
	cp $(clang_path).clang-format ./
	clang-format -n *.c *.h
clang_replace:
	cp $(clang_path).clang-format ./
	clang-format -i *.c *.h
s21_grep:
	$(gcc) s21_grep.c grepFlagFuncs.c $(cmn) -std=c11 -o s21_grep