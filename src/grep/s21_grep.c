#include <stdio.h>
#include "s21_grep.h"
#include "../common/common_modules.h"

int main() {
    char *str = parse_input("This is grep");
    printf("%s",str);
    return 0;
}