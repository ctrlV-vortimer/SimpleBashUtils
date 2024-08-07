CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: s21_grep 

s21_grep: s21_grep.o 
	$(CC) $(CFLAGS) s21_grep.o -o s21_grep 

s21_grep.o: s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) -c s21_grep.c -o s21_grep.o

clean:
	rm -rf *.o s21_grep

rebuild: clean all
