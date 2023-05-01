#ifndef VECTOR_V_S_PTR_H
#define VECTOR_V_S_PTR_H
#include <stdio.h>
#include <stdlib.h>

#include "../defines.h"
#include "vector_string.h"
typedef struct _vector_v_s_ptr {
  size_t size;
  size_t length;
  v_s_ptr* data;
  v_s_ptr* last;
  v_s_ptr* first;
} vector_v_s_ptr;
vector_v_s_ptr* init_v_s_ptr(size_t size);
vector_v_s_ptr* init_data_v_s_ptr(const v_s_ptr* data, size_t size);
void refresh_last_first_v_s_ptr(vector_v_s_ptr* vec);
v_s_ptr* set_data_v_s_ptr(vector_v_s_ptr* vec, const v_s_ptr* data,
                          size_t size);
v_s_ptr pop_v_s_ptr(vector_v_s_ptr* vec);
size_t push_v_s_ptr(vector_v_s_ptr* vec, v_s_ptr a);
size_t push_data_v_s_ptr(vector_v_s_ptr* vec, const v_s_ptr* data, size_t size);
void foreach_v_v_s_ptr(vector_v_s_ptr* vec, void (*func)(v_s_ptr));
void free_v_v_s_ptr(vector_v_s_ptr* vec, void (*free_data)(v_s_ptr));
#endif  // VECTOR_V_S_PTR_H