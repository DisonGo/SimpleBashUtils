#ifndef GREP_FLAG_FUNCS_H
#define GREP_FLAG_FUNCS_H
#include <ctype.h>
#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/flagPair.h"
#include "../common/utils.h"
#include "grepFlags.h"
#define MAX_MATCH_COUNT 100
int e_f_check(char** argv, int* Flags, const char* str_pat, FlagPair* val_arr,
              int* curFile);
void c_f_func(FILE* fp, regex_t* pattern, int Flags, int multiFiles,
              const char* fileName);
void l_f_func(FILE* fp, regex_t* pattern, int Flags, const char* fileName);
int f_f_func(FlagPair* val_arr, int* Flags);
void o_f_func(vector_v_s_ptr* pattern_vec, int Flags, const char* line);
void add_value(FlagPair* pair, const char* str);
void default_f_func(FILE* fp, regex_t* pattern, vector_v_s_ptr* pattern_vec,
                    int Flags, int multiFiles, const char* fileName);
void grep_usage();
int compile_pattern(const char* text, regex_t* regeP, int Flags);
#endif  //  GREP_FLAG_FUNCS_H