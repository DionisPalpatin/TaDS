#ifndef MEASUREMENTS_H__
#define MEASUREMENTS_H__


#include "constants.h"
#include "tree.h"
#include "hash.h"

int search_file(FILE *f, int num);
void timememory1(int len);
void timememory(node_t *head, node_t *headbal, inttable_t *table, FILE *f);


#endif