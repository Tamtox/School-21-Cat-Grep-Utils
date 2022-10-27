CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: s21_cat s21_grep
 
rebuild: clean s21_cat s21_grep

s21_cat.o: s21_cat.c s21_cat.h
	$(CC) $(CFLAGS) -c ./cat/s21_cat.c

s21_grep.o: s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) -c ./cat/s21_grep.c

common_modules.o: common_modules.c common_modules.h
	$(CC) $(CFLAGS) -c ./common/common_modules.c

state_sort: state_sort.o binary_functions.o
		$(CC) $(CFLAGS) state_sort.o binary_functions.o -o ../build/Quest_1

state_search:state_search.o binary_functions.o
		$(CC) $(CFLAGS) state_search.o binary_functions.o -o ../build/Quest_2

clear_state:clear_state.o binary_functions.o
		$(CC) $(CFLAGS) clear_state.o binary_functions.o -o ../build/Quest_3

state_sort.o: state_sort.c
		$(CC) $(CFLAGS) -c state_sort.c

state_search.o: state_search.c
		$(CC) $(CFLAGS) -c state_search.c

clear_state.o: clear_state.c
		$(CC) $(CFLAGS) -c clear_state.c

binary_functions.o: binary_functions.c binary_functions.h
		$(CC) $(CFLAGS) -c binary_functions.c

clean:
		rm -rf *.o ../cat
		rm -rf *.o ../grep
