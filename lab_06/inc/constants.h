#ifndef CONSTANTS_H__
#define CONSTANTS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define SRC_FILE_NAME "data/data/example.txt"
#define TEST_FILE_NAME_FORMAT "data/test/test_%d.txt"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET    "\x1b[0m"

#define FILE_ERR_MESS "Error: unable to find the file!\n"
#define STANDARD_ERR_MESS "Read error! Check the data.\n"
#define COMM_ERR_MESS "Error: command must be an integer number!\n"
#define CHOICE_ERR_MESS "Error: incorrect choice!\n"
#define MEM_ALLOC_ERR_MESS "Error: some memory error take place, rerun the program.\n"
#define TREE_ERR_MESS "Error: tree has not been created yet!\n"

#endif