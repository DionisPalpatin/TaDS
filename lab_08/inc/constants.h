#ifndef CONSTANTS_H_
#define CONSTANTS_H_


#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET    "\x1b[0m"

#define EPS 1e-9
#define INF 10000
#define TOTAL_TESTS_RUNS 12500

#define TABLE_DELIM_PART_FORMAT "%7s"
#define TABLE_HEADER_CELL_FORMAT "%7zu"
#define TABLE_CONT_CELL_FORMAT "%7d"

#define SRC_FILE_NAME "data/data/example.txt"
#define TEST_FILE_NAME_FORMAT "data/test/test_%d.txt"

#define FILE_ERR_MESS "Error: unable to find the file!\n"
#define STANDARD_ERR_MESS "Read error! Check the data.\n"
#define COMM_ERR_MESS "Error: command must be an integer number!\n"
#define CHOICE_ERR_MESS "Error: incorrect choice!\n"
#define MEM_ALLOC_ERR_MESS "Error: some memory error take place, rerun the program.\n"
#define WAY_ERR_MESS "Error: no way was found!\n"


#endif