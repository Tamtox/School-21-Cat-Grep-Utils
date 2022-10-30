// Copyright 2022 Manualti

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "s21_grep.h"
#include "../common/common_modules.h"

int main(int argc, char *argv[]) {
    char *allowed_flags = "eivcln";
    grepFlags active_flags = {false,false,false,false,false,false};
    bool legal_flag = true;
    for (int i = 1; i < argc && legal_flag; i++) {
        // Parse flags
        if (argv[i][0] == '-') {
            // Str argv to variable
            int flag_len = StrLen(argv[i]);
            char *flag = malloc(flag_len * sizeof(char));
            for (int j = 0; j < flag_len; j++) {
                flag[j] = argv[i][j];
            }
            for (int j = 1; j < flag_len; j++) {
                // Check if flag is legal
                if (!StrIncludesChar(allowed_flags, flag[j])) {
                    printf("usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] [-C[num]]\n");
                    printf("[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
                    printf("[--context[=num]] [--directories=action] [--label] [--line-buffered]\n");
                    printf("[--null] [pattern] [file ...]\n");
                    legal_flag = false;
                    break;
                }
                // Set flag to active
                switch(flag[j]) {
                    case 'e':
                        active_flags.e = true;
                    break;
                    case 'i':
                        active_flags.i = true;
                    break;
                    case 'v':
                        active_flags.v = true;
                    break;
                    case 'c':
                        active_flags.c = true;
                    break;
                    case 'l':
                        active_flags.l = true;
                    break;
                    case 'n':
                        active_flags.n = true;
                    break;
                }
            }
            free(flag);
        } else {
            
        }
    }
    return 0;
}