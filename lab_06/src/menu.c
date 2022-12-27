//
// Created by dionis on 25.12.22.
//
#include <assert.h>
#include <stdio.h>

#include <menu.h>
#include <data_types.h>
#include <constants.h>
#include <io.h>
#include <tree.h>


errors_t menu(tree_t *tree, size_t *depths)
{
	assert(tree);
	print_menu();
	input_prompt();

	errors_t exit_code = OK;
	int menu_item = 1;
	int read_status = scanf("%d", &menu_item);

	while (menu_item != 0)
	{
		if (read_status != 1)
			err_message(COMM_ERR_MESS);
		else
			switch (menu_item)
			{
				case 1:
					exit_code = read_tree_from_file(SRC_FILE_NAME, tree);
					break;

				case 2:
					exit_code = add_node(tree);
					break;

				case 3:
//					print_road_graph(roads);
					break;

				case 4:
					explore_depths(tree);
					break;

				case 5:

					break;

				case 6:

					break;

				case 7:
					print_menu();
					break;

				// Menu option for otchet only
				case 100500:

					break;

				default:
					err_message("Error: unknown command!\n");
					break;
			}

		input_prompt();
		fflush(stdin);
		setbuf(stdin, NULL);
		read_status = scanf("%d", &menu_item);
	}

	return exit_code;
}
