#define _POSIX_C_SOURCE 200809L // Ради getline'а

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <read.h>
#include <data_types.h>
#include <io.h>


/**
 * @brief Функция, читающая строку из потока ввода stream (файл или stdin).
 * @param[in] stream - поток ввода.
 * @param[out] str - строка, в которую надо поместить прочитанную строку.
 * @param[in,out] len - указатель на переменную, в которую будет записана длина строки.
 * @return 0, если все хорошо, иначе код ошибки.
 */
error_t read_string(FILE *stream, char **str, size_t *len)
{
	assert(str && len);

	error_t exit_code = OK;
	*len = 0;
	ssize_t read_status;

	if (stream == stdin)
	{
		fflush(stdin);
		setbuf(stdin, NULL);
	}

	read_status = getline(str, len, stream);

	if (read_status < 0)
	{
		err_message(STANDART_ERR_MESS);
		exit_code = READ_ERR;
	}
	else if (*len == 0)
	{
		exit_code = STR_SIZE_ERR;
		err_message(DATA_LEN_ERR_MESS);
	}

	// Читаем из файла же, в том числе, последняя строка может и не содержать символ новой строки. Удаляем его
	if (exit_code == OK)
	{
		char *new_line_sym = strchr(*str, '\n');
		if (new_line_sym)
			*new_line_sym = '\0';
	}

	return exit_code;
}


/**
 * @brief Функция чтения очередного параметра из потока ввода stream. Функция требует, чтобы первая часть каждой строки
 * содержала имя поля, в которое нужно записать значение, вторая - само значение, и чтобы части были разделены двоеточием.
 * @param stream - поток ввода.
 * @param theater - указатель на переменную, хранящую информацию об афише.
 * @return 0, если все хорошо, иначе код ошибки.
 */
error_t get_new_value(FILE *stream, theater_t *theater)
{
	assert(theater);

	error_t exit_code;
	size_t str_len = 0;
	char *new_str = NULL;

	exit_code = read_string(stream, &new_str, &str_len);

	char *field_type = NULL;
	char *field_value = NULL;
	char new_str_copy[str_len + 1];

	if (exit_code == OK)
	{
		strcpy(new_str_copy, new_str);

		str_len = 0;
		field_type = strtok(new_str_copy, DELIMITER);
		field_value = strtok(NULL, DELIMITER);

		if (!field_type || !field_value)
		{
			exit_code = READ_ERR;
			err_message(DATA_ALLOC_ERR_MESS);
		}
		else
			str_len = strlen(field_value);
	}

	if (str_len == 0)
	{
		exit_code = STR_SIZE_ERR;
		err_message(DATA_ALLOC_ERR_MESS);
	}

	if (exit_code == OK)
	{
		if (strcmp(THEATER_FIELD, field_type) == 0)
			exit_code = put_value_to_string_field(field_value, theater->name, str_len, MAX_THEATER_NAME_LEN, THEATER_ERR_MESS);
		else if (strcmp(PERF_FIELD, field_type) == 0)
			exit_code = put_value_to_string_field(field_value, theater->perf, str_len, MAX_PERF_NAME_LEN, PERF_ERR_MESS);
		else if (strcmp(PROD_FIELD, field_type) == 0)
			exit_code = put_value_to_string_field(field_value, theater->prod, str_len, MAX_PROD_NAME_LEN, PROD_ERR_MESS);
		else if (strcmp(MIN_PRICE_FIELD, field_type) == 0)
			exit_code = put_value_to_price_field(field_value, &(theater->min_price));
		else if (strcmp(MAX_PRICE_FIELD, field_type) == 0)
			exit_code = put_value_to_price_field(field_value, &(theater->max_price));
		else if (strcmp(TYPE_FIELD, field_type) == 0)
			exit_code = put_value_to_type_field(field_value, theater);
		else
			exit_code = put_value_to_attr_field(field_type, field_value, theater);
	}

	free(new_str);

	return exit_code;
}


