// 2022 Manualti
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "s21_cat.h"
#include "../common/common_modules.h"

int main(int argc, char *argv[]) {
    bool flagParse = true;
    char *allowedFlags = "benstET";
    int activeFlags[7] = {0,0,0,0,0,0,0};
    bool legalFlag = true;
    for (int i = 1; i < argc && legalFlag; i++) {
        // Stop flag parse mode
        if (argv[i][0] != '-') {
            flagParse = false;
        }
        // Read files when flag parse if finished
        if (!flagParse) {
            // readFile(argv[i]);
        } else {
            // Str argv to variable
            int flagLen = strLen(argv[i]);
            char *flag = malloc(flagLen * sizeof(char));
            for (int j = 0; j < flagLen; j++) {
                flag[j] = argv[i][j];
            }
            // Check string flags
            char strFlagCheck = checkStrFlags(flag);
            if (strFlagCheck == 'z') {
                for (int j = 1; j < flagLen; j++) {
                    // Check if flag is legal
                    if (!strIncludesChar(allowedFlags, flag[j])) {
                        printf("cat: illegal option -- %c\n", flag[j]);
                        printf("usage: cat [-%s] [file ...]\n", allowedFlags);
                        legalFlag = false;
                        break;
                    }
                    // Set flag to active
                    for (int k = 0; k < 7; k++) {
                        if (allowedFlags[k] == flag[j]) {
                            activeFlags[k] = 1;
                        }
                    }
                }
            } else {
                for (int j = 0; j < 7; j++) {
                    if (allowedFlags[j] == strFlagCheck) {
                        activeFlags[j] = 1;
                    }
                }
            }
            free(flag);
        }
    }
    for (int j = 0; j < 7; j++) {
        printf("%d\n",activeFlags[j]);
    }
    return 0;
}
