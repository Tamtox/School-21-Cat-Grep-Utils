#ifndef SRC_S21_COMMON_H_
#define SRC_S21_COMMON_H_

#include <stdbool.h>

int StrLen(char *str);
bool StrIncludesChar(char *str, char c);
void StrToLowercase(char *str);
void SliceStr(char *str, char *result, int from, int to);
void AppendStr(char *str1, char *str2, char separator);

#endif // SRC_S21_COMMON_H_
