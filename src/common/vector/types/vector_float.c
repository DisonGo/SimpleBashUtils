#include "vector_float.h"

vector_float* init_float(size_t size) {
  size_t len = size ? size : BASE_LENGTH;
  vector_float* new_vec = calloc(1, sizeof(vector_float));
  if (!new_vec) return NULL;
  new_vec->size = len;
  new_vec->length = 0;
  new_vec->data = calloc(len, sizeof(float));
  new_vec->last = new_vec->first = NULL;
  if (!new_vec->data) return NULL;
  return new_vec;
}
vector_float* init_data_float(const float* data, size_t size) {
  if (!data) return NULL;
  size_t len = size ? size : BASE_LENGTH;
  vector_float* new_vec = calloc(1, sizeof(vector_float));
  if (!new_vec) return NULL;
  new_vec->length = new_vec->size = len;
  new_vec->data = calloc(len, sizeof(float));
  if (!new_vec->data) return NULL;
  for (size_t i = 0; i < size; i++) new_vec->data[i] = data[i];
  refresh_last_first_float(new_vec);
  return new_vec;
}
void refresh_last_first_float(vector_float* vec) {
  if (!vec->data) return;
  vec->first = &vec->data[0];
  vec->last = &vec->data[vec->length - 1];
}
float* set_data_float(vector_float* vec, const float* data, size_t size) {
  if (!vec || !data || !size) return NULL;
  if (vec->length + size >= MAX_LENGTH) return NULL;
  free(vec->data);
  vec->data = calloc(size, sizeof(float));
  if (vec->data == NULL) return NULL;
  for (size_t i = 0; i < size; i++) {
    vec->data[i] = data[i];
  }
  vec->length = vec->size = size;
  refresh_last_first_float(vec);
  return vec->data;
}
float pop_float(vector_float* vec) {
  if (!vec) return (float)0;
  if (!vec->length) return (float)0;
  float c = *vec->last;
  vec->data = realloc(vec->data, --vec->length * sizeof(float));
  refresh_last_first_float(vec);
  return c;
}
size_t push_float(vector_float* vec, float a) {
  if (!vec || !vec->data) return -1;
  if (vec->length + 1 >= MAX_LENGTH) return -1;
  vec->data = realloc(vec->data, ++vec->length * sizeof(float));
  vec->size = vec->length;
  vec->data[vec->length - 1] = a;
  refresh_last_first_float(vec);
  return vec->length - 1;
}
size_t push_data_float(vector_float* vec, const float* data, size_t size) {
  if (!vec || !vec->data) return -1;
  size_t old_len = vec->length, n_len = old_len + size;
  if (n_len >= MAX_LENGTH) return -1;
  vec->data = realloc(vec->data, n_len * sizeof(float));
  if (!vec->data) return -1;
  for (size_t i = old_len, k = 0; i < n_len; i++, k++) {
    vec->data[i] = data[k];
  }
  vec->length = n_len;
  refresh_last_first_float(vec);
  return n_len;
}
void foreach_v_float(vector_float* vec, void (*func)(float)) {
  for (size_t i = 0; i < vec->length; i++) func(vec->data[i]);
}
void free_v_float(vector_float* vec, void (*free_data)(float)) {
  if (free_data) foreach_v_float(vec, free_data);
  free(vec->data);
  free(vec);
}