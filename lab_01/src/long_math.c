#include <long_math.h>


/**
 * @brief Функция умножения двух целых чисел, представленных в виде массивов длиной 30 символов типа int.
 * @param num1 - первый множитель.
 * @param num2 - второй множитель.
 * @param result - указатель на массив, в который надо записать результат.
 */
void long_mult(const int *num1, const int *num2, int *result)
{
	int intermediate_result[MANTISSA_LEN * 2] = {0};
	int final_result[MANTISSA_LEN * 2] = {0};

	for (size_t i = 29; i >= 0 && num1[i]; --i)
	{
		int remainder = 0;
		for (size_t j = 29; j >= 0 && num2[j]; --j)
		{
			intermediate_result[j + MANTISSA_LEN] = (num1[i] * num2[j] + remainder) % 10;
			remainder = (num1[i] * num2[j] + remainder) / 10;
		}

		long_sum(final_result, intermediate_result, i);
	}
}


/**
 * @brief Функция сложения двух целых чисел, представленных в виде массивов длиной 30 символов типа int.
 * Используется в функции умножения.
 * @param num1 - первое слагаемое, сюда же записывается и результат.
 * @param num2 - второе слагаемое.
 * @param iter - текущая итерация умножения, то есть то, на сколько надо умножить слагаемое num2.
 */
void long_sum(int *num1, int *num2, size_t iter)
{
	for (size_t i = 0; i < MANTISSA_LEN * 2 - iter; ++i)
		num2[i] = num2[i + iter];
	for (size_t i = MANTISSA_LEN * 2 - 1; i >= MANTISSA_LEN * 2 - iter; --i)
		num2[i] = 0;

	int tmp[MANTISSA_LEN * 2];
	int remainder = 0;
	for (size_t i = MANTISSA_LEN * 2; i > 0; --i)
	{
		tmp[i] = (num1[i - 1] + num2[i - 1] + remainder) % 10;
		remainder = (num1[i - 1] * num2[i - 1] + remainder) / 10;
	}

	for (size_t i = 0; i < MANTISSA_LEN * 2; ++i)
		num1[i] = tmp[i];
}


int mult_exp_form_long_numbers(num_t *num1, num_t *num2, num_t *res)
{

}