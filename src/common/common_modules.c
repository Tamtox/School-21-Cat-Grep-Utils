#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "common_modules.h"


int StrLen (char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

bool StrIncludesChar (char *str, char c) {
    bool result = false;
    int strL = StrLen(str);
    for (int i = 0; i < strL; i++) {
        if (str[i] == c) {
            result = true;
        }
    }
    return result;
}

char CheckStrFlags (char *flag) {
    char str_flags[3][20] = {"--number-nonblank","--number","--squeeze-blank"};
    char *str_flags_let = "bns";
    char result = 'z';
    for (int i = 0; i < 3; i++) {
        int comparison = strcmp(str_flags[i],flag);
        if (comparison == 0) {
            result = str_flags_let[i];
        }
    }
    return result;
}


void ReadCatFile(char *fileName, catFlags *active_flags) {
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
            int line_count = 0;
            int squeeze = 0;
            while (fgets(line, MAX_LENGTH, file)) {
                // Squeeze empty lines
                if (active_flags->s && line[0] == '\n') {
                    squeeze = 1;
                    continue;
                } 
                if (squeeze) {
                    squeeze = 0;
                    if (active_flags->E) {
                        printf("$\n");
                    } else {
                        printf("\n");
                    }
                }
                // Line numeration
                if (active_flags->b || active_flags->n) {
                    if (active_flags->b) {
                        if (line[0] != '\n') {
                            line_count ++;
                            printf("%6d\t", line_count);
                        }
                    } else {
                        line_count ++;
                        printf("%6d\t", line_count);
                    }
                }
                for (int i = 0; i < 256; i++) {
                    // Show tabulation
                    if (line[i] == '\t' && active_flags->T) {
                        printf("^I");
                        continue;
                    }
                    // Break output when end is reached and add new line 
                    if (line[i] == '\0') {
                        break;
                    } 
                    // Print char of line or $ when needed
                    if (line[i] == '\n') {
                        if (active_flags->E) {
                            printf("$\n");
                        } else {
                            printf("\n");
                        }
                    } else {
                        printf("%c", line[i]);
                    }
                    // Print non-printable characters
                    if ((line[i] >= 0 && line[i] <= 31) && (line[i] != 9 && line[i] != 10) && active_flags->v) {
                        printf("^%c", line[i] + 64);
                        continue;
                    }
                    if (line[i] == 127 && active_flags->v) {
                        printf("^?");
                        continue;
                    }
                }
            }
            // Squeeze empty lines if they are at the end
            if (squeeze) {
                if (active_flags->E) {
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
