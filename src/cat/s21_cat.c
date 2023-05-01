#include "s21_cat.h"

int main(int argc, char **argv) {
  int Flags = 0;
  const char *short_options = "benstvTE?";
  const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'}};
  Flags = read_flags(argc, argv, short_options, long_options, NULL,
                     &cat_flag_switch);
  int curFile = optind;
  int stdinMode = curFile == argc;
  while (stdinMode) {
    FILE *fp = STDIN_FILENO;
    flag_transform_text(fp, Flags);
    fclose(fp);
  }
  while (curFile < argc) {
    FILE *fp = fopen(argv[curFile], "rb");
    if (!fp) {
      fprintf(stderr, "%s: %s: No such file or directory", argv[0],
              argv[curFile]);
      exit(1);
    }
    flag_transform_text(fp, Flags);
    fclose(fp);
    curFile++;
  }
  return 0;
}
void flag_transform_text(FILE *fp, int Flags) {
  char buffer[BUFFER_SIZE];
  int lastLineBlank = 0;
  int lineN = 1;
  while (fgets(buffer, BUFFER_SIZE, (fp == NULL ? stdin : fp))) {
    if (fp == STDIN_FILENO) lineN = 1;
    if (flag_transform_line(buffer, Flags, &lastLineBlank, &lineN))
      printf("%s", buffer);
  }
}
int flag_transform_line(char *buffer, int Flags, int *lastBlank, int *lineN) {
  int length = strlen(buffer);
  buffer[length] = '\0';
  if (Flags & v_f) replace_32_128chars(buffer);
  if (Flags & t_f) {
    replace_char(buffer, "\t", "^I");
  }
  if (Flags & s_f) {
    int currentLineBlank = (strlen(buffer) <= 1);
    if (*lastBlank && currentLineBlank) return 0;
    *lastBlank = currentLineBlank;
  }
  if (Flags & n_f) {
    if (Flags & b_f) {
      Flags ^= n_f;
    } else {
      numerate_line(buffer, lineN);
    }
  }
  if (Flags & b_f && !(Flags & n_f)) {
    if (strlen(buffer) >= 1 && buffer[0] != '\n') {
      numerate_line(buffer, lineN);
    }
  }
  if (Flags & e_f) {
    length = strlen(buffer);
    if (buffer[length - 1] == '\n') {
      buffer[length - 1] = '$';
      strcat(buffer, "\n");
    }
  }
  return 1;
}
void numerate_line(char *line, int *lineN) {
  char *tmp = calloc(strlen(line) + 1, sizeof(char));
  strcpy(tmp, line);
  line[0] = '\0';
  sprintf(line, "%*d\t", 6, (*lineN)++);
  strcat(line, tmp);
  free(tmp);
}
void cat_flag_switch(int *Flags, int option, FlagPair *value_arr) {
  if (!value_arr) value_arr = NULL;
  switch (option) {
    case 'b':
      *Flags |= b_f;
      break;
    case 'e':
      *Flags |= e_f | v_f;
      break;
    case 'E':
      *Flags |= e_f;
      break;
    case 'n':
      *Flags |= n_f;
      break;
    case 's':
      *Flags |= s_f;
      break;
    case 't':
      *Flags |= t_f | v_f;
      break;
    case 'T':
      *Flags |= t_f;
      break;
    case 'v':
      *Flags |= v_f;
      break;
    case '?':
      printf("usage: s21_cat [-benstvTB?] [file ...]\n");
      exit(1);
  }
}