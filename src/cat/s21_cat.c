#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "s21_cat.h"
#include "../common/common_modules.h"

int main(int argc, char *argv[]) {
    bool flagParse = true;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            flagParse = false;
        }
        readFile(argv[i]);
    }
    return 0;
}