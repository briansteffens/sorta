#ifndef SORTO_H
#define SORTO_H

#include <stdbool.h>

typedef int (*compare_function)(void*, void*);

int compare_int(void* left, void* right);

bool is_sorted(void* list, int size, int items, compare_function compare);

void insertion_sort(void* list, int size, int items, compare_function compare);
void selection_sort(void* list, int size, int items, compare_function compare);
void bubble_sort(void* list, int size, int items, compare_function compare);

#endif
