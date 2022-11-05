

#ifndef SRC_CAT_FUNCTIONS_H_
#define SRC_CAT_FUNCTIONS_H_

#include <stdbool.h>

typedef struct CatFlags {
  bool b;  // numbers only non-empty lines
  bool E;  // implies -v but also display end-of-line characters as $
  bool n;  // number all output lines
  bool s;  // squeeze multiple adjacent blank lines
  bool T;  // implies -v but also display tabs as ^I
  bool v;  // Print imprintable chars
} catFlags;

char CheckStrFlags(char *flag);
int CatLineNumeration(bool numerate_full_lines, bool numerate_lines,
                      int line_count, char line_start);
void ReadCatFile(char *fileName, catFlags *active_flags);

#endif  // SRC_CAT_FUNCTIONS_H_