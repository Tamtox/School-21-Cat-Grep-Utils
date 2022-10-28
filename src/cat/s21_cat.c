#include <stdio.h>
#include <stdlib.h>
#include "s21_cat.h"
#include "../common/common_modules.h"

int main(int argc, char *argv[]) {
    printf("%s\n",argv[1]);
    printf("%d", argc);
    for (int i = 1; i < argc; i++) {

    }
    readFile(argv[1]);
    return 0;
}