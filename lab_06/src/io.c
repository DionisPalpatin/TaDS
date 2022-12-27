#include <stdio.h>

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

}