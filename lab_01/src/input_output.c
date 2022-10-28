#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#include <input_output.h>
#include <constants.h>
#include <structs.h>


void write_num_to_struct(const char *num_str, num_t *num);

int get_num(num_t *num, prog_state_t *prog_state)
{
    assert(num && prog_state);

    /*
     * exit_code = код выхода из функции
     * num_str - строка, содержащая вводимую в консоль строку (по факту строковое представление введенного числа)
     * src_stream - поток ввода
     */
    int exit_code = OK;
    wchar_t num_str[STR_NUM_LEN + 1];
    FILE *src_stream = stdin;

    num_str[STR_NUM_LEN] = '0'; // Проверка переполнения. Если будет введена слишком длинная строка, этот символ == '\0'
    if (!fgetws(num_str, STR_NUM_LEN + 1, src_stream))
        exit_code = READ_ERROR;
    else if ()

    return exit_code;
}

bool validate_num(num_t *number);