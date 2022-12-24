#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <constants.h>
#include <data_types.h>
#include <graph.h>
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
			"7 - compare matrix realization and list;\n"
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


void print_list_as_matrix(road_graph_list_t *roads)
{
	assert(roads);

	for (size_t i = 0; i < roads->total_cities; ++i)
	{
		int dists[roads->total_cities];

		for (size_t j = 0; j < roads->total_cities; ++j)
			dists[i] = INF;
		for (conn_city_t *j = roads->cities[i].next; j != NULL; j = j->next)
			dists[j->ind] = j->dist;

		for (size_t j = 0; j < roads->total_cities; ++j)
		{
			if (dists[j] == INF)
				printf("%7s", "INF");
			else
				printf("%7d", dists[j]);
		}
		printf("\n");
	}
}


void print_meas_results_tables(long double results[10][2], size_t sizes[10][2])
{
	printf("|---------------|----------|-------------------------|-------------------------|\n"
		   "|  Matrix size  |   What   |     Graph as matrix     |      Graph as list      |\n"
		   "|---------------|----------|-------------------------|-------------------------|\n");

	for (int i = 0; i < 10; ++i)
	{
		printf("|               |Time (ms) |%25Lf|%25Lf|\n", results[i][0], results[i][1]);
		printf("|%15d|----------|-------------------------|-------------------------|\n", i * 5 + 5);
		printf("|               |Memory(b) |%25zu|%25zu|\n", sizes[i][0], sizes[i][1]);
		printf("|---------------|----------|-------------------------|-------------------------|\n");
	}

	printf("\n\n\n");
	printf("|---------------|--------------|-------------------------|\n"
		   "|  Matrix size  |     What     |        Comparison       |\n"
		   "|---------------|--------------|-------------------------|\n");

	for (int i = 0; i < 10; ++i)
	{
		printf("|               |  Time ratio  |%25Lf|\n", results[i][0] / results[i][1]);
		printf("|%15d|--------------|-------------------------|\n", i * 5 + 5);
		printf("|               | Memory ratio |%25lf|\n", (double)sizes[i][0] / sizes[i][1]);
		printf("|---------------|--------------|-------------------------|\n");
	}
}


void print_meas_results_tables_to_file(long double results[10][2], size_t sizes[10][2])
{
	FILE *out_f = fopen("res_file_format.txt", "w");
	if (!out_f)
		return;

	for (int i = 0; i < 10; ++i)
	{
		fprintf(out_f, "%25Lf %25Lf\n", results[i][0], results[i][1]);
		fprintf(out_f, "%25zu %25zu\n", sizes[i][0], sizes[i][1]);
	}

	fprintf(out_f, "\n\n\n");

	for (int i = 0; i < 10; ++i)
	{
		fprintf(out_f, "%25Lf\n", results[i][0] / results[i][1]);
		fprintf(out_f, "%25lf\n", (double)sizes[i][0] / sizes[i][1]);
	}

	fclose(out_f);
}



void err_message(const char *message)
{
	printf("%s%s%s", COLOR_RED, message, COLOR_RESET);
}
