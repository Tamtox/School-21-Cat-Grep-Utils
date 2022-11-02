#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>
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

void SliceStr (char *str, char *result, int from , int to) {
    result = realloc(result, (to - from) * sizeof(char));
    for (int i = 0; i < to - from; i++) {
        result[i] = str[from + i];
    }
    result[to - from] = '\0';
}

void AppendStr (char *str1, char *str2, char separator) {
    int str1_len = StrLen(str1);
    int str2_len = StrLen(str2);
    str1 = realloc(str1, (str1_len + str2_len + 1) * sizeof(char));
    for (int i = 0; i < str2_len; i++) {
        str1[str1_len + i] = str2[i];
    }
    str1[str1_len + str2_len] = separator;
    str1[str1_len + str2_len + 1] = '\0';
}

int CatLineNumeration (bool numerate_full_lines, bool numerate_lines, int line_count, char line_start) {
    if (numerate_full_lines || numerate_lines) {
        // Numerates only non blank lines
        if (numerate_full_lines) {
            if (line_start != '\n') {
                line_count ++;
                printf("%6d\t", line_count);
            }
        } 
        // Numerates all lines
        else {
            line_count ++;
            printf("%6d\t", line_count);
        }
    }
    return line_count;
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
                        if (active_flags->n && !active_flags->b) {
                            line_count++;
                            printf("%6d\t$\n",line_count);
                        } else {
                            printf("$\n");
                        }
                    } else {
                        if (active_flags->n && !active_flags->b) {
                            line_count++;
                            printf("%6d\t\n",line_count);
                        } else {
                            printf("\n");
                        }
                    }
                }
                // Line numeration
                line_count = CatLineNumeration(active_flags->b,active_flags->n,line_count,line[0]);
                for (int i = 0; i < 256; i++) {
                    // Break output when end is reached and add new line 
                    if (line[i] == '\0') {
                        break;
                    }
                    // Show tabulation
                    if (line[i] == '\t' && active_flags->T) {
                        if (active_flags->T) {
                            printf("^I");
                            continue;
                        } else {
                            printf("\t");
                            continue;
                        }
                    }
                    // Print non-printable characters
                    if ((line[i] >= 0 && line[i] <= 31) && line[i] != 9 && line[i] != 10 && active_flags->v) {
                        printf("^%c", line[i] + 64);
                        continue;
                    }
                    if (line[i] == 127 && active_flags->v) {
                        printf("^?");
                        continue;
                    }
                    // Make new line and add $ when flag E active
                    if (line[i] == '\n') {
                        if (active_flags->E) {
                            printf("$\n");
                            continue;
                        } else {
                            printf("\n");
                            continue;
                        }
                    } else {
                        printf("%c", line[i]);
                    }
                }
            }
            // Squeeze empty lines if they are at the end
            if (squeeze) {
                if (active_flags->E) {
                    if (active_flags->n && !active_flags->b) {
                        line_count++;
                        printf("%6d\t$\n",line_count);
                    } else {
                        printf("$\n");
                    }
                } else {
                    if (active_flags->n && !active_flags->b) {
                        line_count++;
                        printf("%6d\t\n",line_count);
                    } else {
                        printf("\n");
                    }
                }
            }
            fclose(file);
        }
    } else {
        fprintf(stderr,"cat: %s: No such file or directory\n", fileName);
    }
}

void PrintMatchedLine(int *line_count, int *matched_count, char *line, char *pattern, grepFlags *active_flags, char *file_name, int files_count) {
    regex_t regex;
    int reti;
    char msgbuf[100];
    // Regex compilation
    reti = regcomp(&regex, pattern, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    // Regex execution
    reti = regexec(&regex, line, 0, NULL, 0);
    *line_count = *line_count + 1;
    // Print normal or inverted matches
    if (!reti) {
        // Print line numbers if v flag is inactive
        if (!active_flags->v) {
            *matched_count = *matched_count + 1; 
            // Check if only total count of matched lines needed
            if (!active_flags->c) { 
                // Line count 
                if (active_flags->n) {
                    if (files_count > 1) {
                        printf("%s:%d:%s", file_name, *line_count, line);
                    } else {
                        printf("%d:%s", *line_count, line);
                    }
                } else {
                    if (files_count > 1) {
                        printf("%s:%s", file_name, line);
                    } else {
                        printf("%s", line);
                    }
                }
            }
        }
    } else if (reti == REG_NOMATCH) {
        // Print line numbers if v flag is active
        if (active_flags->v) {
            *matched_count = *matched_count + 1;
            // Check if only total count of matched lines needed
            if (!active_flags->c) {
                // Line count 
                if (active_flags->n) {
                    if (files_count > 1) {
                        printf("%s:%d:%s", file_name, *line_count, line);
                    } else {
                        printf("%d:%s", *line_count, line);
                    }
                } else {
                    if (files_count > 1) {
                        printf("%s:%s", file_name, line);
                    } else {
                        printf("%s", line);
                    }
                }
            }
        }
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
}

void ReadGrepFile(char *file_name, grepFlags *active_flags, char *patterns, int files_count) {
    FILE *file = NULL;
    file = fopen(file_name, "r");
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
            int matched_count = 0;
            while (fgets(line, MAX_LENGTH, file)) {
                // Iterate through patterns
                int patterns_len = StrLen(patterns);
                int start_pos = 0;
                for (int i = 0; i < patterns_len; i++) {
                    if (patterns[i] == ',') {
                        char *pattern = malloc(0 * sizeof(char));
                        SliceStr (patterns, pattern, start_pos, i);
                        PrintMatchedLine(&line_count, &matched_count, line, pattern, active_flags, file_name, files_count);
                        start_pos = i + 1;
                        free(pattern);
                    }
                }
            }
            // Print matched lines count
            if (active_flags->c) {
                // Output filenames if there are more than 1 file
                if (files_count > 1) {
                    printf("%s:%d\n", file_name , matched_count);
                    // Output only matched file names
                    if (active_flags->l && matched_count) {
                        printf("%s\n", file_name);
                    }
                } else {
                    printf("%d\n", matched_count);
                    // Output only matched file names
                    if (active_flags->l && matched_count) {
                        printf("%s\n", file_name);
                    }
                }
            }
            fclose(file);
        }
    } else {
        fprintf(stderr,"grep: %s: No such file or directory\n", file_name);
    }
}
