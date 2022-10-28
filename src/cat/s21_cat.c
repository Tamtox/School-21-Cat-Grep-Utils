// 2022 Manualti
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "s21_cat.h"
#include "../common/common_modules.h"

int main(int argc, char *argv[]) {
    bool flagParse = true;
    char *allowedFlags = "benstuv";
    bool legalFlag = true;
    char flags[50];
    int flagPos = 0;
    for (int i = 1; i < argc && legalFlag; i++) {
        // Stop flag parse mode
        if (argv[i][0] != '-') {
            flags[flagPos] = '\0';
            flagParse = false;
        }
        // Read files or parse flags
        if (!flagParse) {
            readFile(argv[i], flags);
        } else {
            int flagLen = strLen(argv[i]);
            for (int j = 0; j < flagLen; j++) {
                // Check if flag is legal
                if (!strIncludes(allowedFlags, argv[i][j]) && argv[i][j] != '-') {
                    printf("cat: illegal option -- %c\n", argv[i][j]);
                    printf("usage: cat [-%s] [file ...]\n", allowedFlags);
                    legalFlag = false;
                    break;
                }
                if (!strIncludes(flags, argv[i][j]) && argv[i][j] != '-') {
                    flags[flagPos] = argv[i][j];
                    flagPos++;
                }
            }
        }
    }
    return 0;
}
