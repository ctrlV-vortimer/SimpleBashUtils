#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

#define COUNT 11000

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int f;
  int h;
  int s;
  int o;
  int print_namefile;
  char arstr[COUNT];
  char arg[COUNT];
} Flag;

Flag readflags(int argc, char *argv[]);
void output(char *argv[], Flag flaggrep);
void process_grepflag(Flag *flaggrep, int *countmatch_file, int *countmatch_str,
                      char *argv[]);
void processmatch_grep(Flag flaggrep, regex_t regcompil, int lineNumber,
                       int *countmatch_str, int *countmatch_file, char *argv[]);
void process_flag_o(Flag flaggrep, regex_t regcompil, int lineNumber,
                    char *argv[]);
void process_flag_f(Flag *flaggrep);

#endif
