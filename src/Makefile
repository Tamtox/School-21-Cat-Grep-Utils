CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: s21_cat s21_grep
 
rebuild: clean s21_cat s21_grep

main.o:
	$(CC) $(CFLAGS) -c main.c

s21_cat.o: s21_cat.c s21_cat.h
	$(CC) $(CFLAGS) -c ./cat/s21_cat.c

s21_grep.o: s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) -c ./cat/s21_grep.c

common_modules.o: common_modules.c common_modules.h
	$(CC) $(CFLAGS) -c ./common/common_modules.c

s21_cat: s21_cat.o common_modules.o
	$(CC) $(CFLAGS) -o s21_cat.o ../common/common_modules.o -o s21_cat

s21_grep: s21_grep.o common_modules.o ../common/common_modules.o -o s21_grep
	$(CC) $(CFLAGS) -o s21_grep.o

clean:
		rm -rf *.o ../cat
		rm -rf *.o ../grep
