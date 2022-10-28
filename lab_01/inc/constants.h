#ifndef LAB_01_CONSTANTS_H
#define LAB_01_CONSTANTS_H

#define MANTISSA_LEN 30
#define EXP_LEN 5
#define STR_NUM_LEN (MANTISSA_LEN + EXP_LEN + 7)
#define BASE 10

#define GREETING "\n"
#define ENTRY_PROMPT "Пожалуйста, введите следующее число:\n"
#define ERROR "Число введено некорректно!"
#define CORRECT_NUMS_FORMATS "\n123, n00025, +123001., –123.456, 1234567 Е –20, 1234567 Е 20, 123.4567 Е23\n"
#define PRINT_ONCE_MORE ("Правильные форматы чисел:\n\t" \
                        CORRECT_NUMS_FORMATS \
                        "Пожалуйста, введите число еще раз:\n")

#endif
