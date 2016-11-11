#include <string.h>

#include "sorta.h"
#include "heap.h"

int heap_parent(heap* heap, int child)
{
    return (child - 1) / 2;
}

int heap_child_left(heap* heap, int parent)
{
    return parent * 2 + 1;
}

int heap_child_right(heap* heap, int parent)
{
    return parent * 2 + 2;
}

void* heap_value(heap* heap, int entry)
{
    return heap->data + entry * heap->size;
}

int heap_child_count(heap* heap, int parent)
{
    int left_i = heap_child_left(heap, parent);

    if (left_i >= heap->len)
        return 0;

    int right_i = heap_child_right(heap, parent);

    if (right_i >= heap->len)
        return 1;
    else
        return 2;
}

int heap_largest_child(heap* heap, int parent)
{
    int left_i = heap_child_left(heap, parent);
    void* left = heap_value(heap, left_i);

    int right_i = heap_child_right(heap, parent);

    if (right_i >= heap->len)
        return left_i;

    void* right = heap_value(heap, right_i);

    return heap->compare(left, right) > 0 ? left_i : right_i;
}

void heap_add(heap* heap, void* new)
{
    // Add the item to the end of the heap
    int current_i = heap->len++;
    memcpy(heap->data + current_i * heap->size, new, heap->size);

    // Rebalance the heap
    unsigned char temp[heap->size];
    void* current = heap_value(heap, current_i);

    // Swap newly-inserted item with its parent as long as parent is smaller
    while (true)
    {
        int parent_i = heap_parent(heap, current_i);
        void* parent = heap_value(heap, parent_i);

        if (heap->compare(current, parent) <= 0)
            break;

        mem_swap(current, parent, heap->size);

        current_i = parent_i;
        current = parent;
    }
}

void heap_rebalance_down(heap* heap, int start)
{
    while (true)
    {
        int child_count = heap_child_count(heap, start);

        if (child_count == 0)
            break;

        void* current = heap_value(heap, start);

        int child_i = heap_largest_child(heap, start);
        void* child = heap_value(heap, child_i);

        // Done shifting down when both child nodes are less than parent
        if (heap->compare(current, child) >= 0)
            break;

        mem_swap(child, current, heap->size);

        start = child_i;
    }
}

void heap_remove_first(heap* heap)
{
    if (heap->len < 1)
        return;

    if (heap->len < 2)
    {
        heap->len--;
        return;
    }

    // Overwrite first node (being removed) with the last node in the heap
    memcpy(heap->data, heap_value(heap, --heap->len), heap->size);

    // Rebalance the heap downward
    heap_rebalance_down(heap, 0);
}
