#include "vector_string.h"
v_s_ptr init_string(int size) {
  int len = size ? size : BASE_LENGTH;
  v_s_ptr new_vec = calloc(len, sizeof(vector_string));
  if (!new_vec) return NULL;
  new_vec->length = len;
  new_vec->str = calloc(len + 1, sizeof(char));
  refresh_last_first_string(new_vec);
  return new_vec;
}
v_s_ptr init_str_string(const char* str) {
  if (!str) return NULL;
  size_t size = strlen(str);
  size_t len = size ? size : BASE_LENGTH;
  v_s_ptr new_vec = calloc(len, sizeof(vector_string));
  if (!new_vec) return NULL;
  new_vec->length = len;
  new_vec->str = calloc(len + 1, sizeof(char));
  strcpy(new_vec->str, str);
  refresh_last_first_string(new_vec);
  return new_vec;
}
void refresh_last_first_string(v_s_ptr str) {
  if (!str->str) return;
  str->first = &str->str[0];
  str->last = &str->str[str->length - 1];
}
char* set_str_string(v_s_ptr str, const char* new_str) {
  int n_len = strlen(new_str);
  if (!str) return NULL;
  if (str->length + n_len + 1 >= MAX_LENGTH) return NULL;
  free(str->str);
  str->str = calloc(n_len + 1, sizeof(char));
  if (str->str == NULL) return NULL;
  strcpy(str->str, new_str);
  str->length = n_len;
  refresh_last_first_string(str);
  return str->str;
}
char pop_string(v_s_ptr str) {
  if (!str) return 0;
  char c = str->str[str->length - 1];
  str->str[str->length - 1] = '\0';
  str->str = realloc(str->str, --str->length);
  refresh_last_first_string(str);
  return c;
}
int push_string(v_s_ptr str, char c) {
  if (!str || !str->str) return -1;
  if (str->length + 1 >= MAX_LENGTH) return -1;
  str->str = realloc(str->str, ++str->length);
  strncat(str->str, &c, 1);
  refresh_last_first_string(str);
  return str->length - 1;
}
int push_str_string(v_s_ptr str, const char* n_str) {
  if (!str) return -1;
  size_t* len = &str->length;
  int n_len = *len + strlen(n_str);
  if (n_len + 1 >= MAX_LENGTH) return -1;
  str->str = realloc(str->str, n_len + 1);
  if (!str->str) return -1;
  strcat(str->str, n_str);
  str->length = n_len;
  refresh_last_first_string(str);
  return n_len;
}
char* at_string(v_s_ptr str, int i) {
  if (!str) return 0;
  if (abs(i) > str->length) return 0;
  if (i < 0) i += str->length;
  return &str->str[i];
}
void foreach_string(v_s_ptr str, void (*func)(char*)) {
  for (size_t i = 0; i < str->length; i++) func(&str->str[i]);
}
void free_string(v_s_ptr vec_s) {
  if (vec_s->str) free(vec_s->str);
  free(vec_s);
}
