#include "strFuncs.h"
void replace_char(char *str, char *c, char *with) {
  char *tmp, *ptr = NULL;
  int w_len = strlen(with), str_len = strlen(str);
  if (!str || !with || !str_len || !w_len) return;
  int count = 0;
  ptr = strstr(str, c);
  while (ptr != NULL) {
    count++;
    ptr = strstr(ptr + 1, c);
  }
  tmp = calloc(str_len + (w_len - 1) * count + 1, 1);
  if (!tmp) return;
  strcpy(tmp, str);
  while (count-- > 0) {
    size_t pos = strcspn(tmp, c);
    char *end = calloc(str_len + (w_len - 1) * count + 1, 1);
    if (!end) return;
    strcpy(end, tmp + pos + 1);
    tmp[pos] = '\0';
    strcat(tmp, with);
    strcat(tmp, end);
    free(end);
  }
  if (strlen(tmp)) strcpy(str, tmp);
  free(tmp);
}
void replace_32_128chars(char *str) {
  size_t str_len = strlen(str);
  for (size_t i = 0; i < str_len; i++) {
    int c = str[i];
    char what[BUFFER_SIZE] = {c};
    if ((c >= 0 && c < 32 && c != 10 && c != 9)) {
      char replace_str[BUFFER_SIZE] = {'^', (c + 64)};
      replace_char(str, what, replace_str);
    } else if ((c < -96 && c > -128)) {
      if (c == -118 || c == -119) {
        c += 64;
        char replace_str[BUFFER_SIZE] = {'M', '-', '^', (c + 128)};
        replace_char(str, what, replace_str);
      } else {
        char replace_str[BUFFER_SIZE] = {'M', '-', (c + 128)};
        replace_char(str, what, replace_str);
      }
    }
    if (c == 127) replace_char(str, what, "^?");
  }
}