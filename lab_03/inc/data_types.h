//
// Created by dionis on 11.12.22.
//

#ifndef LAB_03_DATA_TYPES_H
#define LAB_03_DATA_TYPES_H


#include <constants.h>


typedef enum error
{
	OK = 0,
	READ_ERR = 1,
	FILE_ERR = 2,
	MTR_SIZE_ERR = 3,
	CHOICE_ERR = 4,
	NON_ZERO_QUAN_ERR = 5,
	MULT_ERR = 6,
	MEM_ALLOC_ERR = 7
} error_t;


typedef struct matrix_std
{
	int rows;
	int cols;
	int data[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
} matrix_std_t;

//typedef struct list_elem
//{
//	int index;
//	struct list_elem *next;
//} list_elem_t;

// матрица в разреженном виде
typedef struct matrix_sparse
{
	int rows;
	int cols;
	int quan;
	int values[MAX_MATRIX_ELEMS]; // AN
	int cols_indexes[MAX_MATRIX_ELEMS]; // JA
	int rows_beginnings[MAX_MATRIX_SIZE + 1]; // IA
} matrix_sparse_t;


#endif //LAB_03_DATA_TYPES_H
