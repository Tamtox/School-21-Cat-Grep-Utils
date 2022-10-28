#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common_modules.h"

int strLen (char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

bool strIncludes (char *str, char c) {
    bool result = false;
    int len = strLen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == c) {
            result = true;
        }
    }
    return result;
}

// char *getStrUntillSpaceEnd (char *str, int startPos) {
//     // Find size of substring
//     int endPos = startPos;
//     int i  = startPos;
//     while (str[i] != ' ' || str[i] != '\0') {
//         endPos++;
//     }
//     // Return substring
//     char *substr = malloc((endPos - startPos) * sizeof(char));
//     for (int j; j < endPos - startPos; j++) {
//         substr[j] = str[startPos + j];
//     }
//     return substr;
// }

void readFile(char *fileName, char *flags) {
    FILE *file = NULL;
    file = fopen(fileName, "r");
    bool
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

// char *get_command_input (char *str) {
//     scanf("%[^\n]%*c",str);
//     return str;
// }

// struct  catInputs parse_command_input (char* input) {
//     int inputLen = strLen(input);
//     struct catInputs parsed;
//     char *catOptions = "benstuv";
//     char error[1000] = "cat: illegal option -- z\nusage: cat [-benstuv] [file ...]";
//     for (int i = 0; i < inputLen; i++) {
//         if (input[i] == '-') {

//         } else {

//         }
//     }
//     return parsed;
// }
