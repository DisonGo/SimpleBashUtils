#include "flagReader.h"

int read_flags(int argc, char **argv, const char *short_options,
               const struct option *long_options, FlagPair *value_arr,
               void (*flagSwitch)(int *, int, FlagPair *)) {
  int Flags = 0;
  int option = 0, option_index = 0;
  while ((option = getopt_long(argc, argv, short_options, long_options,
                               &option_index)) != -1) {
    flagSwitch(&Flags, option, value_arr);
  }
  return Flags;
}