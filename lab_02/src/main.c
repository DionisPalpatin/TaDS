//
// Created by dionis on 03.12.22.
//


#include <data_types.h>
#include <io.h>
#include <menu.h>


int main(void)
{
	error_t exit_code = 0;
	table_t table = {.size = 0};

	greetings();
	exit_code = menu(&table);

	return exit_code;
}