#ifndef FLAG_PAIR_H
#define FLAG_PAIR_H
#include "vector/types/vector_v_s_ptr.h"
typedef struct FlagPair {
  int flag;
  int values_count;
  vector_v_s_ptr* vals;
} FlagPair;
#endif  //  FLAG_PAIR_H