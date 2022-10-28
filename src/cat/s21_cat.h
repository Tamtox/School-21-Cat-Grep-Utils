#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

struct catFlags {
    bool b = false; // numbers only non-empty lines
    bool e = false; // 
    bool n = false; // number all output lines
    bool s = false; // squeeze multiple adjacent blank lines
    bool t;
    bool u;
    bool v;

};

#endif // SRC_S21_CAT_H_