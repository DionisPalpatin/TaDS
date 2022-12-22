//
// Created by dionis on 02.12.22.
//


#include <stdio.h>
#include <assert.h>

#include <io.h>
#include <constants.h>
#include <data_types.h>


void greetings(void)
{
	printf(COLOR_GREEN "%s" COLOR_RESET "%s",
		   "\nHello! With this program you can: \n",
		   " - see the difference in the execution time of different sorting algorithms\n"
		   " - enter your own poster\n"
		   "- delete poster by some field\n"
		   " - sort only the key table, without touching the main one, and see the result\n"
		   " - display sorted table\n"
		   " - sort the key table and use them to display the source table in sorted form\n"
		   " - sort by two different algorithms and display the results\n\n\n");
}


void print_menu(void)
{
	printf("%s",
		   "Menu: \n"
		   "1 - Load table from file.\n"
		   "2 - Append entry to end of file.\n"
		   "3 - Delete the entry with the specified name.\n"
		   "4 - Sort the keymap and display it.\n"
		   "5 - Sort the table and display it.\n"
		   "6 - Sort the key table and use it to display the original table on the screen.\n"
		   "7 - Compare table sort time using algorithms complexity O(n^2) and O(n*log(n))\n"
		   " and compare the time of normal sorting and sorting by key table.\n"
		   "8 - List all musical performances for children of the specified age\n"
		   " with duration less than specified.\n"
		   "9 - Display table on screen.\n"
		   "10 - Clear table.\n"
		   "11 - Menu.\n"
		   "0 - Quit.\n");
}


void input_prompt(void)
{
	printf(COLOR_BLUE"%s"COLOR_RESET"%s","\n\nEnter 11 to display the menu", "\nEnter your choice: ");
}


void print_table(const table_t *table)
{
	assert(table);

	if (table->size == 0)
	{
		err_message(TABLE_ERR_MESS);
		return;
	}

	print_header();
	for (size_t i = 0; i < table->size; ++i)
		print_entry(table->theaters + i);
}


void print_entry(const theater_t *theater)
{
	assert(theater);

	if (theater->for_whom == child)
	{
		char *type = theater->type.child.type == fairy_tale ? "Fairy tale" : "Play";
		printf(TABLE_CHILD_FORMAT, theater->name, theater->perf, theater->prod, theater->min_price,
			   theater->max_price, "child", "-", "-", theater->type.child.min_age,
			   theater->type.child.max_age, type, "-");
	}
	else if (theater->for_whom == adult)
	{
		char *type = theater->type.adult.type == g_play ? "Play" : theater->type.adult.type == drama ? "Drama" : "Comedy";
		printf(TABLE_ADULT_FORMAT, theater->name, theater->perf, theater->prod, theater->min_price,
			   theater->max_price, "adult", "-", "-", "-", "-", type, "-");
	}
	else
	printf(TABLE_MUS_FORMAT, theater->name, theater->perf, theater->prod, theater->min_price,
		   theater->max_price, "Musical", theater->type.musical.comp, theater->type.musical.country,
		   theater->type.musical.min_age, "-", "-", theater->type.musical.dur);
}


void print_header(void)
{
	printf(SOME_STR);
	printf(TABLE_HEADER_FORMAT, "Theater", "Performance", "Producer", "Min price", "Max price",
		   "Perf. type", "Composer", "Country", "Min age.", "Max age.", "Genre", "Dur.");
	printf(SOME_STR);
}


void print_table_use_keys(const table_t *table)
{
	assert(table);

	if (table->size == 0)
	{
		err_message(TABLE_ERR_MESS);
		return;
	}

	print_header();
	for (size_t i = 0; i < table->size; ++i)
		print_entry(table->theaters + (table->keys[i].id));
}


void print_keys(const table_t *table)
{
	assert(table);

	if (table->size == 0)
	{
		err_message(TABLE_ERR_MESS);
		return;
	}

	print_key_header();
	for (size_t i = 0; i < table->size; i++)
		printf(KEY_TABLE_LINE_FORMAT, table->keys[i].id, table->keys[i].perf_name);
}


void print_key_header(void)
{
	printf(KEY_TABLE_HEADER_FORMAT, "id", "Performance name");
}


void err_message(const char *message)
{
	printf("%s%s%s", COLOR_RED, message, COLOR_RESET);
}
