#include <stdio.h>

#include <graph.h>
#include <io.h>
#include <data_types.h>
#include <constants.h>
#include <measurements.h>


errors_t menu(road_graph_t *roads, road_graph_t *res_dists)
{
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
					exit_code = load_graph_from_file(SRC_FILE_NAME, roads);
					break;

				case 2:
					print_road_graph(roads);
					break;

				case 3:
					exit_code = floyd_warshall(roads, res_dists);
					break;

				case 4:
					print_matrix(res_dists->roads_matrix, res_dists->total_cities, res_dists->total_cities);
					break;

				case 5:
					compare_realizations(1);
					break;

				case 6:
					print_menu();
					break;

				case 100500:
					compare_realizations(0);
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