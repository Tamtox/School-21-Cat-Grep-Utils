CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: s21_grep
 
rebuild: clean s21_grep

s21_grep: s21_grep.o grep_functions.o common_modules.o
	$(CC) $(CFLAGS) s21_grep.o grep_functions.o common_modules.o -o s21_grep

s21_grep.o:
	$(CC) $(CFLAGS) -c s21_grep.c -o s21_grep.o

grep_functions.o:
	$(CC) $(CFLAGS) -c grep_functions.c -o grep_functions.o

common_modules.o:
	$(CC) $(CFLAGS) -c ../common/common_modules.c -o common_modules.o

clean:
	rm -rf *.o s21_grep
