#include "vector_int.h"
vector_int* init_int(size_t size) {
  size_t len = size ? size : BASE_LENGTH;
  vector_int* new_vec = calloc(1, sizeof(vector_int));
  if (!new_vec) return NULL;
  new_vec->size = len;
  new_vec->length = 0;
  new_vec->data = calloc(len, sizeof(int));
  new_vec->last = new_vec->first = NULL;
  if (!new_vec->data) return NULL;
  return new_vec;
}
vector_int* init_data_int(const int* data, size_t size) {
  if (!data) return NULL;
  size_t len = size ? size : BASE_LENGTH;
  vector_int* new_vec = calloc(1, sizeof(vector_int));
  if (!new_vec) return NULL;
  new_vec->length = new_vec->size = len;
  new_vec->data = calloc(len, sizeof(int));
  if (!new_vec->data) return NULL;
  for (size_t i = 0; i < size; i++) new_vec->data[i] = data[i];
  refresh_last_first_int(new_vec);
  return new_vec;
}
void refresh_last_first_int(vector_int* vec) {
  if (!vec->data) return;
  vec->first = &vec->data[0];
  vec->last = &vec->data[vec->length - 1];
}
int* set_data_int(vector_int* vec, const int* data, size_t size) {
  if (!vec || !data || !size) return NULL;
  if (vec->length + size >= MAX_LENGTH) return NULL;
  free(vec->data);
  vec->data = calloc(size, sizeof(int));
  if (vec->data == NULL) return NULL;
  for (size_t i = 0; i < size; i++) {
    vec->data[i] = data[i];
  }
  vec->length = vec->size = size;
  refresh_last_first_int(vec);
  return vec->data;
}
int pop_int(vector_int* vec) {
  if (!vec) return (int)0;
  if (!vec->length) return (int)0;
  int c = *vec->last;
  vec->data = realloc(vec->data, --vec->length * sizeof(int));
  refresh_last_first_int(vec);
  return c;
}
size_t push_int(vector_int* vec, int a) {
  if (!vec || !vec->data) return -1;
  if (vec->length + 1 >= MAX_LENGTH) return -1;
  vec->data = realloc(vec->data, ++vec->length * sizeof(int));
  vec->size = vec->length;
  vec->data[vec->length - 1] = a;
  refresh_last_first_int(vec);
  return vec->length - 1;
}
size_t push_data_int(vector_int* vec, const int* data, size_t size) {
  if (!vec || !vec->data) return -1;
  size_t old_len = vec->length, n_len = old_len + size;
  if (n_len >= MAX_LENGTH) return -1;
  vec->data = realloc(vec->data, n_len * sizeof(int));
  if (!vec->data) return -1;
  for (size_t i = old_len, k = 0; i < n_len; i++, k++) {
    vec->data[i] = data[k];
  }
  vec->length = n_len;
  refresh_last_first_int(vec);
  return n_len;
}
void foreach_v_int(vector_int* vec, void (*func)(int)) {
  for (size_t i = 0; i < vec->length; i++) func(vec->data[i]);
}
void free_v_int(vector_int* vec, void (*free_data)(int)) {
  if (free_data) foreach_v_int(vec, free_data);
  free(vec->data);
  free(vec);
}