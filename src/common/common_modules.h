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
    bool e; // numbers only non-empty lines
    bool i; // implies -v but also display end-of-line characters as $
    bool v; // number all output lines
    bool c; // squeeze multiple adjacent blank lines
    bool l; // implies -v but also display tabs as ^I
    bool n;
} grepFlags;

int StrLen (char *str);
bool StrIncludesChar (char *str, char c);
char CheckStrFlags (char *flag);
int CatLineNumeration (bool numerate_full_lines, bool numerate_lines, int line_count, char line_start);
void ReadCatFile(char *fileName, catFlags *activeFlags);

#endif // SRC_S21_COMMON_H_

