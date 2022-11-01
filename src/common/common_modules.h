#ifndef SRC_S21_COMMON_H_
#define SRC_S21_COMMON_H_

typedef struct CatFlags {
    bool b; // numbers only non-empty lines
    bool E; // implies -v but also display end-of-line characters as $
    bool n; // number all output lines
    bool s; // squeeze multiple adjacent blank lines
    bool T; // implies -v but also display tabs as ^I
    bool v;
} catFlags;

typedef struct GrepFlags {
    bool e; // pattern
    bool i; // Ignore uppercase vs. lowercase.
    bool v; // Invert match.
    bool c; // Output count of matching lines only.
    bool l; // Output matching files only.
    bool n; // Precede each matching line with a line number.
} grepFlags;

int StrLen (char *str);
bool StrIncludesChar (char *str, char c);
char CheckStrFlags (char *flag);
void SliceStr (char *str, char *result, int from , int to);
void AppendStr (char *str1, char *str2);
int CatLineNumeration (bool numerate_full_lines, bool numerate_lines, int line_count, char line_start);
void ReadCatFile(char *fileName, catFlags *activeFlags);
// void ReadGrepFile(char *fileName, catFlags *active_flags, char *patterns);

#endif // SRC_S21_COMMON_H_

