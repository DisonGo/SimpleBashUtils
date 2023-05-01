#include "grepFlagFuncs.h"
int e_f_check(char **argv, int *Flags, const char *str_pat, FlagPair *val_arr,
              int *curFile) {
  if (*Flags & e_f) {
    add_value(val_arr, str_pat);
  } else {
    if (access(argv[*curFile], F_OK) == 0) {
      return (*Flags) & f_f ? 1 : 0;
    } else {
      *Flags |= e_f;
      add_value(val_arr, argv[(*curFile)++]);
    }
  }
  return 1;
}
void c_f_func(FILE *fp, regex_t *pattern, int Flags, int multiFiles,
              const char *fileName) {
  char line[BUFFER_SIZE];
  int succ = 0, n = 0;
  while (fgets(line, BUFFER_SIZE, fp)) {
    succ = (regexec(pattern, line, 0, NULL, 0) == 0);
    if (Flags & v_f) succ = !succ;
    if (succ) n++;
    if (n && Flags & l_f) break;
  }
  if (multiFiles && !(Flags & h_f)) {
    print_file_name(fileName);
    printf(":");
  }
  printf("%d", n);
  prt_n();
  rewind(fp);
}
void l_f_func(FILE *fp, regex_t *pattern, int Flags, const char *fileName) {
  char line[BUFFER_SIZE];
  int succ = 0;
  while (fgets(line, BUFFER_SIZE, fp)) {
    succ = (regexec(pattern, line, 0, NULL, 0) == 0);
    if (Flags & v_f) succ = !succ;
    if (succ) {
      print_file_name(fileName);
      prt_n();
      break;
    }
  }
  rewind(fp);
}
int f_f_func(FlagPair *val_arr, int *Flags) {
  for (size_t i = 0; i < val_arr[1].vals->length; i++) {
    v_s_ptr val = val_arr[1].vals->data[i];
    FILE *reg_f = fopen(val->str, "r");
    if (!reg_f) {
      if (!(*Flags & s_f)) file_not_found(val->str);
      return 0;
    }
    char reg_line[BUFFER_SIZE];
    while (fgets(reg_line, BUFFER_SIZE, reg_f)) {
      if (reg_line[0] == '\n') {
        *Flags |= print_all | e_f;
        break;
      }
      tamper_n(reg_line);
      add_value(&val_arr[0], reg_line);
    }
    if (reg_f) fclose(reg_f);
  }
  if (val_arr[0].vals->length) *Flags |= e_f;
  return 1;
}
void o_f_func(vector_v_s_ptr *pattern_vec, int Flags, const char *line) {
  int match = 0, eflags = 0;
  regex_t pattern;
  regmatch_t reg_match[1];
  size_t line_len = strlen(line), offset = 0;
  for (size_t i = 0; i < pattern_vec->length; i++) {
    compile_pattern(pattern_vec->data[i]->str, &pattern, Flags);
    int res = !regexec(&pattern, line + offset, 1, reg_match, eflags);
    if (Flags & v_f && !res) {
      printf("%s", line);
      prt_n();
      regfree(&pattern);
      break;
    }
    while (res) {
      eflags = REG_NOTBOL;
      match++;
      for (size_t i = offset + reg_match[0].rm_so;
           i < offset + reg_match[0].rm_eo; i++) {
        printf("%c", line[i]);
      }
      prt_n();
      offset += reg_match[0].rm_eo;
      if (reg_match[0].rm_so == reg_match[0].rm_eo) offset += 1;
      if (offset > line_len) break;
      res = !regexec(&pattern, line + offset, 1, reg_match, eflags);
    }
    regfree(&pattern);
  }
}
void add_value(FlagPair *pair, const char *str) {
  if (pair->vals == NULL) return;
  push_v_s_ptr(pair->vals, init_str_string(str));
}
void default_f_func(FILE *fp, regex_t *pattern, vector_v_s_ptr *pattern_vec,
                    int Flags, int multiFiles, const char *fileName) {
  char line[BUFFER_SIZE];
  int succ = 0, lineN = 0;
  while (fgets(line, BUFFER_SIZE, fp)) {
    lineN++;
    succ = (regexec(pattern, line, 0, NULL, 0) == 0);
    if (Flags & v_f) succ = !succ;
    if (Flags & print_all) succ = 1;
    if (succ) {
      tamper_n(line);
      if (multiFiles && !(Flags & h_f)) {
        print_file_name(fileName);
        printf(":");
      }
      if (Flags & n_f) printf("%d:", lineN);
      if (Flags & print_all) {
        printf("%s", line);
        prt_n();
      } else if (Flags & o_f) {
        o_f_func(pattern_vec, Flags, line);
      } else {
        printf("%s", line);
        prt_n();
      }
    }
  }
  rewind(fp);
}
void grep_usage() { printf("usage: grep [-eivclnhsfo?] [file ...]\n"); }
int compile_pattern(const char *pattern, regex_t *regeP, int Flags) {
  int reg_flags = REG_EXTENDED;
  if (Flags & i_f) reg_flags |= REG_ICASE;
  if (pattern[0] == '.' && pattern[1] == '\0') reg_flags |= REG_NEWLINE;
  int ret = regcomp(regeP, pattern, reg_flags);
  if (ret) {
    if (Flags & s_f) return 0;
    char error[BUFFER_SIZE];
    (void)regerror(ret, regeP, error, sizeof error);
    fprintf(stderr, "pattern `%s': %s\n", pattern, error);
    return 0;
  }
  return 1;
}