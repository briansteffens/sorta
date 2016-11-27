#include <stdio.h>
#include <string.h>

#include "sorta.h"
#include "heap.h"
#include "stack.h"
#include "vector.h"

STACK_H(int, int)
STACK_C(int, int)

VECTOR_H(int, int)
VECTOR_C(int, int)

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
    vector_int vec;
    vector_int_init(&vec);

    vector_int_add(&vec, 123);
    vector_int_add(&vec, 321);

    printf("%d\n", vec.len);
    printf("%d\n", vec.items[0]);
    printf("%d\n", vec.items[1]);

    vector_int_free(&vec);

    return 0;
}
