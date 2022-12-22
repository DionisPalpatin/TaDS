#include <string.h>
#include <ctype.h>

#include <validation.h>
#include <structs.h>


/**
 * @brief Функция, выполняющая проверку числа.
 * @param number - строка с числом.
 * @return Ненулевой код в случае ошибка или нулевой код в случае успеха.
 */
bool validate_num(const char *number)
{
	bool valid = true;

	const char *e = strchr(number, 'E');
	if (e)
		valid = validate_exp_form(number, e);
	else
		valid = validate_normal_form(number);

	return valid;
}


/**
 * @brief Функция, выполняющая проверку числа, записанного в экспоненциальной форме.
 * @param num - строка с числом.
 * @param e_pos - указатель на ячейку, где находится E.
 * @return Ненулевой код в случае ошибка или нулевой код в случае успеха.
 */
inline bool validate_exp_form(const char *num, const char *e_pos)
{
	/*
	 Корректная форма: (+-)х Еу или (+-)х Е (+-)у, где х и у - это какие-то числа.
	 Поэтому Е должен быть как минимум третьим символом, перед ним должен быть пробел, после него или пробел, или
	 сразу число. После Е идти дробное число не может.
	 */
	if (e_pos < num + 3)
		return false;
	if (!*(e_pos + 1) || !*(e_pos + 2))
		return false;
	if (*(e_pos - 1) != ' ')
		return false;
	if (*(e_pos + 1) == '+' || *(e_pos + 1) == '-')
		return false;

	// Проверка мантиссы
	{
		const char *mant = num;
		if (*(mant) == '+' || *(mant) == '-')
		{
			mant++;
			if (*mant == '.')
				return false;
		}

		for (; isdigit(*mant); ++mant);
		if (*mant == '.' && *(mant + 1) == ' ')
			for (++mant; isdigit(*mant); ++mant);

		if ((*mant == ' ' && *(mant + 1) != 'E') || (!isdigit(*mant) && *mant != ' '))
			return false;
	}

	// Проверка экспоненты
	{
		const char *exp = *(e_pos + 1) != ' ' ? e_pos + 1 : e_pos + 2;
		if (*exp == '+' || *exp == '-')
			exp++;

		for (; isdigit(*exp); ++exp);

		if (*exp != '\0')
			return false;
	}

	return true;
}


/**
 * @brief Функция, выполняющая проверку числа, записанного не в экспоненциальной форме.
 * @param num - строка с числом.
 * @return Ненулевой код в случае ошибка или нулевой код в случае успеха.
 */
inline bool validate_normal_form(const char *num)
{
	if (*(num) == '+' || *(num) == '-')
	{
		num++;
		if (*num == '.')
			return false;
	}

	for (; isdigit(*num); ++num);
	if (*num == '.')
		for (++num; isdigit(*num); ++num);

	if (*(num))
		return false;

	return true;
}
