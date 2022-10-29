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

int strLen (char *str);
bool strIncludesChar (char *str, char c);
char checkStrFlags (char *flag);
void readFile(char *fileName, catFlags *activeFlags);

#endif // SRC_S21_COMMON_H_

