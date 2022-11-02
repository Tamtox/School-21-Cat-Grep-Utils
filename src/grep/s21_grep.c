// Copyright 2022 Manualti

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/common_modules.h"

int main(int argc, char *argv[]) {
  bool pattern_mode = true;
  char *patterns = malloc(1 * sizeof(char));
  char *files = malloc(1 * sizeof(char));
  int files_count = 0;
	if (patterns == NULL || files == NULL) {
		fprintf(stderr,"Malloc error\n");
		exit(1);
	}
  char *allowed_flags = "eivcln";
  grepFlags active_flags = {false, false, false, false, false, false};
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
          fprintf(stderr,
                  "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B "
                  "num] [-C[num]]\n");
          fprintf(
              stderr,
              "[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
          fprintf(stderr,
                  "[--context[=num]] [--directories=action] [--label] "
                  "[--line-buffered]\n");
          fprintf(stderr, "[--null] [pattern] [file ...]\n");
          legal_flag = false;
          break;
        }
        // Stop reading flags if e flag is reached and push rest of the flag as
        // pattern
        if (flag[j] == 'e') {
          active_flags.e = true;
          int remaining_len = flag_len - j - 1;
          if (remaining_len > 0) {
            char *remaining_flags = malloc(0 * sizeof(char));
            if (remaining_flags == NULL) {
              fprintf(stderr,"Malloc error\n");
		          exit(1);
            }
            SliceStr(flag, remaining_flags, j + 1, flag_len);
            AppendStr(patterns, remaining_flags, ',');
            pattern_mode = false;
            free(remaining_flags);
          } else {
            pattern_mode = true;
          }
          break;
        }
        // Set flag to active
        switch (flag[j]) {
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
    }
    // Parse pattern and files then save them
    else {
      if (pattern_mode) {
        AppendStr(patterns, argv[i], ',');
        pattern_mode = false;
      } else {
        AppendStr(files, argv[i], ',');
        files_count++;
      }
    }
  }
  // Iterate through files
  int files_len = StrLen(files);
  int start_pos = 0;
  for (int i = 0; i < files_len; i++) {
    if (files[i] == ',') {
      char *file_name = malloc(0 * sizeof(char));
      if (file_name == NULL) {
        fprintf(stderr,"Malloc error\n");
		    exit(1);
      }
      SliceStr(files, file_name, start_pos, i);
      ReadGrepFile(file_name, &active_flags, patterns, files_count);
      start_pos = i + 1;
      free(file_name);
    }
  }
  free(patterns);
  free(files);
  return 0;
}