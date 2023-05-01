#ifndef FLAG_READER_H
#define FLAG_READER_H
#include <getopt.h>
#include <stdlib.h>

#include "flagPair.h"
int read_flags(int argc, char** argv, const char* short_options,
               const struct option* long_options, FlagPair* value_arr,
               void (*flagSwitch)(int*, int, FlagPair*));
#endif  // FLAG_READER_H
