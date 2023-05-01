SHELL := /bin/bash

Flags 				= -Werror -Wall -Wextra
gcc 				= gcc $(Flags)
cmn 				= ../common/flagReader.c ../common/strFuncs.c
clang_path			= ../../materials/build/scripts/
OS := $(shell uname -s)
ifeq ($(OS), Darwin)
 gcc += -D OS_MAC
endif
ifeq ($(OS), Linux)
 gcc += -D OS_LINUX
endif


all: clean s21_cat
clear:
	clear
clean:
	rm -rf ./tests/s21_cat ./tests/*.out
	rm -rf s21_cat *.out
	rm -rf .clang-format
testing: clear all
	mv s21_cat ./tests
	cd ./tests; chmod u=rwx test_func_cat.sh ; ./test_func_cat.sh
	rm ./tests/s21_cat
clang:
	cp $(clang_path).clang-format ./
	clang-format -n *.c *.h
clang_replace:
	cp $(clang_path).clang-format ./
	clang-format -i *.c *.h
s21_cat:
	$(gcc) s21_cat.c $(cmn) -std=c11 -o s21_cat