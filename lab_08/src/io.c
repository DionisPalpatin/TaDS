#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <constants.h>
#include <data_types.h>
#include <io.h>


void greetings(void)
{
		printf(COLOR_GREEN"\n\n\nHello!\n\n\n"COLOR_RESET);
}


void print_menu(void)
{
	printf(COLOR_BLUE"%s" COLOR_RESET "%s",
			"\n\nMENU (select one item, enter a number):\n\n",
			"1 - load graph from file;\n"
			"2 - load graph manually;\n"
			"3 - print graph with Graphviz;\n"
			"4 - find the path through all roads without repetition;\n"
			"5 - print found way;\n"
			"6 - print menu;\n"
			"0 - program exit.\n"
	);
}


void input_prompt(void)
{
	printf(COLOR_BLUE"%s"COLOR_RESET"%s","\n\nEnter 17 to display the menu", "\nEnter your choice: ");
}


void print_road_graph(road_graph_t *roads)
{
	assert(roads);
	if (roads->total_cities == 0)
	{
		err_message("Error: graph has no tops, build the graph for the first.\n");
		return;
	}

	FILE *f_out = fopen("res.dot", "w");
	if (!f_out)
	{
		err_message(FILE_ERR_MESS);
		return;
	}

	fprintf(f_out, "digraph ROAD_GRAPH {\n");
	for (size_t i = 0; i < roads->total_cities; ++i)
		for (size_t j = i + 1; j < roads->total_cities; ++j)
		{
			if (roads->roads_matrix[i][j] > 0 && roads->roads_matrix[i][j] < INF)
				fprintf(f_out, "%zu -> %zu [label=\"%d\"];\n", i, j, roads->roads_matrix[i][j]);
			if (roads->roads_matrix[j][i] > 0 && roads->roads_matrix[j][i] < INF)
				fprintf(f_out, "%zu -> %zu [label=\"%d\"];\n", j, i, roads->roads_matrix[j][i]);
		}
	fprintf(f_out, "}\n");

	fclose(f_out);

	system("dot -Tpng res.dot -o res.png");
	system("open res.png");
}


void print_matrix(int **matrix, size_t rows, size_t cols)
{
	assert(matrix);

	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			if (matrix[i][j] == INF)
				printf("%7s", "INF");
			else
				printf("%7d", matrix[i][j]);
		}
		printf("\n");
	}
}


void err_message(const char *message)
{
	printf("%s%s%s", COLOR_RED, message, COLOR_RESET);
}
