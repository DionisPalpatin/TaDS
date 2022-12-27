#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <tree.h>
#include <data_types.h>
#include <io.h>
#include <constants.h>


void free_node(node_t *node)
{
	free(node);
}


void free_tree(tree_t *tree)
{
	if (!tree->head)
		return;

	free_branch(tree->head);
}


void free_branch(node_t *node)
{
	if (!node)
		return;

	free_branch(node->right);
	free_branch(node->left);
	free_node(node);
}



node_t* create_node(int node_data)
{
    node_t *node = malloc(sizeof(node_t));

	if (node)
    {
		node->data = node_data;
        node->depth = 0;
        node->right = NULL;
        node->left = NULL;
    }
	else
	{
		err_message(MEM_ALLOC_ERR_MESS);
	}

    return node;    
}


node_t* find_node(node_t *cur_node, int node_data)
{
	assert(cur_node);

	if (cur_node->data == node_data)
		return cur_node;
	else if (node_data < cur_node->data)
		return find_node(cur_node->left, node_data);
	else if (node_data > cur_node->data)
		return find_node(cur_node->right, node_data);

    return NULL;
}


void insert_node(node_t *cur_node, node_t *new_node, size_t cur_depth)
{
	assert(cur_node && new_node);

	if (new_node->data < cur_node->data)
	{
		if (cur_node->left)
			insert_node(cur_node->left, new_node, ++cur_depth);
		else
		{
			cur_node->left = new_node;
			new_node->depth = cur_depth;
		}
	}
	else if (new_node->data > cur_node->data)
	{
		if (cur_node->right)
			insert_node(cur_node->right, new_node, ++cur_depth);
		else
		{
			cur_node->right = new_node;
			new_node->depth = cur_depth;
		}
	}
	else if (new_node->data < cur_node->data)
		free_node(new_node);
}


errors_t read_tree_from_file(const char *file_name, tree_t *tree)
{
	assert(file_name && tree);

	errors_t exit_code = OK;

	FILE *src_f = fopen(file_name, "r");
	if (!src_f)
	{
		err_message(FILE_ERR_MESS);
		exit_code = FILE_ERR;
	}

	size_t total_nums = 0;
	if (exit_code == OK && (fscanf(src_f, "%zu", &total_nums) != 1 || total_nums == 0))
	{
		err_message(STANDARD_ERR_MESS);
		exit_code = READ_ERR;
	}

	if (exit_code == OK)
	{
		init_tree(tree, total_nums);
		exit_code = read_nums(src_f, tree);
	}

	if (src_f)
		fclose(src_f);

	return exit_code;
}


errors_t read_nums(FILE *src, tree_t *tree)
{
	assert(src && tree);

	errors_t exit_code = OK;

	for (size_t i = 0; i < tree->total_elems && exit_code == OK; ++i)
	{
		int new_num = 0;

		if (fscanf(src, "%d", &new_num) != 1)
		{
			err_message(STANDARD_ERR_MESS);
			exit_code = READ_ERR;
		}
		else
		{
			node_t *new_node = create_node(new_num);
			if (new_node)
			{
				if (tree->head)
					insert_node(tree->head, new_node, 0);
				else
				{
					tree->head = new_node;
					new_node->depth = 0;
				}
			}
		}
	}

	return exit_code;
}


void init_tree(tree_t *tree, size_t total_nums)
{
	assert(tree);

	tree->head = NULL;
	tree->total_elems = total_nums;
}


errors_t add_node(tree_t *tree)
{
	assert(tree);

	errors_t exit_code = OK;
	int node_value = 0;

	printf("Input node value: ");
	fflush(stdin);
	setbuf(stdin, NULL);

	if (scanf("%d", &node_value) != 1)
	{
		exit_code = READ_ERR;
		err_message(STANDARD_ERR_MESS);
	}
	else
	{
		node_t *new_node = create_node(node_value);
		if (new_node)
			insert_node(tree->head, new_node, 0);
	}

	return exit_code;
}


void sort_tree(tree_t *tree, size_t *sorted_arr, size_t *cur_len)
{
	assert(tree && sorted_arr && cur_len);

	if (tree->total_elems == 0)
	{
		err_message(TREE_ERR_MESS);
		return;
	}

	sort_branch(tree->head, sorted_arr, cur_len);
}


void sort_branch(node_t *cur_node, size_t *sorted_arr, size_t *cur_len)
{
	if (!cur_node)
		return;

	sort_branch(cur_node->left, sorted_arr, cur_len);
	sorted_arr[(*cur_len)++] = cur_node->data;
	sort_branch(cur_node->right, sorted_arr, cur_len);
}


void calculate_nodes(node_t *cur_node, size_t *depths)
{
	assert(cur_node && depths);

	++(depths[cur_node->depth]);

	if (cur_node->left)
		explore_depths(cur_node, depths);
	if (cur_node->right)
		explore_depths(cur_node, depths);
}


void explore_depths(tree_t *tree)
{
	assert(tree);

	size_t depths[tree->total_elems];
	memset(depths, 0, sizeof(size_t) * tree->total_elems);

	calculate_nodes(tree->head, depths);

	printf("Results:\n");
	for (size_t i = 0; i < tree->total_elems && depths[i] != -1; ++i)
		printf("\tLevel %zu: %zu\n", i, depths[i]);
}
