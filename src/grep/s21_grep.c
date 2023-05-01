#include "s21_grep.h"
int main(int argc, char **argv) {
  int Flags = 0, curFile = 0, multiFiles = 0;
  const char *short_options = "e:ivclnhsf:o?";
  size_t val_len = strlen(short_options) - 3;
  FlagPair value_arr[val_len];
  for (size_t i = 0; i < val_len; i++)
    value_arr[i].vals = new_vector(v_s_ptr, 1);
  regex_t pattern;
  FILE *fp = NULL;
  Flags =
      read_flags(argc, argv, short_options, NULL, value_arr, &grep_flag_switch);
  curFile = optind;
  if (curFile >= argc) {
    grep_usage();
    free_programm(NULL, value_arr, val_len);
  }
  if (Flags & f_f)
    if (!f_f_func(value_arr, &Flags))
      free_programm(Flags & e_f ? &pattern : NULL, value_arr, val_len);
  if (!(Flags & e_f))
    if (!e_f_check(argv, &Flags, argv[curFile], value_arr, &curFile))
      free_programm(Flags & e_f ? &pattern : NULL, value_arr, val_len);

  multiFiles = (argc - curFile > 1);
  v_s_ptr reg_str = compile_reg_v_s_ptr(value_arr[0].vals);
  if (Flags & print_all) set_str_string(reg_str, ".*");
  if (Flags & e_f) compile_pattern(reg_str->str, &pattern, Flags);
  while (curFile < argc) {
    v_s_ptr filename = init_str_string(argv[curFile]);
    if ((fp = fopen(filename->str, "r")) == NULL) {
      if (Flags & s_f) continue;
      file_not_found(filename->str);
      free_string(filename);
      curFile++;
      continue;
    }
    flag_action_menu(fp, &pattern, value_arr, Flags, multiFiles, filename->str);
    free_string(filename);
    if (fp != NULL) fclose(fp);
    curFile++;
  }
  free_string(reg_str);
  free_programm(Flags & e_f ? &pattern : NULL, value_arr, val_len);
  return 0;
}
void flag_action_menu(FILE *fp, regex_t *pattern, FlagPair *val_arr, int Flags,
                      int multiFiles, const char *fileName) {
  if (Flags & c_f) c_f_func(fp, pattern, Flags, multiFiles, fileName);
  if (Flags & l_f) l_f_func(fp, pattern, Flags, fileName);
  if (Flags & c_f || Flags & l_f) return;
  default_f_func(fp, pattern, &val_arr->vals[0], Flags, multiFiles, fileName);
}
v_s_ptr compile_reg_v_s_ptr(vector_v_s_ptr *pattern_vec) {
  v_s_ptr n_str = init_string(1);
  for (size_t i = 0; i < pattern_vec->length; i++) {
    push_str_string(n_str, pattern_vec->data[i]->str);
    if (i + 1 < pattern_vec->length) push_string(n_str, '|');
  }
  return n_str;
}
void grep_flag_switch(int *Flags, int option, FlagPair *value_arr) {
  switch (option) {
    case 'e': {
      *Flags |= e_f;
      add_value(&value_arr[0], optarg);
      break;
    }
    case 'i':
      *Flags |= i_f;
      break;
    case 'v':
      *Flags |= v_f;
      break;
    case 'c':
      *Flags |= c_f;
      break;
    case 'l':
      *Flags |= l_f;
      break;
    case 'n':
      *Flags |= n_f;
      break;
    case 'h':
      *Flags |= h_f;
      break;
    case 's':
      *Flags |= s_f;
      break;
    case 'f': {
      *Flags |= f_f;
      add_value(&value_arr[1], optarg);
      break;
    }
    case 'o':
      *Flags |= o_f;
      break;
    case '?':
      grep_usage();
      break;
  }
}
void free_vector_v_s_ptr(v_s_ptr a) { free_string(a); }
void free_programm(regex_t *pattern, FlagPair *val_arr, size_t val_size) {
  if (pattern != NULL) regfree(pattern);
  for (size_t i = 0; i < val_size; i++) {
    free_v_v_s_ptr(val_arr[i].vals, free_vector_v_s_ptr);
  }
  exit(0);
}