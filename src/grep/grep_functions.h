

#ifndef SRC_GREP_FUNCTIONS_H_
#define SRC_GREP_FUNCTIONS_H_

#include <stdbool.h>

typedef struct GrepFlags {
  bool e; // pattern
  bool i; // Ignore uppercase vs. lowercase.
  bool v; // Invert match.
  bool c; // Output count of matching lines only.
  bool l; // Output matching files only.
  bool n; // Precede each matching line with a line number.
  bool h; // Output matching lines without preceding them by file names.
  bool s; // Suppress error messages about nonexistent or unreadable files.
  bool f; // Take regexes from a file.
  bool o; // Output the matched parts of a matching line.
} grepFlags;

void ReadPatternFromFile(char *file_name, char *patterns);
void PrintMatch(char *pattern, char *text, grepFlags *active_flags);
void PrintMatchedLine(int *patterns_matching, char *line, char *pattern,
                      grepFlags *active_flags, int files_count, int *to_print,
                      char *file_name, int line_count, int line_len);
void ReadGrepFile(char *file_name, grepFlags *active_flags, char *patterns,
                  int files_count);

#endif // SRC_GREP_FUNCTIONS_H_