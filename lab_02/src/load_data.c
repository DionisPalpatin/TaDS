#include <stdio.h>
#include <assert.h>

#include <load_data.h>
#include <constants.h>
#include <read.h>
#include <io.h>
#include <table.h>


error_t load_data_from_file(table_t *table, const char *file_name)
{
	assert(table);

	error_t exit_code;

	FILE *file = NULL;
	exit_code = open_file(&file, file_name, "r");

	while (exit_code == OK && !feof(file))
	{
		exit_code = read_theater_info(file, table->theaters + table->size);
		if (exit_code == OK)
			++(table->size);
	}

	if (exit_code == OK)
		creat_key_table(table);

	if (file)
		fclose(file);

	return exit_code;
}


error_t open_file(FILE **file, const char *file_name, const char *mode)
{
	assert(file);

	error_t exit_code = OK;

	*file = fopen(file_name, mode);
	if (!*file)
	{
		exit_code = FILE_ERR;
		err_message(FILE_ERR_MESS);
	}

	return exit_code;
}


error_t read_theater_info(FILE *file, theater_t *theater)
{
	assert(theater);

	error_t exit_code = OK;

	theater->name[0] = '\0';
	theater->perf[0] = '\0';
	theater->prod[0] = '\0';
	theater->min_price = FLAG_PRICE;
	theater->max_price = FLAG_PRICE;

	while (!end_of_input(theater) && exit_code == OK)
			exit_code = get_new_value(file, theater);

	return exit_code;
}


error_t read_theater_info_from_stdin(theater_t *theater)
{
	assert(theater);

	error_t exit_code;

	theater->name[0] = '\0';
	theater->perf[0] = '\0';
	theater->prod[0] = '\0';
	theater->min_price = FLAG_PRICE;
	theater->max_price = FLAG_PRICE;

	printf("Theater: ");
	exit_code = get_new_value_from_stdin(theater, THEATER_FIELD);

	if (!exit_code)
	{
		printf("Performance: ");
		exit_code = get_new_value_from_stdin(theater, PERF_FIELD);
	}

	if (!exit_code)
	{
		printf("Producer: ");
		exit_code = get_new_value_from_stdin(theater, PROD_FIELD);
	}

	if (!exit_code)
	{
		printf("Minimum price: ");
		exit_code = get_new_value_from_stdin(theater, MIN_PRICE_FIELD);
	}

	if (!exit_code)
	{
		printf("Maximum price: ");
		exit_code = get_new_value_from_stdin(theater, MAX_PRICE_FIELD);
	}

	if (!exit_code)
	{
		printf("Type: ");
		exit_code = get_new_value_from_stdin(theater, TYPE_FIELD);
	}

	if (!exit_code)
		switch (theater->for_whom)
		{
			case child:
				printf("Minimum age: ");
				exit_code = get_new_value_from_stdin(theater, MIN_AGE_FIELD);
				if (!exit_code)
				{
					printf("Maximum age: ");
					exit_code = get_new_value_from_stdin(theater, MAX_AGE_FIELD);
				}
				if (!exit_code)
				{
					printf("Genre: ");
					exit_code = get_new_value_from_stdin(theater, GENRE_FIELD);
				}
				break;

			case adult:
				printf("Genre: ");
				exit_code = get_new_value_from_stdin(theater, GENRE_FIELD);
				break;

			case musical:
				printf("Composer: ");
				exit_code = get_new_value_from_stdin(theater, COMP_FIELD);
				if (!exit_code)
				{
					printf("Country: ");
					exit_code = get_new_value_from_stdin(theater, COUNTRY_FIELD);
				}
				if (!exit_code)
				{
					printf("Minimum age: ");
					exit_code = get_new_value_from_stdin(theater, MIN_AGE_FIELD);
				}
				if (!exit_code)
				{
					printf("Duration: ");
					exit_code = get_new_value_from_stdin(theater, DUR_FIELD);
				}
				break;

			case no_choice:
				err_message("This is too much illegal:) Do not do what u do\n");
				exit_code = TYPE_ERR;
				break;

			default:
				err_message(TYPE_ERR_MESS);
				exit_code = TYPE_ERR;
				break;
		}

	return exit_code;
}


int end_of_input(theater_t *theater)
{
	assert(theater);

	if (theater->name[0] == '\0')
		return FALSE;
	if (theater->perf[0] == '\0')
		return FALSE;
	if (theater->prod[0] == '\0')
		return FALSE;
	if (theater->min_price == FLAG_PRICE)
		return FALSE;
	if (theater->max_price == FLAG_PRICE)
		return FALSE;

	if (theater->for_whom == no_choice)
		return FALSE;

	if (theater->for_whom == child)
	{
		if (theater->type.child.type == not_defined_c)
			return FALSE;
		if (theater->type.child.min_age == FLAG_AGE)
			return FALSE;
		if (theater->type.child.max_age == FLAG_AGE)
			return FALSE;
	}

	if (theater->for_whom == adult)
		if (theater->type.adult.type == not_defined_g)
			return FALSE;

	if (theater->for_whom == musical)
	{
		if (theater->type.musical.min_age == FLAG_AGE)
			return FALSE;
		if (theater->type.musical.dur == FLAG_DUR)
			return FALSE;
		if (theater->type.musical.country[0] == '\0')
			return FALSE;
		if (theater->type.musical.comp[0] == '\0')
			return FALSE;
	}

	return TRUE;
}


error_t save_table_to_file(table_t *table, const char *file_name)
{
	assert(table && file_name);

	error_t exit_code;

	FILE *file = NULL;
	exit_code = open_file(&file, file_name, "w");

	if (exit_code == OK)
		for (size_t i = 0; i < table->size; ++i)
		{
			fprintf(file, "Theater:%s\n", table->theaters[i].name);
			fprintf(file, "Performance:%s\n", table->theaters[i].perf);
			fprintf(file, "Producer:%s\n", table->theaters[i].prod);
			fprintf(file, "Minimum price:%ld\n", table->theaters[i].min_price);
			fprintf(file, "Maximum price:%ld\n", table->theaters[i].max_price);

			if (table->theaters[i].for_whom == child)
			{
				fprintf(file, "Type:%s\n", "child");
				fprintf(file, "Minimum age:%ld\n", table->theaters[i].type.child.min_age);
				fprintf(file, "Maximum age:%ld\n", table->theaters[i].type.child.max_age);

				if (table->theaters[i].type.child.type == c_play)
					fprintf(file, "Genre:%s", "play");
				else
					fprintf(file, "Genre:%s", "fairy tale");
			}
			else if (table->theaters[i].for_whom == adult)
			{
				fprintf(file, "Type:%s\n", "adult");
				if (table->theaters[i].type.adult.type == g_play)
					fprintf(file, "Genre:%s", "play");
				else if (table->theaters[i].type.adult.type == drama)
					fprintf(file, "Genre:%s", "drama");
				else
					fprintf(file, "Genre:%s", "comedy");
			}
			else
			{
				fprintf(file, "Type:%s\n", "musical");
				fprintf(file, "Composer:%s\n", table->theaters[i].type.musical.comp);
				fprintf(file, "Country:%s\n", table->theaters[i].type.musical.country);
				fprintf(file, "Minimum age:%ld\n", table->theaters[i].type.musical.min_age);
				fprintf(file, "Duration:%ld", table->theaters[i].type.musical.dur);
			}

			if (i != table->size - 1)
				fprintf(file, "%c", '\n');
		}

	if (file)
		fclose(file);

	return exit_code;
}
