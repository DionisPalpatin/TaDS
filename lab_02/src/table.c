#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <table.h>
#include <data_types.h>
#include <io.h>
#include <load_data.h>


/**
 * @brief Создание таблицы ключей по существующей таблице данных.
 * @param table - указатель на таблицу.
 */
void creat_key_table(table_t *table)
{
	assert(table);

	if (table->size == 0)
		printf("Таблица еще не сформирована.\n");
	else
		for (size_t i = 0; i < table->size; ++i)
		{
			table->keys[i].id = i;
			strcpy(table->keys[i].perf_name, table->theaters[i].perf);
		}
}


/**
 * @brief Поиск записи. Данная функция предлагает пользователю ввести имя спектакля, который нужно найти, проводит все
 * необходимые проверки и, если все хорошо, выводит на экран или требуемую запись, или сообщение, что такой записи нет.
 * @param table - указатель на таблицу.
 */
void find_entries(const table_t *table)
{
	assert(table);

	if (table->size == 0)
	{
		printf("Таблица еще не сформирована.\n");
		return;
	}

	printf("Enter your age and maximum duration in minutes separated by a space "
		   "(there are records with a duration less than the specified): ");
	age_t age;
	dur_t over_dur;
	if (scanf("%ld %ld", &age, &over_dur) != 2)
	{
		err_message(STANDART_ERR_MESS);
		return;
	}

	print_header();
	for (size_t i = 0; i < table->size; ++i)
		if (table->theaters[i].for_whom == musical)
		{
			age_t min_age = table->theaters[i].type.musical.min_age;
			dur_t dur = table->theaters[i].type.musical.dur;
			if (age >= min_age && over_dur > dur)
				print_entry(table->theaters + i);
		}
}


/**
 * @brief Удаление записи по названию спектакля. Данная функция предлагает пользователю ввести имя спектакля, который
 * нужно удалить, проводит все необходимые проверки и, если все хорошо, удаляет требуемую запись или выводит сообщение,
 * что такой записи нет.
 * @param table - указатель на таблицу.
 * @return 0, если все хорошо, код ошибки иначе.
 */
error_t delete_entry(table_t *table)
{
	assert(table);

	error_t exit_code = OK;

	if (table->size == 0)
	{
		err_message(TABLE_ERR_MESS);
		exit_code = OVERFLOW_TABLE;
		return exit_code;
	}

	printf("Input performance name: ");
	size_t len = 0;
	char *to_delete = NULL;
	fflush(stdin);
	setbuf(stdin, NULL);
	ssize_t success = getline(&to_delete, &len, stdin);

	if (success < 0)
	{
		err_message(STANDART_ERR_MESS);
		exit_code = READ_ERR;
	}

	char *new_line_sym = strchr(to_delete, '\n');
	if (new_line_sym)
		*new_line_sym = '\0';

	len = strlen(to_delete);
	if (len < 1 || len > MAX_PERF_NAME_LEN)
	{
		err_message(PERF_ERR_MESS);
		exit_code = STR_SIZE_ERR;
	}

	if (exit_code == OK)
	{
		size_t pos = get_entry_id(table, to_delete);
		if (pos < MAX_TABLE_SIZE)
		{
			for (size_t i = table->keys[pos].id; i < table->size; ++i)
				memcpy(table->theaters + i, table->theaters + i + 1, sizeof(theater_t));
			for (size_t i = pos; i < table->size; ++i)
				memcpy(table->keys + i, table->keys + i + 1, sizeof(keys_t));
			--(table->size);
		}
		else
			printf("Poster with this performance does not exist.\n");
	}

	return exit_code;
}


/**
 * @brief Функция получения индекса ключа в массиве (не поля id найденного ключа).
 * @param table - указатель на таблицу.
 * @param name - название спектакля, которого нужно найти.
 * @return
 */
size_t get_entry_id(const table_t *table, const char *name)
{
	assert(table);

	for (size_t i = 0; i < table->size; ++i)
		if (strcmp(table->keys[i].perf_name, name) == 0)
			return i;

	return MAX_TABLE_SIZE;
}


/**
 * @brief Функция добавления записи в конец существующей таблицы. Если таблицы нет, она создается. Если таблица уже
 * полностью заполнена, пользователю выводится соответствующее сообщение об этом.
 * @param table - указатель на таблицу.
 * @return 0, если все хорошо, иначе код ошибки.
 */
error_t add_entry(table_t *table)
{
	assert(table);

	error_t exit_code = OK;

	if (table->size == MAX_TABLE_SIZE)
	{
		exit_code = OVERFLOW_TABLE;
		err_message(TABLE_OVERFLOW_ERR_MESS);
	}

	if (exit_code == OK)
	{
		printf("Format of theater poster:\n"
			   "	Theater: *input here any string*\n"
			   "	Performance: *input here any string*\n"
			   "	Producer: *input here any string*\n"
			   "	Minimum price: *here you can only enter a positive integer*\n"
			   "	Maximum price: *here you can only enter a positive integer*\n"
			   "	Type: *child, adult or musical*\n"
			   "\n	After that, depending on the specified type, you will be prompted to enter:\n"
			   "		For the child type:\n"
			   "			Minimum age: *here you can only enter a positive integer*\n"
			   "			Maximum age: *here you can only enter a positive integer*\n"
			   "			Genre: *play or fairy tale*\n"
			   "		For the adult type:\n"
			   "			Genre: *play, drama or comedy*\n"
			   "		For the musical type:\n"
			   "			Composer: *input here any string*\n"
			   "			Country: *input here any string*\n"
			   "			Minimum age: *here you can only enter a non-negative integer*\n"
			   "			Maximum dur: *here you can only enter a positive integer*\n"
			   "\nRemember that spaces will be processed as part of inputted words, and maximum len of string fields is 20 symbols.\n"
			   "Keywords (Theater, Performance ans so on) will be printed on the screen as prompts.\n\n\n");

		exit_code = read_theater_info_from_stdin(table->theaters + table->size);
		if (exit_code == OK)
			++(table->size);
	}

	return exit_code;
}


/**
 * @brief Функция очищения таблицы. Очищение проходит очень просто: вся область памяти, выделенная под таблицу,
 * заполняется нулями. Так как таблица занимает всего 156008 байт, такой подход допустим.
 * @param table - указатель на таблицу.
 */
void clean_table(table_t *table)
{
	assert(table);

	memset(table, 0, sizeof(table_t));
}
