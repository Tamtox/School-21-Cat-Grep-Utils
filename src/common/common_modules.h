#ifndef SRC_S21_COMMON_H_
#define SRC_S21_COMMON_H_

typedef struct CatFlags {
    bool b; // numbers only non-empty lines
    bool E; // implies -v but also display end-of-line characters as $
    bool n; // number all output lines
    bool s; // squeeze multiple adjacent blank lines
    bool T; // implies -v but also display tabs as ^I
    bool v; // Print imprintable chars
} catFlags;

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

int StrLen (char *str);
bool StrIncludesChar (char *str, char c);
void StrToLowercase (char *str);
char CheckStrFlags (char *flag);
void SliceStr (char *str, char *result, int from , int to);
void AppendStr (char *str1, char *str2, char separator);
int CatLineNumeration (bool numerate_full_lines, bool numerate_lines, int line_count, char line_start);
void ReadCatFile(char *fileName, catFlags *activeFlags);
void ReadPatternFromFile (char *file_name, char *patterns);
void PrintMatchedLine(int *line_count, int *matched_count, char *line, char *pattern, grepFlags *active_flags, char *file_name, int files_count);
void ReadGrepFile(char *file_name, grepFlags *active_flags, char *patterns, int files_count);

#endif // SRC_S21_COMMON_H_

