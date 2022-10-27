#include <stdio.h>
#include "s21_cat.h"
#include "../common/common_modules.h"

int main() {
    char input[1000]; 
    get_command_input (input);
    printf("\n%s",input);
    return 0;
}