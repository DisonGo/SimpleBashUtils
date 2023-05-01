#ifndef VECTOR_STRING_H
#define VECTOR_STRING_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../defines.h"
typedef struct _vector_s {
  size_t length;
  char* str;
  char* last;
  char* first;
} vector_string;
typedef vector_string* v_s_ptr;
v_s_ptr init_string(int size);
v_s_ptr init_str_string(const char* n_str);
char* at_string(v_s_ptr str, int i);
char pop_string(v_s_ptr str);
void free_string(v_s_ptr vec_s);
int push_string(v_s_ptr str, char c);
char* set_str_string(v_s_ptr str, const char* new_str);
void foreach_string(v_s_ptr str, void (*func)(char*));
int push_str_string(v_s_ptr str, const char* n_str);
void refresh_last_first_string(v_s_ptr str);
#endif  // VECTOR_STRING_H
