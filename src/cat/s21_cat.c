#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int lineNumber = 1;

  struct Flagcat flagcat = {0};
  flagcat = process_flags(argc, argv, flagcat);
  for (int i = optind; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");

    if (file != NULL) {
      print_symbols(file, flagcat, &lineNumber);
    } else {
      printf("Не удалось открыть файл.\n");
      return 1;
    }
    fclose(file);
  }

  return 0;
}
struct Flagcat process_flags(int argc, char *argv[], struct Flagcat flagcat) {
  int rez = 0;
  int long_index = 0;

  while ((rez = getopt_long(argc, argv, "benstvET", long_opt, &long_index)) !=
         -1) {
    switch (rez) {
      case 'b':
        flagcat.b = 1;
        break;
      case 'e':
        flagcat.e = 1;
        flagcat.v = 1;
        break;
      case 'n':
        flagcat.n = 1;
        break;
      case 's':
        flagcat.s = 1;
        break;
      case 'E':
        flagcat.e = 1;
        break;
      case 't':
        flagcat.t = 1;
        break;
      case 'T':
        flagcat.t = 1;
        break;
      case 'v':
        flagcat.v = 1;
        break;
    }
  }

  if (flagcat.b == 1) {
    flagcat.n = 0;
  }

  return flagcat;
}

void print_symbols(FILE *file, struct Flagcat flagcat, int *lineNumber) {
  char symbol = 0;

  char pre_symbol = '\n';
  int emptylines = -1;

  while ((symbol = fgetc(file)) != EOF) {
    if ((flagcat.s && pre_symbol == '\n' && symbol == '\n')) {
      emptylines++;

      if (emptylines > 0) {
        continue;
      }
    } else {
      emptylines = -1;
    }
    if (flagcat.n && pre_symbol == '\n') {
      printf("%6d\t", (*lineNumber)++);
    }
    if (flagcat.b && pre_symbol == '\n' && symbol != '\n') {
      printf("%6d\t", (*lineNumber)++);
    }
    if (flagcat.e && symbol == '\n') {
      printf("$");
    }
    if (flagcat.t && symbol == '\t') {
      printf("^");
      symbol = 'I';
    }
    if (flagcat.v &&
        (((symbol >= 0 && symbol < 9) || (symbol > 10 && symbol < 32)) ||
         (symbol == 127))) {
      if (symbol == 127) {
        symbol -= 64;
      } else {
        symbol += 64;
      }
      printf("^");
    }

    printf("%c", symbol);
    pre_symbol = symbol;
  }
}
