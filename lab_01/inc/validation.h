#ifndef APP_EXE_VALIDATION_H
#define APP_EXE_VALIDATION_H


#include <stdbool.h>


bool validate_num(const char *number);
inline bool validate_exp_form(const char *num, const char *e_pos);
inline bool validate_normal_form(const char *num);

#endif
