#include "common_modules.h"

#include <stdbool.h>
#include <stdio.h>

int StrLen(char *str) {
  int len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

bool StrIncludesChar(char *str, char c) {
  bool result = false;
  int strL = StrLen(str);
  for (int i = 0; i < strL; i++) {
    if (str[i] == c) {
      result = true;
    }
  }
  return result;
}

void StrToLowercase(char *str) {
  int str_len = StrLen(str);
  for (int i = 0; i < str_len; i++) {
    if (str[i] >= 65 && str[i] <= 90) {
      str[i] = str[i] + 32;
    }
  }
}

void SliceStr(char *str, char *result, int from, int to) {
  for (int i = 0; i < to - from; i++) {
    result[i] = str[from + i];
  }
  result[to - from] = '\0';
}

void AppendStr(char *str1, char *str2, char separator) {
  int str1_len = StrLen(str1);
  int str2_len = StrLen(str2);
  for (int i = 0; i < str2_len; i++) {
    str1[str1_len + i] = str2[i];
  }
  str1[str1_len + str2_len] = separator;
  str1[str1_len + str2_len + 1] = '\0';
}
