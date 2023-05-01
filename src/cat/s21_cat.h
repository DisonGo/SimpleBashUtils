#ifndef S21_CAT_H
#define S21_CAT_H
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/flagReader.h"
#include "../common/strFuncs.h"
#include "catFlags.h"
void flag_transform_text(FILE* fp, int Flags);
int flag_transform_line(char* buffer, int Flags, int* lastBlank, int* lineN);
void numerate_line(char* line, int* lineN);
void cat_flag_switch(int* Flags, int option, FlagPair* value_arr);

#endif  // S21_CAT_H
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4096
#endif