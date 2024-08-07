#include "s21_grep.h"

int main(int argc, char *argv[]) {
  Flag flaggrep = readflags(argc, argv);

  while (optind < argc) {
    output(argv, flaggrep);
    optind++;
  }
  return 0;
}

Flag readflags(int argc, char *argv[]) {
  int rez = 0;
  Flag flaggrep = {};
  while ((rez = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    switch (rez) {
      case 'e':
        flaggrep.e = 1;
        strcat(flaggrep.arg, optarg);
        strcat(flaggrep.arg, "|");
        break;
      case 'i':
        flaggrep.i = 1;
        break;
      case 'v':
        flaggrep.v = 1;
        break;
      case 'c':
        flaggrep.c = 1;
        break;
      case 'l':
        flaggrep.l = 1;
        break;
      case 'n':
        flaggrep.n = 1;
        break;
      case 'f':
        process_flag_f(&flaggrep);
        flaggrep.f = 1;
        break;
      case 'h':
        flaggrep.h = 1;
        break;
      case 's':
        flaggrep.s = 1;
        break;
      case 'o':
        flaggrep.o = 1;
        break;
    }
    if (flaggrep.l == 1) {
      flaggrep.c = 0;
    }
  }
  if (!flaggrep.e && !flaggrep.f) {
    if (argc > optind) {
      strcat(flaggrep.arg, argv[optind]);
    }
    optind++;
  }
  if ((argc > optind + 1) && !flaggrep.h) flaggrep.print_namefile = 1;

  if (flaggrep.e || flaggrep.f) flaggrep.arg[strlen(flaggrep.arg) - 1] = '\0';

  if (flaggrep.c || flaggrep.l || flaggrep.v) flaggrep.o = 0;

  return flaggrep;
}

void output(char *argv[], Flag flaggrep) {
  FILE *file;
  regex_t regcompil;
  int lineNumber = 1, countmatch_str = 0, countmatch_file = 0,
      flag_i = REG_EXTENDED;
  if (flaggrep.i) flag_i = REG_EXTENDED | REG_ICASE;
  file = fopen(argv[optind], "r");
  if (file != NULL) {
    if (!regcomp(&regcompil, flaggrep.arg, flag_i)) {
      while (fgets(flaggrep.arstr, COUNT, file) != NULL) {
        if (flaggrep.o) {
          process_flag_o(flaggrep, regcompil, lineNumber, argv);
          lineNumber++;
          continue;
        }
        processmatch_grep(flaggrep, regcompil, lineNumber, &countmatch_str,
                          &countmatch_file, argv);
        lineNumber++;
      }
      process_grepflag(&flaggrep, &countmatch_file, &countmatch_str, argv);
      regfree(&regcompil);
    }
    fclose(file);
  } else if (!flaggrep.s) {
    fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
  }
}

void process_grepflag(Flag *flaggrep, int *countmatch_file, int *countmatch_str,
                      char *argv[]) {
  if (flaggrep->c) {
    if (flaggrep->print_namefile) printf("%s:", argv[optind]);
    if (flaggrep->l && *countmatch_str) *countmatch_str = 1;
    printf("%d\n", *countmatch_str);
  }
  if (flaggrep->l && *countmatch_file) printf("%s\n", argv[optind]);
}

void processmatch_grep(Flag flaggrep, regex_t regcompil, int lineNumber,
                       int *countmatch_str, int *countmatch_file,
                       char *argv[]) {
  regmatch_t matchinfo;
  int match = regexec(&regcompil, flaggrep.arstr, 1, &matchinfo, 0);  // *
  if (flaggrep.v) match = !match;
  if (!match) {
    if (!flaggrep.c && !flaggrep.l && !flaggrep.o) {
      if (flaggrep.print_namefile) printf("%s:", argv[optind]);

      if (flaggrep.n) printf("%d:", lineNumber);
      if (strchr(flaggrep.arstr, '\n') == NULL) strcat(flaggrep.arstr, "\n");
      printf("%s", flaggrep.arstr);
    }
    *countmatch_file = 1;
    (*countmatch_str)++;
  }
}

void process_flag_o(Flag flaggrep, regex_t regcompil, int lineNumber,
                    char *argv[]) {
  regmatch_t matchinfo;
  char *sym = flaggrep.arstr;
  while (regexec(&regcompil, sym, 1, &matchinfo, 0) != REG_NOMATCH) {
    if (flaggrep.print_namefile) printf("%s:", argv[optind]);
    if (flaggrep.n) printf("%d:", lineNumber);
    for (int j = matchinfo.rm_so; j < matchinfo.rm_eo; j++) {
      putchar(sym[j]);
    }
    sym += matchinfo.rm_eo;
    printf("\n");
  }
}

void process_flag_f(Flag *flaggrep) {
  char arstr_f[COUNT];
  FILE *f;
  f = fopen(optarg, "r");
  if (f != NULL) {
    while (fgets(arstr_f, COUNT, f) != NULL) {
      arstr_f[strcspn(arstr_f, "\n")] = '\0';
      if (strlen(arstr_f) == 0) strcat(arstr_f, ".");

      strcat(flaggrep->arg, arstr_f);
      strcat(flaggrep->arg, "|");
    }

    fclose(f);
  } else if (!flaggrep->s) {
    fprintf(stderr, "grep: %s: No such file or directory\n", optarg);
  }
}
