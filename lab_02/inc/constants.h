//
// Created by dionis on 28.11.22.
//

#ifndef LAB_02_CONSTANTS_H
#define LAB_02_CONSTANTS_H


#define GNZ 2500000000 // 2.5 ГГц тактовая частота моего процессора по ТТХ


#define DATA_FILE "../datas/data.txt"


#define DELIMITER ":"


#define TRUE 1
#define FALSE 0


#define THEATER_FIELD "Theater"
#define PERF_FIELD "Performance"
#define PROD_FIELD "Producer"
#define MIN_PRICE_FIELD "Minimum price"
#define MAX_PRICE_FIELD "Maximum price"
#define TYPE_FIELD "Type"
#define MIN_AGE_FIELD "Minimum age"
#define MAX_AGE_FIELD "Maximum age"
#define GENRE_FIELD "Genre"
#define COMP_FIELD "Composer"
#define COUNTRY_FIELD "Country"
#define DUR_FIELD "Duration"


#define MAX_THEATER_NAME_LEN 20
#define MAX_PERF_NAME_LEN 20
#define MAX_PROD_NAME_LEN 20
#define MAX_COMP_NAME_LEN 20
#define MAX_COUNTRY_NAME_LEN 20
#define MAX_TABLE_SIZE 1000


#define FLAG_DUR (-1)
#define FLAG_AGE (-1)
#define FLAG_PRICE (-1)


#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"


#define SOME_STR "|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n"
#define KEY_TABLE_HEADER_FORMAT "| %10s | %30s |\n"
#define KEY_TABLE_LINE_FORMAT "| %10zu | %30s |\n"
#define TABLE_HEADER_FORMAT "| %20s | %20s | %20s | %10s | %10s | %20s | %20s | %20s | %10s | %10s | %20s | %5s |\n"
#define TABLE_CHILD_FORMAT "| %20s | %20s | %20s | %10ld | %10ld | %20s | %20s | %20s | %10ld | %10ld | %20s | %5s |\n"
#define TABLE_ADULT_FORMAT "| %20s | %20s | %20s | %10ld | %10ld | %20s | %20s | %20s | %10s | %10s | %20s | %5s |\n"
#define TABLE_MUS_FORMAT "| %20s | %20s | %20s | %10ld | %10ld | %20s | %20s | %20s | %10ld | %10s | %20s | %5ld |\n"


#define HEADER1 "|---------------|--------|-------------------------------------|-------------------------------------|\n"
#define HEADER2 "|               |        |             Main table              |              Key table              |\n"
#define HEADER3 "| Total entries |  What  |-------------------------------------|-------------------------------------|\n"
#define HEADER4 "|               |        |      Bubble      |      Quick       |      Bubble      |      Quick       |\n"
#define MAIN_DELIM "|---------------|--------|------------------|------------------|------------------|------------------|\n"
#define ENTRY_LINE_1 "|               | Memory |%18zu|%18zu|%18zu|%18zu|\n"
#define ENTRY_DELIM "|%15zu|--------|------------------|------------------|------------------|------------------|\n"
#define ENTRY_LINE_2 "|               |  Time  |%18Lf|%18Lf|%18Lf|%18Lf|\n"


#define TABLE_OVERFLOW_ERR_MESS "Error: table has reached its maximum size!\n"
#define TABLE_ERR_MESS "Error: table is not creat yet!\n"
#define FILE_ERR_MESS "Error: unable to find the file!\n"
#define DATA_ALLOC_ERR_MESS "Error: Unable to allocate new value!\n"
#define DATA_LEN_ERR_MESS "Error: input data must not be zero length!\n"
#define USED_FIELD_ERR_MESS "Error: This field has already been defined!\n"
#define TYPE_NOT_DEFINE_ERR_MESS "Error: Performance type was not defined!\n"
#define TYPE_ATTR_ERR_MESS "Error: Invalid field for the specified performance type!\n"
#define STANDART_ERR_MESS "Read error! Check the data.\n"
#define PERF_ERR_MESS "Error: Invalid view name! Check the input data.\nRemember that the maximum length of the title is 20 characters.\n"
#define THEATER_ERR_MESS "Error: Incorrect theater name! Please check the input data.\nRemember that the maximum length of the title is 20 characters.\n"
#define PROD_ERR_MESS "Error: Invalid director name! Please check your input.\nRemember that the maximum name length is 20 characters.\n"
#define COMP_ERR_MESS "Error: Invalid composer name! Please check your input.\nRemember that the maximum name length is 20 characters.\n"
#define CNTR_ERR_MESS "Error: Invalid country name! Please check the input data.\nRemember that the maximum length of the title is 20 characters.\n"
#define TYPE_ERR_MESS "Error: Invalid performance type! Check the input data.\nPossible types: child, adult, musical.\n"
#define GENRE_ERR_MESS "Error: Incorrect genre of the performance.\nPossible genres: for children - fairy tale and play, for adults - play, drama and comedy.\n"
#define PRICE_ERR_MESS "Error: Incorrect price per view! Check the input.\n"
#define AGE_ERR_MESS "Error: incorrect value of the age limit! Please check your input.\n"
#define DUR_ERR_MESS "Error: Incorrect performance duration! Please check your input.\n"


#endif //LAB_02_CONSTANTS_H
