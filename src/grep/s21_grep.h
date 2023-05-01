#ifndef S21_GREP_H
#define S21_GREP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/flagReader.h"
#include "../common/utils.h"
#include "../common/vector/types/vector_v_s_ptr.h"
#include "grepFlagFuncs.h"
#include "grepFlags.h"
typedef char* string;
void grep_flag_switch(int* Flags, int option, FlagPair* value_arr);
void flag_action_menu(FILE* fp, regex_t* pattern, FlagPair* val_arr, int Flags,
                      int multiFiles, const char* fileName);
v_s_ptr compile_reg_v_s_ptr(vector_v_s_ptr* vec);
void free_vector_v_s_ptr(v_s_ptr a);
void free_programm(regex_t* pattern, FlagPair* val_arr, size_t val_size);
#endif  //  S21_GREP_H