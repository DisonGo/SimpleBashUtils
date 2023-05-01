#ifndef VECTOR_FLOAT_H
#define VECTOR_FLOAT_H
#include <stdio.h>
#include <stdlib.h>

#include "../defines.h"
typedef struct _vector_float {
  size_t size;
  size_t length;
  float* data;
  float* last;
  float* first;
} vector_float;
vector_float* init_float(size_t size);
vector_float* init_data_float(const float* data, size_t size);
void refresh_last_first_float(vector_float* vec);
float* set_data_float(vector_float* vec, const float* data, size_t size);
float pop_float(vector_float* vec);
size_t push_float(vector_float* vec, float a);
size_t push_data_float(vector_float* vec, const float* data, size_t size);
void foreach_v_float(vector_float* vec, void (*func)(float));
void free_v_float(vector_float* vec, void (*free_data)(float));
#endif  // VECTOR_FLOAT_H
