#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "common_modules.h"


int strLen (char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

bool strIncludesChar (char *str, char c) {
    bool result = false;
    int strL = strLen(str);
    for (int i = 0; i < strL; i++) {
        if (str[i] == c) {
            result = true;
        }
    }
    return result;
}

char checkStrFlags (char *flag) {
    char strFlags[3][20] = {"--number-nonblank","--number","--squeeze-blank"};
    char *strFlagsLet = "bns";
    char result = 'z';
    for (int i = 0; i < 3; i++) {
        int comparison = strcmp(strFlags[i],flag);
        if (comparison == 0) {
            result = strFlagsLet[i];
        }
    }
    return result;
}


void readFile(char *fileName, catFlags *activeFlags) {
    FILE *file = NULL;
    file = fopen(fileName, "r");
    if (file != NULL) {
        // Read file whole 
        int numbytes;
        fseek(file, 0L, SEEK_END);
        numbytes = ftell(file);
        fseek(file, 0L, SEEK_SET);
        if (numbytes > 0) {
            // Read file line by line
            const unsigned MAX_LENGTH = 256;
            char line[MAX_LENGTH];
            int lineCount = 0;
            int squeeze = 0;
            while (fgets(line, MAX_LENGTH, file)) {
                // Squeeze empty lines
                if (activeFlags->s && line[0] == '\n') {
                    squeeze = 1;
                    continue;
                } 
                if (squeeze) {
                    squeeze = 0;
                    if (activeFlags->E) {
                        printf("$\n");
                    } else {
                        printf("\n");
                    }
                }
                // Line numeration
                if (activeFlags->b || activeFlags->n) {
                    if (activeFlags->b) {
                        if (line[0] != '\n') {
                            lineCount ++;
                            printf("%6d\t", lineCount);
                        }
                    } else {
                        lineCount ++;
                        printf("%6d\t", lineCount);
                    }
                }
                for (int i = 0; i < 256; i++) {
                    // Print non-printable characters
                    if (line[i] >= 0  && activeFlags->v) {
                        printf("^%c", char);
                        continue;
                    }
                    // Show tabulation
                    if (line[i] == '\t' && activeFlags->T) {
                        printf("^I");
                        continue;
                    }
                    // Break output when end is reached and add new line 
                    if (line[i] == '\0') {
                        break;
                    } 
                    // Print char of line or $ when needed
                    if (line[i] == '\n') {
                        if (activeFlags->E) {
                            printf("$\n");
                        } else {
                            printf("\n");
                        }
                    } else {
                        printf("%c", line[i]);
                    }
                }
            }
            // Squeeze empty lines if they are at the end
            if (squeeze) {
                if (activeFlags->E) {
                    printf("$\n");
                } else {
                    printf("\n");
                }
            }
            fclose(file);
        }
    } else {
        printf("cat: %s: No such file or directory", fileName);
    }

}
