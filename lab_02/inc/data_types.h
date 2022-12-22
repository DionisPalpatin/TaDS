//
// Created by dionis on 28.11.22.
//

#ifndef LAB_02_DATA_TYPES_H
#define LAB_02_DATA_TYPES_H


#include <stddef.h>

#include <constants.h>


typedef long price_t;
typedef long age_t;
typedef long dur_t;


// ----------------------------------------------------------
// Возможные ошибки
typedef enum
{
	OK = 0,
	READ_ERR = 1,
	FILE_ERR = 2,
	STR_SIZE_ERR = 3,
	PRICE_ERR = 5,
	OVERFLOW_TABLE = 6,
	AGE_ERR = 7,
	GENRE_ERR = 8,
	DUR_ERR = 9,
	TYPE_ERR = 10,
	UNKNOWN_FIELD = 11,
	USED_FIELD_ERR = 12,
	TYPE_NOT_DEFINE_ERR = 13,
	TYPE_ATTR_ERR = 14,
} error_t;
// ----------------------------------------------------------


// ----------------------------------------------------------
// Типы спектаклей
typedef enum which_perf
{
	no_choice = 0,
	child = 1,
	adult = 2,
	musical = 3,
} which_perf_t;


typedef enum child_perf_types
{
	not_defined_c = 0,
	fairy_tale = 1,
	c_play = 2
} child_perf_t;


typedef enum adult_perf_types
{
	not_defined_g = 0,
	g_play = 1,
	drama = 2,
	comedy = 3
} adult_perf_t;
// ----------------------------------------------------------


// ----------------------------------------------------------
// Характеристики спектаклей
typedef struct child
{
	age_t min_age;
	age_t max_age;
	child_perf_t type;
} child_t;


typedef struct adult
{
	adult_perf_t type;
} adult_t;


typedef struct musical
{
	char comp[MAX_COMP_NAME_LEN + 1];
	char country[MAX_COUNTRY_NAME_LEN + 1];
	age_t min_age;
	dur_t dur;
} musical_t;
// ----------------------------------------------------------


// ----------------------------------------------------------
// Все возможные виды спектаклей
typedef union perf_type
{
	child_t child;
	adult_t adult;
	musical_t musical;
} perf_t;
// ----------------------------------------------------------


// ----------------------------------------------------------
// Информация о театре
typedef struct theater
{
	char name[MAX_THEATER_NAME_LEN + 1];
	char perf[MAX_PERF_NAME_LEN + 1];
	char prod[MAX_PROD_NAME_LEN + 1];
	price_t min_price;
	price_t max_price;
	which_perf_t for_whom;
	perf_t type;
} theater_t;
// ----------------------------------------------------------


// ----------------------------------------------------------
// Таблица ключей для сортировки. Сортируется по минимальной цене билета
typedef struct key
{
	char perf_name[MAX_PERF_NAME_LEN + 1];
	size_t id;
} keys_t;
// ----------------------------------------------------------


// ----------------------------------------------------------
// Таблица всех записей
typedef struct table
{
	theater_t theaters[MAX_TABLE_SIZE];
	keys_t keys[MAX_TABLE_SIZE];
	size_t size;
} table_t;
// ----------------------------------------------------------


#endif //LAB_02_DATA_TYPES_H
