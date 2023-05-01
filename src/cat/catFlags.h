#ifndef CAT_FLAGS_H
#define CAT_FLAGS_H
typedef enum cat_flags {
  b_f = 1 << 0,
  e_f = 1 << 1,
  n_f = 1 << 2,
  s_f = 1 << 3,
  t_f = 1 << 4,
  v_f = 1 << 5
} cat_flags;
#endif  //  CAT_FLAGS_H