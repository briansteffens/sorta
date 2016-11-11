#ifndef HEAP_H
#define HEAP_H

#include "sorta.h"

typedef struct
{
    void* data;
    int size;
    int len;
    compare_function compare;
} heap;

void* heap_value(heap* heap, int entry);

int heap_parent(heap* heap, int child);
int heap_child_left(heap* heap, int parent);
int heap_child_right(heap* heap, int parent);
int heap_child_count(heap* heap, int parent);
int heap_largest_child(heap* heap, int parent);

void heap_rebalance_down(heap* heap, int start);

void heap_add(heap* heap, void* new_item);
void heap_remove_first(heap* heap);

#endif