error_t get_new_value_from_stdin(theater_t *theater, const char *field_type)
{
	assert(theater);

	error_t exit_code;
	size_t str_len = 0;
	char *new_str = NULL;

	exit_code = read_string(stdin, &new_str, &str_len);

	if (str_len == 0 && exit_code == OK)
	{
		exit_code = STR_SIZE_ERR;
		err_message(DATA_LEN_ERR_MESS);
	}
	else if (exit_code == OK)
		str_len = strlen(new_str);

	if (exit_code == OK)
	{
		if (strcmp(THEATER_FIELD, field_type) == 0)
			exit_code = put_value_to_string_field(new_str, theater->name, str_len, MAX_THEATER_NAME_LEN, THEATER_ERR_MESS);
		else if (strcmp(PERF_FIELD, field_type) == 0)
			exit_code = put_value_to_string_field(new_str, theater->perf, str_len, MAX_PERF_NAME_LEN, PERF_ERR_MESS);
		else if (strcmp(PROD_FIELD, field_type) == 0)
			exit_code = put_value_to_string_field(new_str, theater->prod, str_len, MAX_PROD_NAME_LEN, PROD_ERR_MESS);
		else if (strcmp(MIN_PRICE_FIELD, field_type) == 0)
			exit_code = put_value_to_price_field(new_str, &(theater->min_price));
		else if (strcmp(MAX_PRICE_FIELD, field_type) == 0)
			exit_code = put_value_to_price_field(new_str, &(theater->max_price));
		else if (strcmp(TYPE_FIELD, field_type) == 0)
			exit_code = put_value_to_type_field(new_str, theater);
		else
			exit_code = put_value_to_attr_field(field_type, new_str, theater);
	}

	free(new_str);

	return exit_code;
}


/**
 * @brief Функция, записывающая строку в поле структуры. Проверка на то, заполнено ли поле и нормальной ли длины
 * переданная в функцию строка, происходят непосредственно внутри функции.
 * @param[in] src_str - строка, которую нужно записать.
 * @param[out] dest_field - поле, в которую нужно записать строку.
 * @param[in] len - длина переданной строки.
 * @param[in] max_len - максимально возможная длина строки.
 * @param[in] err_mess - сообщение, которое будет выведено в случае некорректной длины.
 * @return 0, если все хорошо, иначе код ошибки.
 */
error_t put_value_to_string_field(const char *src_str, char *dest_field, size_t len, size_t max_len, const char *err_mess)
{
	assert(src_str && dest_field && max_len > 0 && err_mess);

	error_t exit_code = OK;

	if (dest_field[0])
	{
		err_message(USED_FIELD_ERR_MESS);
		exit_code = USED_FIELD_ERR;
	}
	else if (len > max_len)
	{
		err_message(err_mess);
		exit_code = STR_SIZE_ERR;
	}
	else
		strcpy(dest_field, src_str);

	return exit_code;
}


/**
 * @brief Функция записи считанной цены в соответсвующее поле структуры. Проверка на корректность цены происходит внутри
 * функции.
 * @param[in] src_str - строка, из которой вычленяется число.
 * @param[out] dest_field - указатель на поле, в которое нужно записать число.
 * @return 0, если все хорошо, иначе код ошибки.
 */
error_t put_value_to_price_field(const char *src_str, price_t *dest_field)
{
	assert(src_str && dest_field);

	error_t exit_code = OK;

	if (*dest_field != FLAG_PRICE)
	{
		err_message(USED_FIELD_ERR_MESS);
		exit_code = USED_FIELD_ERR;
	}
	else
	{
		char *end_ptr = NULL;
		price_t new_price = strtol(src_str, &end_ptr, 10);

		if (*end_ptr || new_price <= 0)
		{
			exit_code = PRICE_ERR;
			err_message(PRICE_ERR_MESS);
		}
		else
			*dest_field = new_price;
	}

	return exit_code;
}


error_t put_value_to_age_field(const char *src_str, age_t *dest_field)
{
	assert(src_str && dest_field);

	error_t exit_code = OK;

	if (*dest_field != FLAG_AGE)
	{
		err_message(USED_FIELD_ERR_MESS);
		exit_code = USED_FIELD_ERR;
	}
	else
	{
		char *end_ptr = NULL;
		age_t new_age = strtol(src_str, &end_ptr, 10);

		if (*end_ptr || new_age < 0)
		{
			exit_code = AGE_ERR;
			err_message(AGE_ERR_MESS);
		}
		else
			*dest_field = new_age;
	}

	return exit_code;
}


error_t put_value_to_dur_field(const char *src_str, dur_t *dest_field)
{
	assert(src_str && dest_field);

	error_t exit_code = OK;

	if (*dest_field != FLAG_DUR)
	{
		err_message(USED_FIELD_ERR_MESS);
		exit_code = USED_FIELD_ERR;
	}
	else
	{
		char *end_ptr = NULL;
		price_t new_dur = strtol(src_str, &end_ptr, 10);

		if (*end_ptr || new_dur <= 0)
		{
			exit_code = PRICE_ERR;
			err_message(PRICE_ERR_MESS);
		}
		else
			*dest_field = new_dur;
	}

	return exit_code;
}


