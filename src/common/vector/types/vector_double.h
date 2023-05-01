#ifndef VECTOR_DOUBLE_H
#define VECTOR_DOUBLE_H
#include <stdio.h>
#include <stdlib.h>

#include "../defines.h"
typedef struct _vector_double {
  size_t size;
  size_t length;
  double* data;
  double* last;
  double* first;
} vector_double;
vector_double* init_double(size_t size);
vector_double* init_data_double(const double* data, size_t size);
void refresh_last_first_double(vector_double* vec);
double* set_data_double(vector_double* vec, const double* data, size_t size);
double pop_double(vector_double* vec);
size_t push_double(vector_double* vec, double a);
size_t push_data_double(vector_double* vec, const double* data, size_t size);
void foreach_v_double(vector_double* vec, void (*func)(double));
void free_v_double(vector_double* vec, void (*free_data)(double));
#endif  // VECTOR_DOUBLE_H
