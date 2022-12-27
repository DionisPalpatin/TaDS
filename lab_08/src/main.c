#include <stdio.h>

#include <menu.h>
#include <data_types.h>
#include <io.h>

int main()
{
	setbuf(stdin, NULL);
	errors_t exit_code;

	road_graph_t roads = {.total_cities = 0, .roads_matrix = NULL};
	road_graph_t res_dists = {.total_cities = 0, .roads_matrix = NULL};

	greetings();
	exit_code = menu(&roads, &res_dists);

	return exit_code;
}
