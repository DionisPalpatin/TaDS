#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include <input_output.h>
#include <constants.h>
#include <structs.h>
#include <validation.h>


/**
 * @brief Перевод числа из строки в структуру.
 * @param num_str - указатель на строковое представление числа.
 * @param num - указатель на структуру, в которую надо записать число.
 */
void write_num_to_struct(const char *num_str, num_t *num)
{
	// Проверяем наличие знака у мантиссы и записываем значение в mant_neg в структуру
	if (*num_str == '+' || *num_str == '-')
	{
		num->mant_neg = *num_str == '+' ? 0 : 1;
		num_str++;
	}
	else
		num->mant_neg = 0;

	// Запись в структуру мантиссы и экспоненты
	const char *e = strchr(num_str, 'E');
	const char *last_mantissa_sym = e ? strchr(num_str, ' ') - 1 : strchr(num_str, '\0') - 1;

	for (size_t i = 29; last_mantissa_sym >= num_str; --last_mantissa_sym, --i)
		num->mantissa[i] = *last_mantissa_sym - '0';
	num->exponent = e ? (int)strtol(e + 1, NULL, BASE) : 0;

	// Нормализация числа
	int shift = (int)dot_shift(num_str);
	if (shift != ZERO)
}


/**
 * @brief Функция, выполняющая нормализацию числа (то есть сдвиг точки с изменением мантиссы при необходимости).
 * @param num_str - указатель на строковое представление числа.
 * @return Количество символов, на которое нужно сдвинуть точку (положительное, отрицательное или ноль - знак отвечает
 		   за направление сдвига, если минус, то в сторону начала числа, плюс - в сторону его конца).
 */
size_t dot_shift(const char *num_str)
{
	size_t shift = 0;

	const char *non_zero = num_str;
	for (; *non_zero == '0' || *non_zero == '.'; ++non_zero);

	if ((*non_zero == ' ' || *non_zero == '\0') && *(non_zero - 1) == 0)
		return ZERO;

	const char *dot = strchr(num_str, '.');
	if (dot)
		shift = non_zero > dot ? non_zero - (dot + 1) : non_zero - dot;
	else
		for (shift = -1; *non_zero != ' ' && *non_zero; --shift);

	return shift;
}


/**
 * @brief Функция, выполняющая считывание числа (из консоли, например), выполняющая его проверку и затем записывающая
   в структуру.
 * @param num - указатель на структуру, в которую необходимо записать число.
 * @param prog_state - указатель на структуру, хранящую настройки программы и ее состояние.
 * @return Ненулевой код в случае ошибка или нулевой код в случае успеха.
 */
int get_num(num_t *num, prog_state_t *prog_state)
{
    assert(num && prog_state);

    int exit_code = OK;
	char num_str[STR_NUM_LEN];
	num_str[STR_NUM_LEN - 1] = '0'; // Проверка переполнения. Если будет введена слишком длинная строка, этот символ == '\0'

    /*
     Проверяется, надо ли повторять ввод. Если да, запускается цикл, который не
     окончится, пока не будет введено неправильное значение, иначе после первой
     же неправильной попытки ввод будет закончен, и пользователю выведется на
     экран главное меню.
    */
    if (prog_state->repeat_input)
    {
        bool correct_input = false;
        while (!correct_input)
        {
            exit_code = read_number(num_str);
            if (!exit_code)
                correct_input = true;
            else
                printf(REPEAT_ONCE_MORE);
        }
    }
    else
    {
	    exit_code = read_number(num_str);
	}

	if (!exit_code && validate_num(num_str))
		write_num_to_struct(num_str, num);
	else if (!exit_code)
		exit_code = NUM_ERROR;

    return exit_code;
}


/**
 * @brief Функция, которая считывает число из потока ввода и проверяет, чтобы оно было правильной длины.
 * @param num_str - строка, в которую надо записать число.
 * @return Ненулевой код в случае ошибка или нулевой код в случае успеха.
 */
int read_number(char *num_str)
{
    assert(num_str);

    if (!fgets(num_str, STR_NUM_LEN + 1, stdin))
        return READ_ERROR;
    else if (num_str[STR_NUM_LEN] == '\0' || num_str[0] == '\n' || num_str[0] == '\0')
		return STR_ERROR;

    return OK;
}
