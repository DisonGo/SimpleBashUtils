#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* get_file_content(FILE* file);
int get_rows_count(FILE* fp);
void prt_n();
void tamper_n(char* str);
void print_file_name(const char* Name);
void print_binary(int a);
void file_not_found(const char* Name);
#endif  // UTILS_H