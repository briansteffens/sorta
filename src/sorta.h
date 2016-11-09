#ifndef SORTA_H
#define SORTA_H

#include <stdbool.h>

typedef int (*compare_function)(void*, void*);

typedef struct
{
    void* data;
    int size;
    int len;
    compare_function compare;
} heap;

int compare_int(void* left, void* right);

void insertion_sort(void* list, int size, int items, compare_function compare);
void selection_sort(void* list, int size, int items, compare_function compare);
void bubble_sort(void* list, int size, int items, compare_function compare);
void shell_sort(void* list, int size, int len, compare_function compare,
                int gaps[], int gaps_len);
void merge_sort(void* list, int size, int len, compare_function compare);

void heap_add(heap* heap, void* new);

#endif
