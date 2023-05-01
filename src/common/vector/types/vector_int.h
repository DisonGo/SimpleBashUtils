#ifndef VECTOR_INT_H
#define VECTOR_INT_H
#include <stdio.h>
#include <stdlib.h>

#include "../defines.h"
typedef struct _vector_int {
  size_t size;
  size_t length;
  int* data;
  int* last;
  int* first;
} vector_int;
vector_int* init_int(size_t size);
vector_int* init_data_int(const int* data, size_t size);
void refresh_last_first_int(vector_int* vec);
int* set_data_int(vector_int* vec, const int* data, size_t size);
int pop_in(vector_int* vec);
size_t push_int(vector_int* vec, int a);
size_t push_data_int(vector_int* vec, const int* data, size_t size);
void foreach_v_int(vector_int* vec, void (*func)(int));
void free_v_int(vector_int* vec, void (*free_data)(int));
#endif  // VECTOR_INT_H
