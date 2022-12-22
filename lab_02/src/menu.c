//
// Created by dionis on 03.12.22.
//
#include <stdio.h>

#include <data_types.h>
#include <menu.h>
#include <io.h>
#include <load_data.h>
#include <table.h>
#include <sort.h>
#include <measurements.h>


error_t menu(table_t *table)
{
	print_menu();
	input_prompt();

	error_t exit_code = OK;
	int menu_item = 1;
	int read_status = scanf("%d", &menu_item);

	while (menu_item != 0)
	{
		if (read_status != 1)
			printf("Некорректный ввод. Команда должна быть целым числом.\n");
		else
			switch (menu_item)
			{
				case 1:
					clean_table(table);
					exit_code = load_data_from_file(table, DATA_FILE);
					break;

				case 2:
					exit_code = add_entry(table);
					break;

				case 3:
					exit_code = delete_entry(table);
					break;

				case 4:
					sort_keys(table);
					print_keys(table);
					break;

				case 5:
					sort_table(table);
					print_table(table);
					break;

				case 6:
					sort_keys(table);
					print_table_use_keys(table);
					break;

				case 7:
					compare_sorts(table);
					break;

				case 8:
					find_entries(table);
					break;

				case 9:
					print_table(table);
					break;

				case 10:
					clean_table(table);
					break;

				case 11:
					print_menu();
					break;

				default:
					printf("Unknown command. The command must be between 0 and 11.\n");
					break;
			}

		input_prompt();
		fflush(stdin);
		setbuf(stdin, NULL);
		read_status = scanf("%d", &menu_item);
	}

	save_table_to_file(table, DATA_FILE);

	return exit_code;
}
