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


void readFile(char *fileName, int *activeFlags) {
    char *allowedFlags = "benstET";
    FILE *file = NULL;
    file = fopen(fileName, "r");
    if (file != NULL) {
        int numbytes;
        fseek(file, 0L, SEEK_END);
        numbytes = ftell(file);
        fseek(file, 0L, SEEK_SET);
        if (numbytes > 0) {
            char *text = malloc(numbytes * sizeof(char));
            fread(text, sizeof(char), numbytes, file);
            int lineCount = 0;
            bool printLine = true;
            bool endChar = true;
            for (int i = 0; i < numbytes; i++) {
                // Print line count
                if (i == 0 && printLine) {
                    lineCount++;
                    printf("%d", lineCount);
                }
                if (text[i] == '\n') {
                    if (endChar) {
                        printf("$");
                    }
                    printf("\n");
                    if (printLine) {
                        lineCount++;
                        printf("%d", lineCount);
                    }
                } else {
                    printf("%c", text[i]);
                }
                // Make new line break if end of document is reached
                if (i == numbytes - 1) {
                    if (endChar) {
                        printf("$");
                    }
                    printf("\n");
                }
            }
            free(text);
        }
    } else {
        printf("cat: %s: No such file or directory", fileName);
    }

}
