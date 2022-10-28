#ifndef SRC_S21_COMMON_H_
#define SRC_S21_COMMON_H_

// struct catInputs {
//     char *command;
//     char *flags;
//     char **fileNames;
//     bool commandError = false;
//     bool flagsError = false;
//     char *filenameErrors;
// };

int strLen (char *str);
// char *getStrUntillSpaceEnd (char *str, int startPos);
void readFile(char *fileName);
// char *get_command_input (char *str);
// struct  catInputs parse_command_input (char* input);

#endif // SRC_S21_COMMON_H_

