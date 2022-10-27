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
	clean_s21_cat clean_s21_grep clean_common_modules

clean_s21_cat:
	rm -rf *.o ./cat
clean_s21_grep:
	rm -rf *.o ./grep
clean_common_modules:
	rm -rf *.o ./common_modules