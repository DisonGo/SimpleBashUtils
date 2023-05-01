#ifndef GREP_FLAGS_H
#define GREP_FLAGS_H
#define BUFFER_SIZE 4096
typedef enum flags {
  e_f = 1 << 0,
  i_f = 1 << 1,
  v_f = 1 << 2,
  c_f = 1 << 3,
  l_f = 1 << 4,
  n_f = 1 << 5,
  h_f = 1 << 6,
  s_f = 1 << 7,
  f_f = 1 << 8,
  o_f = 1 << 9,
  print_all = 1 << 10
} grep_flags;
#endif  //  GREP_FLAGS_H