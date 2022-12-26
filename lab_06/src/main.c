#include <io.h>
#include <tree.h>
#include <menu.h>


int main(void)
{
   	tree_t tree = {.total_elems = 0, .head = NULL};
	errors_t exit_code = OK;

	exit_code = menu(&tree);

	free_tree(&tree);

	return exit_code;
}