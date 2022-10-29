// Copyright 2022 Manualti
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../common/common_modules.h"

int main(int argc, char *argv[]) {
    bool flagParse = true;
    char *allowedFlags = "benstET";
    catFlags activeFlags = {false,false,false,false,false,false};
    bool legalFlag = true;
    for (int i = 1; i < argc && legalFlag; i++) {
        // Stop flag parse mode
        if (argv[i][0] != '-') {
            flagParse = false;
        }
        // Read files when flag parse if finished
        if (!flagParse) {
            readFile(argv[i],&activeFlags);
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
                    switch(flag[j]) {
                        case 'b':
                            activeFlags.b = true;
                        break;
                        case 'e':
                            activeFlags.E = true;
                            activeFlags.v = true;
                        break;
                        case 'E':
                            activeFlags.E = true;
                        break;
                        case 'n':
                            activeFlags.n = true;
                        break;
                        case 's':
                            activeFlags.s = true;
                        break;
                        case 't':
                            activeFlags.T = true;
                            activeFlags.v = true;
                        break;
                        case 'T':
                            activeFlags.T = true;
                        break;
                    }
                }
            } else {
                // Set flag to active
                switch(strFlagCheck) {
                    case 'b':
                        activeFlags.b = true;
                    break;
                    case 'n':
                        activeFlags.n = true;
                    break;
                    case 's':
                        activeFlags.s = true;
                    break;
                }
            }
            free(flag);
        }
    }
    return 0;
}
