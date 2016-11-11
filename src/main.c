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
    const int list_len = 10;
    int list[] = { 4, 2, 8, 1, 3, 4, 5, 9, 0, 3 };

    print_list(list, list_len);
    printf("%d\n", is_sorted(list, sizeof(int), list_len, compare_int));

    heap_sort(list, sizeof(int), list_len, compare_int);

    print_list(list, list_len);
    printf("%d\n", is_sorted(list, sizeof(int), list_len, compare_int));

    return 0;
}
