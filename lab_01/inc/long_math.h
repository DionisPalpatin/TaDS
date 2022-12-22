#ifndef APP_EXE_LONG_MATH_H
#define APP_EXE_LONG_MATH_H


#include <structs.h>


void long_mult(const int *num1, const int *num2, int *result);
void long_sum(int *num1, int *num2, size_t iter);

int mult_exp_form_long_numbers(num_t *num1, num_t *num2, num_t *res);

bool check_mantissa_overflow(int *result);
bool check_exponent_overflow(int *exponent);


#endif
