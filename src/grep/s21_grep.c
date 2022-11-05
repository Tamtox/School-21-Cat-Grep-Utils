// Copyright 2022 Manualti

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/common_modules.h"
#include "grep_functions.h"

int main(int argc, char *argv[]) {
  bool pattern_mode = true;
  bool pattern_from_file_mode = false;
  char patterns[250] = {'\0'};
  char files[250] = {'\0'};
  int files_count = 0;
  char *allowed_flags = "eivclnhsfo";
  grepFlags active_flags = {false, false, false, false, false,
                            false, false, false, false, false};
  bool legal_flag = true;
  // Scout ahead for e flag
  for (int i = 1; i < argc && legal_flag; i++) {
    // Parse flags
    bool end_scout = false;
    if (argv[i][0] == '-') {
      // Str argv to variable
      int flag_len = StrLen(argv[i]);
      char flag[50] = {'\0'};
      for (int j = 0; j < flag_len; j++) {
        flag[j] = argv[i][j];
      }
      flag[flag_len] = '\0';
      for (int j = 1; j < flag_len; j++) {
        if (flag[j] == 'e') {
          pattern_mode = false;
          end_scout = true;
        }
      }
    }
    if (end_scout) {
      break;
    }
  }
  for (int i = 1; i < argc && legal_flag; i++) {
    // Parse flags
    if (argv[i][0] == '-') {
      // Str argv to variable
      int flag_len = StrLen(argv[i]);
      char flag[50] = {'\0'};
      for (int j = 0; j < flag_len; j++) {
        flag[j] = argv[i][j];
      }
      flag[flag_len] = '\0';
      for (int j = 1; j < flag_len; j++) {
        // Check if flag is legal
        if (!StrIncludesChar(allowed_flags, flag[j])) {
          fprintf(stderr,
                  "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B "
                  "num] [-C[num]]\n");
          fprintf(
              stderr,
              "[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
          fprintf(stderr, "[--context[=num]] [--directories=action] [--label] "
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
            char remaining_flags[50] = {'\0'};
            SliceStr(flag, remaining_flags, j + 1, flag_len);
            AppendStr(patterns, remaining_flags, ',');
            pattern_mode = false;
          } else {
            pattern_mode = true;
          }
          break;
        }
        // Stop reading flags if f flag is reached and read pattern from
        // provided file or use remaining flags as filename
        if (flag[j] == 'f') {
          active_flags.f = true;
          int remaining_len = flag_len - j - 1;
          if (remaining_len > 0) {
            char remaining_flags[50] = {'\0'};
            SliceStr(flag, remaining_flags, j + 1, flag_len);
            ReadPatternFromFile(remaining_flags, patterns);
            pattern_from_file_mode = false;
          } else {
            pattern_from_file_mode = true;
          }
          pattern_mode = false;
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
        case 'h':
          active_flags.h = true;
          break;
        case 's':
          active_flags.s = true;
          break;
        case 'o':
          active_flags.o = true;
          break;
        }
      }
    } else { // Parse pattern, files with patterns and files to apply patterns
             // then save them
      if (pattern_from_file_mode) {
        ReadPatternFromFile(argv[i], patterns);
        pattern_from_file_mode = false;
        pattern_mode = false;
      } else if (pattern_mode) {
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
      char file_name[50] = {'\0'};
      SliceStr(files, file_name, start_pos, i);
      ReadGrepFile(file_name, &active_flags, patterns, files_count);
      start_pos = i + 1;
    }
  }
  return 0;
}