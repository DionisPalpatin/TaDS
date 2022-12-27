#ifndef TREE_H__
#define TREE_H__

#include <data_types.h>


void free_node(node_t *node);
void free_tree(tree_t *tree);
void free_branch(node_t *node);

void insert_node(node_t *cur_node, node_t *new_node, size_t cur_depth);
node_t* create_node(int node_data);
node_t* find_node(node_t *cur_node, int node_data);

void init_tree(tree_t *tree, size_t total_nums);
errors_t read_tree_from_file(const char *file_name, tree_t *tree);
errors_t read_nums(FILE *src, tree_t *tree);
errors_t add_node(tree_t *tree);

void sort_tree(tree_t *tree, size_t *sorted_arr, size_t *cur_len);
void sort_branch(node_t *cur_node, size_t *sorted_arr, size_t *cur_len);

void calculate_nodes(node_t *cur_node, size_t *depths);
void explore_depths(tree_t *tree);


#endif