#ifndef APP_EXE_STRUCTS_H
#define APP_EXE_STRUCTS_H

#include <stddef.h>
#include <stdbool.h>

#include "constants.h"


/**
 * Данная структура является представлением числа в моей программе.
 * Число при вводе автоматически приводится к нормализованному виду, поэтому мантисса хранит только числа после точки.
 * Знаки лежат в отдельных переменных типа bool (если ноль, значит число положительное, 1 - отрицательное).
 */
typedef struct number
{
    int mantissa[MANTISSA_LEN];
    int exponent[EXP_LEN];

    bool mant_sign;
    bool exp_sign;
} num_t;

typedef struct nums_storage
{
    num_t first_num;
    num_t sec_num;
    num_t multiply;
} nums_storage_t;

typedef struct prog_state
{
    bool repeat_input;
    bool no_nums_changes;
} prog_state_t;

#endif
