#include <getopt.h>
#include <stdio.h>

struct Flagcat {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
};

struct option long_opt[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {NULL, 0, NULL, 0},
};

struct Flagcat process_flags(int argc, char *argv[], struct Flagcat flagcat);

void print_symbols(FILE *file, struct Flagcat flagcat, int *lineNumber);
