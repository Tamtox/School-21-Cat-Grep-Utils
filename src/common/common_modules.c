#include <stdio.h>
#include "common_modules.h"

char *get_command_input (char *str) {
    scanf("%[^\n]%*c",str);
    return str;
}

char *parse_command_input (char* input) {
    return  input;
}