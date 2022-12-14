#include "grep_functions.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/common_modules.h"

void ReadPatternFromFile(char *file_name, char *patterns) {
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
      const unsigned MAX_LENGTH = 500;
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
    fprintf(stderr, "grep: %s: No such file or directory\n", file_name);
  }
}

void PrintMatch(char *pattern, char *text, grepFlags *active_flags) {
  regex_t regex;
  int reg_status;
  reg_status = regcomp(&regex, pattern, active_flags->i ? REG_ICASE : 0);
  if (reg_status) {
    fprintf(stderr, "Could not compile regex\n");
    regfree(&regex);
    exit(1);
  }
  size_t nmatch = 2;
  regmatch_t matches[nmatch];
  reg_status = regexec(&regex, text, nmatch, matches, 0);
  regfree(&regex);
  if (reg_status == 0) {
    printf("%.*s\n", (int)(matches[0].rm_eo - matches[0].rm_so),
           text + matches[0].rm_so);
    // printf("%d", (int)matches[0].rm_eo);
    // printf("match offsets are %lld %lld\n", matches[0].rm_so,
    // matches[0].rm_eo);
  }
}

void PrintMatchedLine(int *patterns_matching, char *line, char *pattern,
                      grepFlags *active_flags, int files_count, int *to_print,
                      char *file_name, int line_count, int line_len) {
  regex_t regex;
  int reg_status;
  reg_status = regcomp(&regex, pattern, active_flags->i ? REG_ICASE : 0);
  if (reg_status) {
    fprintf(stderr, "Could not compile regex\n");
    regfree(&regex);
    exit(1);
  }
  if (active_flags->o && !active_flags->c && !active_flags->v &&
      !active_flags->l) {
    reg_status = regexec(&regex, line, 0, 0, 0);
    regfree(&regex);
    // Check if line contains any matches
    if (!reg_status) {
      // Print file name if more than one file
      if (files_count > 1 && !active_flags->h) {
        printf("%s:", file_name);
        // to_print[0] = 1;
      }
      // Print line number if n flag is active
      if (active_flags->n) {
        printf("%d:", line_count);
        // to_print[1] = 1;
      }
      // Print out all matches by adjusting line offset
      for (int i = 0; i < line_len; i++) {
        // Find start and end of substring
        int start = 0, end = 0;
        // Find Substrings separated by non-printable chars
        if (line[i] > 32 && line[i] != 127) {
          start = i;
          for (int j = i + 1; j < line_len; j++) {
            if ((line[j] >= 0 && line[j] <= 32) || line[j] == 127) {
              end = j;
              break;
            }
          }
          if (end > 0) {
            i = end;
          }
        }
        if (end > 0) {
          char sub_str[255] = {'\0'};
          SliceStr(line, sub_str, start, end);
          PrintMatch(pattern, sub_str, active_flags);
        }
      }
      if (line[line_len - 1] != '\n') {
        printf("\n");
      }
    }
  } else {
    reg_status = regexec(&regex, line, 0, 0, 0);
    regfree(&regex);
    // Print normal or inverted matches
    if (!reg_status && !active_flags->v) {
      // Check if only total count of matched lines needed
      if (!active_flags->c && !active_flags->l && *patterns_matching < 1) {
        if (files_count > 1 && !active_flags->h) {
          to_print[0] = 1;
        }
        if (active_flags->n) {
          to_print[1] = 1;
        }
        to_print[2] = 1;
      }
      *patterns_matching = *patterns_matching + 1;
    } else if (reg_status == REG_NOMATCH && active_flags->v) {
      // Check if only total count of matched lines needed
      if (!active_flags->c && !active_flags->l && *patterns_matching < 1) {
        if (files_count > 1 && !active_flags->h) {
          to_print[0] = 1;
        }
        if (active_flags->n) {
          to_print[1] = 1;
        }
        to_print[2] = 1;
      }
      *patterns_matching = *patterns_matching + 1;
    }
  }
}

void ReadGrepFile(char *file_name, grepFlags *active_flags, char *patterns,
                  int files_count) {
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
      const unsigned MAX_LENGTH = 500;
      char line[MAX_LENGTH];
      int line_count = 0;
      int matched_count = 0;
      while (fgets(line, MAX_LENGTH, file)) {
        int line_len = StrLen(line);
        line_count++;
        // Iterate through patterns
        int patterns_len = StrLen(patterns);
        int start_pos = 0;
        // Check if multiple patterns apply to same line
        int total_patterns = 0;
        int patterns_matching = 0;
        // Print: 0 - filename, 1 - line number, 2 - line
        int to_print[3] = {0, 0, 0};
        for (int i = 0; i < patterns_len; i++) {
          if (patterns[i] == ',') {
            char pattern[50] = {'\0'};
            SliceStr(patterns, pattern, start_pos, i);
            PrintMatchedLine(&patterns_matching, line, pattern, active_flags,
                             files_count, to_print, file_name, line_count,
                             line_len);
            total_patterns++;
            start_pos = i + 1;
          }
        }
        if (!active_flags->v) {
          if (patterns_matching) {
            matched_count++;
          }
        } else {
          if (patterns_matching >= total_patterns) {
            matched_count++;
          }
        }
        // Prevent line from printing if v flag is active and multiple matterns
        // are present
        if (active_flags->v && patterns_matching != total_patterns) {
          continue;
        }
        // Print file name if more than one file and h flag is inactive
        if (to_print[0]) {
          printf("%s:", file_name);
        }
        // Print line number if n flag is active
        if (to_print[1]) {
          printf("%d:", line_count);
        }
        // Print line
        if (to_print[2]) {
          printf("%s", line);
        }
        // Print space at the end of file
        if (to_print[2] && line[line_len - 1] != '\n') {
          printf("\n");
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
      fprintf(stderr, "grep: %s: No such file or directory\n", file_name);
    }
  }
}