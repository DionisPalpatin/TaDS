#ifndef LAB_01_CONSTANTS_H
#define LAB_01_CONSTANTS_H

#define MANTISSA_LEN 30
#define EXP_LEN 6
#define STR_NUM_LEN (MANTISSA_LEN + EXP_LEN + 7)
#define BASE 10

#define RAW_EXP_MIN (-99999)
#define RAW_EXP_MAX (+99999)
#define NORM_EXP_MIN (-99999 - 30)
#define NORM_EXP_MAX (+99999 + 30)
#define ZERO (NORM_EXP_MIN - 1)

#define GREETING "\n"
#define ENTRY_PROMPT "Please enter the next number:\n"
#define ERROR "Number entered incorrectly!"
#define CORRECT_NUMS_FORMATS "\n123, .00025, +123001., –123.456, 1234567 Е –20, 1234567 Е 20, 123.4567 Е23\n"
#define REPEAT_ONCE_MORE (ERROR \
						  "Correct number formats:\n\t" \
						  CORRECT_NUMS_FORMATS \
						  "Please enter the number again:\n")

#endif
