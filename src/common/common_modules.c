#include <stdio.h>
#include <stdlib.h>
#include "common_modules.h"

int strLen (char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
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

void readFile(char *fileName) {
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
            printf("%s\n", text);
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
