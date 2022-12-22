//
// Created by dionis on 02.12.22.
//


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

#include <measurements.h>
#include <data_types.h>
#include <sort.h>
#include <load_data.h>


unsigned long long milliseconds_now(void)
{
	struct timeval val;

	if (gettimeofday(&val, NULL))
		return (unsigned long long) -1;

	return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}


void compare_sorts(table_t *const table)
{
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);
	printf(HEADER4);
	printf(MAIN_DELIM);

	char *file_names[] = {"test_data_50.txt", "test_data_100.txt", "test_data_250.txt", "test_data_500.txt", "test_data_1000.txt"};
	size_t total_els[] = {50, 100, 250, 500, 1000};
	size_t iters = 5;

	for (size_t i = 0; i < iters; ++i)
	{
		long double t_bubble_res = 0, t_quick_res = 0, k_bubble_res = 0, k_quick_res = 0;
		size_t counter = 10200;

		// Память сортировками занята одинаковая
		size_t mem_used_table = sizeof(theater_t) * total_els[i];
		size_t mem_used_key = sizeof(keys_t) * total_els[i];

		// Загружаем таблицу во временную переменную
		table_t test_table = {.size = 0};
		(void) load_data_from_file(&test_table, file_names[i]);

		// Измерение сортировки пузырьком основной таблицы
		t_bubble_res = run_test(&test_table, counter, sort_table_bubble);

		// Измерение быстрой сортировки основной таблицы
		t_quick_res = run_test(&test_table, counter, sort_table_quick_sort);

		// Измерение сортировки пузырьком таблицы ключей
		k_bubble_res = run_test(&test_table, counter, sort_key_table_bubble);

		// Измерение быстрой сортировки таблицы ключей
		k_quick_res = run_test(&test_table, counter, sort_key_table_quick_sort);

		printf(ENTRY_LINE_1, mem_used_table, mem_used_table, mem_used_key, mem_used_key);
		printf(ENTRY_DELIM, total_els[i]);
		printf(ENTRY_LINE_2, t_bubble_res, t_quick_res, k_bubble_res, k_quick_res);
		printf(MAIN_DELIM);
	}
}


long double run_test(const table_t *table, size_t iters, void (*sort_func)(table_t *))
{
	table_t table_copy = {.size = 0};
	long long unsigned start = 0, end = 0, res = 0;

	for (uint64_t i = 0; i < iters; ++i)
	{
		memcpy(&table_copy, table, sizeof(table_t));

		start = milliseconds_now();
		sort_func(&table_copy);
		end = milliseconds_now();

		res += end - start;
	}

	return (long double) res / iters;
}