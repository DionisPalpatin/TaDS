//
// Created by dionis on 02.12.22.
//
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <sort.h>
#include <data_types.h>
#include <table.h>


void sort_table_bubble(table_t *table)
{
	assert(table);

	for (size_t i = 0; i < table->size; ++i)
		for (size_t j = 0; j < table->size - 1 - i; ++j)
		{
			theater_t *first = table->theaters + j;
			theater_t *sec = table->theaters + j + 1;
			if (compare_table_els(first, sec) > 0)
				swap(first, sec, sizeof(theater_t));
		}
}


void sort_table_quick_sort(table_t *table)
{
	qsort(table->theaters, table->size, sizeof(theater_t), compare_table_els);
}


void sort_key_table_bubble(table_t *table)
{
	assert(table);

	for (size_t i = 0; i < table->size; ++i)
		for (size_t j = 0; j < table->size - 1 - i; ++j)
		{
			keys_t *first = table->keys + j;
			keys_t *sec = table->keys + j + 1;
			if (compare_key_els(first, sec) > 0)
				swap(first, sec, sizeof(keys_t));
		}
}


void sort_key_table_quick_sort(table_t *table)
{
	qsort(table->keys, table->size, sizeof(keys_t), compare_key_els);
}


void sort_keys(table_t *table)
{
	if (table->size == 0)
	{
		printf("Таблица еще не сформирована.\n");
		return;
	}

	printf("Выберите тип сортировки:\n1 - сортировка пузырьком;\n2 - быстрая сортировка;\nВведите 1 или 2: ");
	int status;
	int choice;

	status = scanf("%d", &choice);
	if (status != 1 || (choice != 1 && choice != 2))
		printf("Ошибка: введено неверное значение!\n");
	else if (choice == 1)
		sort_key_table_bubble(table);
	else
		sort_key_table_quick_sort(table);
}


void sort_table(table_t *table)
{
	if (table->size == 0)
	{
		printf("Таблица еще не сформирована.\n");
		return;
	}

	printf("Выберите тип сортировки:\n1 - сортировка пузырьком;\n2 - быстрая сортировка;\nВведите 1 или 2: ");
	int status;
	int choice;

	status = scanf("%d", &choice);
	if (status != 1 || (choice != 1 && choice != 2))
		printf("Ошибка: введено неверное значение!\n");
	else
	{
		if (choice == 1)
			sort_table_bubble(table);
		else
			sort_table_quick_sort(table);

		creat_key_table(table);
	}
}


void swap(void *first, void *sec, size_t size)
{
	char temp[size];

	memcpy(temp, first, size);
	memcpy(first, sec, size);
	memcpy(sec, temp, size);
}


int compare_table_els(const void *ptr1, const void *ptr2)
{
	return strcmp(((theater_t *)(ptr1))->perf, ((theater_t *)(ptr2))->perf);
}


int compare_key_els(const void *ptr1, const void *ptr2)
{
	return strcmp(((keys_t *)(ptr1))->perf_name, ((keys_t *)(ptr2))->perf_name);
}
