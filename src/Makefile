CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: s21_cat s21_grep
 
rebuild: clean s21_cat s21_grep

s21_cat: s21_cat.o common_modules.o
	$(CC) $(CFLAGS) ./cat/s21_cat.o ./common/common_modules.o -o ./cat/s21_cat

s21_grep: s21_grep.o common_modules.o
	$(CC) $(CFLAGS) ./grep/s21_grep.o ./common/common_modules.o -o ./grep/s21_grep

s21_cat.o:
	$(CC) $(CFLAGS) -c ./cat/s21_cat.c -o ./cat/s21_cat.o

s21_grep.o:
	$(CC) $(CFLAGS) -c ./grep/s21_grep.c -o ./grep/s21_grep.o

common_modules.o:
	$(CC) $(CFLAGS) -c ./common/common_modules.c -o ./common/common_modules.o

clean:
	rm -rf *.o ./cat/s21_cat ./cat/*.o rm -rf *.o ./grep/s21_grep ./grep/*.o rm -rf *.o ./common/*.o
