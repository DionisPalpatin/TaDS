#ifndef CONSTANTS_H_
#define CONSTANTS_H_


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <locale.h>
#include <string.h>


#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET    "\x1b[0m"

#define MAX_MATRIX_SIZE        150
#define MAX_MATRIX_ELEMS       (MAX_MATRIX_SIZE * MAX_MATRIX_SIZE)

#define TOTAL_TEST_RUNS 10000

#define MTR_FILE_FORMAT_LINE "./datas/data/mtr_%d_%d.txt"
#define VEC_FILE_FORMAT_LINE "./datas/data/vec_%d_%d.txt"


#define FILE_ERR_MESS "Error: unable to find the file!\n"
#define STANDARD_ERR_MESS "Read error! Check the data.\n"
#define COMM_ERR_MESS "Error: command must be an integer number!\n"
#define CHOICE_ERR_MESS "Error: incorrect choice!\n"
#define NON_ZERO_QUAN_ERR_MESS "Error: incorrect quantity of non-zero elements!\n"
#define MTR_SIZE_ERR_MESS "Error: incorrect matrix size!\n"
#define MULT_ERR_MESS "Error: matrices cannot be multiplied, sizes is not correct!\n"
#define MEM_ALLOC_ERR_MESS "Error: some memory error take place, rerun the program.\n"


#endif
