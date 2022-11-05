CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: s21_cat
 
rebuild: clean s21_cat

s21_cat: s21_cat.o cat_functions.o common_modules.o
	$(CC) $(CFLAGS) s21_cat.o cat_functions.o common_modules.o -o s21_cat

s21_cat.o:
	$(CC) $(CFLAGS) -c s21_cat.c -o s21_cat.o

cat_functions.o:
	$(CC) $(CFLAGS) -c cat_functions.c -o cat_functions.o

common_modules.o:
	$(CC) $(CFLAGS) -c ../common/common_modules.c -o common_modules.o

clean:
	rm -rf *.o s21_cat
