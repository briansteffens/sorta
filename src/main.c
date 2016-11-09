#include <stdio.h>
#include <string.h>

#include "sorta.h"
#include "heap.h"

void print_list(int* list, int list_len)
{
    for (int i = 0; i < list_len; i++)
    {
        if (i > 0)
            printf(", ");

        printf("%d", list[i]);
    }

    printf("\n");
}

bool is_sorted(void* list, int size, int items, compare_function compare)
{
    void* previous = list;
    void* current = list + size;

    for (int i = 1; i < items; i++)
    {
        if (compare(previous, current) > 0)
            return false;

        previous += size;
        current += size;
    }

    return true;
}

void print_heap(heap* heap)
{
    void* current = heap->data;
    for (int i = 0; i < heap->len; i++)
    {
        printf("%d ", *(int*)current);
        current += heap->size;
    }

    printf("\n");
}

int main(int argc, char* argv[])
{
    int data[32];

    heap heap;
    heap.data = &data;
    heap.size = sizeof(int);
    heap.len = 0;
    heap.compare = compare_int;

    int items[] = { 3, 7, 1, 9, 2, 4, 3 };
    heap_add(&heap, &items[0]);
    heap_add(&heap, &items[1]);
    heap_add(&heap, &items[2]);
    heap_add(&heap, &items[3]);
    heap_add(&heap, &items[4]);
    heap_add(&heap, &items[5]);
    heap_add(&heap, &items[6]);

    print_heap(&heap);
    heap_remove_first(&heap);
    print_heap(&heap);
    heap_remove_first(&heap);
    print_heap(&heap);
    heap_remove_first(&heap);
    print_heap(&heap);
    heap_remove_first(&heap);
    print_heap(&heap);
    heap_remove_first(&heap);
    print_heap(&heap);
    heap_remove_first(&heap);
    print_heap(&heap);
    heap_remove_first(&heap);
    print_heap(&heap);

    return 0;
}
