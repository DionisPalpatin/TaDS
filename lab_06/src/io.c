#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <io.h>
#include <tree.h>
#include <data_types.h>
#include <constants.h>


void greetings(void)
{
	printf(COLOR_GREEN"\n\n\nHello!\n\n\n"COLOR_RESET);
}


void print_menu(void)
{
	printf(COLOR_BLUE"%s" COLOR_RESET "%s",
		   "\n\nMENU (select one item, enter a number):\n\n",
		   "1 - load tree from file;\n"
		   "2 - add new number to tree and to file;\n"
		   "3 - print tree in graphic form;\n"
		   "4 - calculate quantity of nodes on each level;\n"
		   "5 - measure sorting time depending on tree structure;\n"
		   "6 - compare the time spent adding an element to the tree and to the file;\n"
		   "7 - menu;\n"
		   "0 - program exit.\n"
	);
}


void input_prompt(void)
{
	printf(COLOR_BLUE"%s"COLOR_RESET"%s","\n\nEnter 17 to display the menu", "\nEnter your choice: ");
}


void print_tree(tree_t *tree)
{
	assert(tree);
	if (tree->total_elems == 0)
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

	fprintf(f_out, "digraph TREE_GRAPH {\n");

	node_t *prev_node = tree->head;
	if (prev_node->left)
		print_branch(f_out, prev_node->left, prev_node);
	if (prev_node->right)
		print_branch(f_out, prev_node->right, prev_node);

	if (!prev_node->right && !prev_node->left)
		fprintf(f_out)

	fprintf(f_out, "}\n");

	fclose(f_out);

	system("dot -Tpng res.dot -o res.png");
	system("open res.png");
}


void print_branch(FILE *out, node_t *cur_node, node_t *prev_node)
{
	assert(cur_node && prev_node && out);

	if (cur_node->left)
		print_branch(out, cur_node->left, cur_node);
	if (cur_node->right)
		print_branch(out, cur_node->right, cur_node);
	fprintf(out, "%d -> %d;\n", prev_node->data, cur_node->data);
}