error_t put_value_to_type_field(const char *src_str, theater_t *theater)
{
	assert(src_str && theater);

	error_t exit_code = OK;

	if (theater->for_whom != no_choice)
	{
		exit_code = USED_FIELD_ERR;
		err_message(USED_FIELD_ERR_MESS);
	}
	else if (strcmp(src_str, "child") == 0)
	{
		theater->for_whom = child;
		theater->type.child.type = not_defined_c;
		theater->type.child.min_age = FLAG_AGE;
		theater->type.child.max_age = FLAG_AGE;
	}
	else if (strcmp(src_str, "adult") == 0)
	{
		theater->for_whom = adult;
		theater->type.adult.type = not_defined_g;
	}
	else if (strcmp(src_str, "musical") == 0)
	{
		theater->for_whom = musical;
		theater->type.musical.comp[0] = '\0';
		theater->type.musical.country[0] = '\0';
		theater->type.musical.min_age = FLAG_AGE;
		theater->type.musical.dur = FLAG_DUR;
	}
	else
	{
		exit_code = TYPE_ERR;
		err_message(TYPE_ERR_MESS);
	}

	return exit_code;
}


error_t put_value_to_attr_field(const char *field_type, const char *field_value, theater_t *theater)
{
	assert(field_type && field_value && theater);

	error_t exit_code = OK;

	if (theater->for_whom == no_choice)
	{
		exit_code = TYPE_NOT_DEFINE_ERR;
		err_message(TYPE_NOT_DEFINE_ERR_MESS);
	}
	else if (strcmp(COMP_FIELD, field_type) == 0)
	{
		if (theater->for_whom == musical)
			exit_code = put_value_to_string_field(field_value, theater->type.musical.comp, strlen(field_value), MAX_COMP_NAME_LEN, COMP_ERR_MESS);
		else
		{
			exit_code = TYPE_ATTR_ERR;
			err_message(TYPE_ERR_MESS);
		}
	}
	else if (strcmp(COUNTRY_FIELD, field_type) == 0)
	{
		if (theater->for_whom == musical)
			exit_code = put_value_to_string_field(field_value, theater->type.musical.country, strlen(field_value), MAX_COUNTRY_NAME_LEN, CNTR_ERR_MESS);
		else
		{
			exit_code = TYPE_ATTR_ERR;
			err_message(TYPE_ERR_MESS);
		}
	}
	else if (strcmp(MIN_AGE_FIELD, field_type) == 0)
	{
		if (theater->for_whom == musical)
			exit_code = put_value_to_age_field(field_value, &(theater->type.musical.min_age));
		else if (theater->for_whom == child)
			exit_code = put_value_to_age_field(field_value, &(theater->type.child.min_age));
		else
		{
			exit_code = TYPE_ATTR_ERR;
			err_message(TYPE_ERR_MESS);
		}
	}
	else if (strcmp(MAX_AGE_FIELD, field_type) == 0)
	{
		if (theater->for_whom == child)
			exit_code = put_value_to_age_field(field_value, &(theater->type.child.max_age));
		else
		{
			exit_code = TYPE_ATTR_ERR;
			err_message(TYPE_ERR_MESS);
		}
	}
	else if (strcmp(DUR_FIELD, field_type) == 0)
	{
		if (theater->for_whom == musical)
			exit_code = put_value_to_dur_field(field_value, &(theater->type.musical.dur));
		else
		{
			exit_code = DUR_ERR;
			err_message(DUR_ERR_MESS);
		}
	}
	else if (strcmp(GENRE_FIELD, field_type) == 0)
		exit_code = put_value_to_genre_field(field_value, theater);


	return exit_code;
}


error_t put_value_to_genre_field(const char *genre, theater_t *theater)
{
	assert(genre && theater);

	error_t exit_code = OK;

	if (strcmp(genre, "play") == 0)
	{
		if (theater->for_whom == child)
			theater->type.child.type = c_play;
		else if (theater->for_whom == adult)
			theater->type.adult.type = g_play;
		else
		{
			exit_code = GENRE_ERR;
			err_message(GENRE_ERR_MESS);
		}
	}
	else if (strcmp(genre, "fairy tale") == 0)
	{
		if (theater->for_whom == child)
			theater->type.child.type = fairy_tale;
		else
		{
			exit_code = GENRE_ERR;
			err_message(GENRE_ERR_MESS);
		}
	}
	else if (strcmp(genre, "comedy") == 0)
	{
		if (theater->for_whom == adult)
			theater->type.adult.type = comedy;
		else
		{
			exit_code = GENRE_ERR;
			err_message(GENRE_ERR_MESS);
		}
	}
	else if (strcmp(genre, "drama") == 0)
	{
		if (theater->for_whom == adult)
			theater->type.adult.type = drama;
		else
		{
			exit_code = GENRE_ERR;
			err_message(GENRE_ERR_MESS);
		}
	}
	else
	{
		exit_code = TYPE_ATTR_ERR;
		err_message(TYPE_ATTR_ERR_MESS);
	}

	return exit_code;
}
