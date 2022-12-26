#ifndef LAB_06_DATA_TYPES_H
#define LAB_06_DATA_TYPES_H


#include <stddef.h>


typedef enum errors
{
	OK = 0,
	READ_ERR = 1,
	FILE_ERR = 2,
	CHOICE_ERR = 3,
	MEM_ALLOC_ERR = 4
} errors_t;


typedef struct node
{
	int data;
	size_t depth;
	struct node* left;
	struct node* right;
} node_t;


typedef struct tree
{
	size_t total_elems;
	node_t *head;
} tree_t;


#endif //LAB_06_DATA_TYPES_H
