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

void StrToLowercase (char *str) {
    int str_len = StrLen(str);
    for (int i = 0; i < str_len; i++) {
        if (str[i] >= 65 && str[i] <= 90) {
            str[i] = str[i] + 32;
        }
    }
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
    for (int i = 0; i < to - from; i++) {
        result[i] = str[from + i];
    }
    result[to - from] = '\0';
}

void AppendStr (char *str1, char *str2, char separator) {
    int str1_len = StrLen(str1);
    int str2_len = StrLen(str2);
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

void ReadPatternFromFile (char *file_name, char *patterns) {
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
            while (fgets(line, MAX_LENGTH, file)) {
                int line_len = StrLen(line);
                if (line[line_len - 1] == '\n') {
                    line[line_len - 1] = '\0';
                }
                // Save line as pattern
                AppendStr(patterns, line, ',');
            }
            fclose(file);
        }
    } else {
        fprintf(stderr,"grep: %s: No such file or directory\n", file_name);
    }
}

void PrintMatchedLine(int *line_count, int *matched_count, int *patterns_matching, char *line, char *pattern, grepFlags *active_flags, char *file_name, int files_count) {
    regex_t regex;
    int reg_status;
    char msgbuf[100];
    int line_len = StrLen(line);
    reg_status = regcomp(&regex, pattern, active_flags->i ? REG_ICASE : 0);
    if (reg_status) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    // Regex execution
    size_t nmatch = 3;
    regmatch_t matches[nmatch];
    if (active_flags->o && !active_flags->c && !active_flags->v && !active_flags->l) {
        printf("O flag case\n");
    } else {
         reg_status = regexec(&regex, line, nmatch, matches, 0);
        regfree(&regex);
        // Print normal or inverted matches
        if (!reg_status) {
            // printf("Line: <<%.*s>>\n", (int)(matches[0].rm_eo - matches[0].rm_so), line + matches[0].rm_so);
            // printf("match offsets are %lld %lld\n", matches[0].rm_so, matches[0].rm_eo);
            // printf("match[0]=%.*s<\n", (int)matches[0].rm_eo, &line[matches[0].rm_so]);

            // printf("submatch offsets are %lld %lld\n", matches[1].rm_so, matches[1].rm_eo);
            // if(matches[1].rm_so != -1) {
            //     printf("match[1]=%.*s<\n", (int)matches[1].rm_eo, &line[matches[1].rm_so]);
            // }
            // Print line numbers if v flag is inactive
            if (!active_flags->v) {
                *matched_count = *matched_count + 1; 
                // Check if only total count of matched lines needed
                if (!active_flags->c && !active_flags->l && *patterns_matching < 1) { 
                    // Print file name if more than one file
                    if (files_count > 1 && !active_flags->h) {
                        printf("%s:", file_name);
                    }
                    // Print line number if n flag is active
                    if (active_flags->n) {
                        printf("%d:", *line_count);
                    }
                    if (active_flags->o) {

                    }
                    printf("%s", line);
                    if (line[line_len - 1] != '\n') {
                        printf("\n");
                    }
                }
                *patterns_matching = *patterns_matching + 1;
            }
        } else if (reg_status == REG_NOMATCH) {
            // Print line numbers if v flag is active
            if (active_flags->v) {
                *matched_count = *matched_count + 1; 
                // Check if only total count of matched lines needed
                if (!active_flags->c && !active_flags->l && *patterns_matching < 1) { 
                    // Print file name if more than one file
                    if (files_count > 1 && !active_flags->h) {
                        printf("%s:", file_name);
                    }
                    // Print line number if n flag is active
                    if (active_flags->n) {
                        printf("%d:", *line_count);
                    }
                    printf("%s", line);
                    if (line[line_len - 1] != '\n') {
                        printf("\n");
                    }
                }
                *patterns_matching = *patterns_matching + 1;
            }
        } else {
            regerror(reg_status, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
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
                line_count++;
                // Iterate through patterns
                int patterns_len = StrLen(patterns);
                int start_pos = 0;
                // Check if multiple patterns apply to same line
                int patterns_matching = 0;
                for (int i = 0; i < patterns_len; i++) {
                    if (patterns[i] == ',') {
                        char pattern[50] ={'\0'};
                        SliceStr (patterns, pattern, start_pos, i);
                        PrintMatchedLine(&line_count, &matched_count, &patterns_matching, line, pattern, active_flags, file_name, files_count);
                        start_pos = i + 1;

                    }
                }
            }
            // Print matched lines count
            if (active_flags->c) {
                // Output filenames if there are more than 1 file
                if (files_count > 1 && !active_flags->h) {
                    printf("%s:", file_name);
                }
                if (active_flags->l) {
                    int matches = matched_count ? 1 : 0;
                    printf("%d\n", matches);
                } else {
                    printf("%d\n", matched_count);
                }
            }
            // Print names of files with matches
            if (active_flags->l && matched_count) {
                printf("%s\n", file_name);
            }
            fclose(file);
        }
    } else {
        if (!active_flags->s) {
            fprintf(stderr,"grep: %s: No such file or directory\n", file_name);
        }
    }
}
