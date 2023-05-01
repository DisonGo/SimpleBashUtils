#include "vector_v_s_ptr.h"

vector_v_s_ptr* init_v_s_ptr(size_t size) {
  size_t len = size ? size : BASE_LENGTH;
  vector_v_s_ptr* new_vec = calloc(1, sizeof(vector_v_s_ptr));
  if (!new_vec) return NULL;
  new_vec->size = len;
  new_vec->length = 0;
  new_vec->data = calloc(len, sizeof(v_s_ptr));
  new_vec->last = new_vec->first = NULL;
  if (!new_vec->data) return NULL;
  return new_vec;
}
vector_v_s_ptr* init_data_v_s_ptr(const v_s_ptr* data, size_t size) {
  if (!data) return NULL;
  size_t len = size ? size : BASE_LENGTH;
  vector_v_s_ptr* new_vec = calloc(1, sizeof(vector_v_s_ptr));
  if (!new_vec) return NULL;
  new_vec->length = new_vec->size = len;
  new_vec->data = calloc(len, sizeof(v_s_ptr));
  if (!new_vec->data) return NULL;
  for (size_t i = 0; i < size; i++) new_vec->data[i] = data[i];
  refresh_last_first_v_s_ptr(new_vec);
  return new_vec;
}
void refresh_last_first_v_s_ptr(vector_v_s_ptr* vec) {
  if (!vec->data) return;
  vec->first = &vec->data[0];
  vec->last = &vec->data[vec->length - 1];
}
v_s_ptr* set_data_v_s_ptr(vector_v_s_ptr* vec, const v_s_ptr* data,
                          size_t size) {
  if (!vec || !data || !size) return NULL;
  if (vec->length + size >= MAX_LENGTH) return NULL;
  free(vec->data);
  vec->data = calloc(size, sizeof(v_s_ptr));
  if (vec->data == NULL) return NULL;
  for (size_t i = 0; i < size; i++) {
    vec->data[i] = data[i];
  }
  vec->length = vec->size = size;
  refresh_last_first_v_s_ptr(vec);
  return vec->data;
}
v_s_ptr pop_v_s_ptr(vector_v_s_ptr* vec) {
  if (!vec) return (v_s_ptr)0;
  if (!vec->length) return (v_s_ptr)0;
  v_s_ptr c = *vec->last;
  vec->data = realloc(vec->data, --vec->length * sizeof(v_s_ptr));
  refresh_last_first_v_s_ptr(vec);
  return c;
}
size_t push_v_s_ptr(vector_v_s_ptr* vec, v_s_ptr a) {
  if (!vec || !vec->data) return -1;
  if (vec->length + 1 >= MAX_LENGTH) return -1;
  vec->data = realloc(vec->data, ++vec->length * sizeof(v_s_ptr));
  vec->size = vec->length;
  vec->data[vec->length - 1] = a;
  refresh_last_first_v_s_ptr(vec);
  return vec->length - 1;
}
size_t push_data_v_s_ptr(vector_v_s_ptr* vec, const v_s_ptr* data,
                         size_t size) {
  if (!vec || !vec->data) return -1;
  size_t old_len = vec->length, n_len = old_len + size;
  if (n_len >= MAX_LENGTH) return -1;
  vec->data = realloc(vec->data, n_len * sizeof(v_s_ptr));
  if (!vec->data) return -1;
  for (size_t i = old_len, k = 0; i < n_len; i++, k++) {
    vec->data[i] = data[k];
  }
  vec->length = n_len;
  refresh_last_first_v_s_ptr(vec);
  return n_len;
}
void foreach_v_v_s_ptr(vector_v_s_ptr* vec, void (*func)(v_s_ptr)) {
  for (size_t i = 0; i < vec->length; i++) func(vec->data[i]);
}
void free_v_v_s_ptr(vector_v_s_ptr* vec, void (*free_data)(v_s_ptr)) {
  if (vec == NULL) return;
  if (vec->data == NULL) return;
  if (free_data != NULL) foreach_v_v_s_ptr(vec, free_data);
  free(vec->data);
  free(vec);
}