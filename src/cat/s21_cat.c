// Copyright 2022 Manualti

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/common_modules.h"

int main(int argc, char *argv[]) {
  bool flag_parse = true;
  char *allowed_flags = "benstvET";
  catFlags active_flags = {false, false, false, false, false, false};
  bool legal_flag = true;
  for (int i = 1; i < argc && legal_flag; i++) {
    // Stop flag parse mode when flags end
    if (argv[i][0] != '-') {
      flag_parse = false;
    }
    // Read files when flag parse if finished
    if (!flag_parse) {
      ReadCatFile(argv[i], &active_flags);
    } else {
      // Str argv to variable
      int flag_len = StrLen(argv[i]);
      char *flag = malloc(flag_len * sizeof(char));
      if (flag == NULL) {
          fprintf(stderr,"Malloc error\n");
          exit(1);
      }
      for (int j = 0; j < flag_len; j++) {
        flag[j] = argv[i][j];
      }
      // Check string flags
      char str_flag_check = CheckStrFlags(flag);
      if (str_flag_check == 'z') {
        for (int j = 1; j < flag_len; j++) {
          // Check if flag is legal
          if (!StrIncludesChar(allowed_flags, flag[j])) {
            fprintf(stderr, "cat: illegal option -- %c\n", flag[j]);
            fprintf(stderr, "usage: cat [-%s] [file ...]\n", allowed_flags);
            legal_flag = false;
            break;
          }
          // Set flag to active
          switch (flag[j]) {
            case 'b':
              active_flags.b = true;
              break;
            case 'e':
              active_flags.E = true;
              active_flags.v = true;
              break;
            case 'E':
              active_flags.E = true;
              break;
            case 'n':
              active_flags.n = true;
              break;
            case 's':
              active_flags.s = true;
              break;
            case 't':
              active_flags.T = true;
              active_flags.v = true;
              break;
            case 'T':
              active_flags.T = true;
              break;
            case 'v':
              active_flags.v = true;
              break;
          }
        }
      } else {
        // Set flag to active
        switch (str_flag_check) {
          case 'b':
            active_flags.b = true;
            break;
          case 'n':
            active_flags.n = true;
            break;
          case 's':
            active_flags.s = true;
            break;
        }
      }
      free(flag);
    }
  }
  return 0;
}
