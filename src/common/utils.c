#include "utils.h"
char *get_file_content(FILE *file) {
  char c;
  int len = 0;
  while ((c = fgetc(file)) != EOF) len++;
  char *str = calloc(len, sizeof(char));
  rewind(file);
  if (str && len) {
    for (int i = 0; (c = fgetc(file)) != EOF; i++) str[i] = c;
  }
  rewind(file);
  return str;
}
void tamper_n(char *str) {
  char *lastC = &str[strlen(str) - 1];
  if (*lastC == '\n') *lastC = '\0';
}
void print_binary(int a) {
  int n = 0;
  for (int cpy = a; cpy > 0; cpy /= 2) n++;
  for (int i = 1 << n; i > 0; i /= 2) printf(a & i ? "1" : "0");
}
int get_rows_count(FILE *fp) {
  int count = 0;
  if (fp) {
    char *cont = get_file_content(fp);
    char *entityStr = strtok(cont, "\n");
    while (entityStr != NULL) {
      if (entityStr[0] != '\0') count++;
      entityStr = strtok(NULL, "\n");
    }
    free(cont);
    free(entityStr);
  }
  rewind(fp);
  return count;
}

void prt_n() { printf("\n"); }
void print_file_name(const char *Name) { printf("%s", Name); }
void file_not_found(const char *Name) {
  fprintf(stderr, "File not found: %s\n", Name);
}