// 2022 Manualti
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "s21_cat.h"
#include "../common/common_modules.h"

int main(int argc, char *argv[]) {
    bool flagParse = true;
    char *allowedFlags = "benstET";
    char *gnuFlags = "-number-nonblank,-number,-squeeze-blank";
    int activeFlags[7] = {0,0,0,0,0,0,0};
    int activeGnuFlags[3] = {0,0,0};
    bool legalFlag = true;
    char flags[100];
    int flagPos = 0;
    for (int i = 1; i < argc && legalFlag; i++) {
        // Stop flag parse mode
        if (argv[i][0] != '-') {
            flags[flagPos] = '\0';
            flagParse = false;
        }
        // Read files when flag parse if finished
        if (!flagParse) {
            readFile(argv[i]);
        } else {
            int flagLen = strLen(argv[i]);
            for (int j = 0; j < flagLen; j++) {
                // Check if flag is a symbol or string 

                // Check if flag is legal
                if (!strIncludes(allowedFlags, argv[i][j]) && argv[i][j] != '-') {
                    printf("cat: illegal option -- %c\n", argv[i][j]);
                    printf("usage: cat [-%s] [file ...]\n", allowedFlags);
                    legalFlag = false;
                    break;
                }
                // Insert flag into flags if its not already there
                if (!strIncludes(flags, argv[i][j]) && argv[i][j] != '-') {
                    flags[flagPos] = argv[i][j];
                    flagPos+=flagLen;
                }
            }
        }
    }
    return 0;
}
