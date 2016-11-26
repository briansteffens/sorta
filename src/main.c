#include <stdio.h>
#include <string.h>

#include "sorta.h"
#include "heap.h"
#include "stack.h"

STACK_H(int, int)
STACK_C(int, int)

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
    /*
    const int list_len = 10;
    int list[] = { 4, 2, 8, 1, 3, 4, 5, 9, 0, 3 };

    print_list(list, list_len);
    printf("%d\n", is_sorted(list, sizeof(int), list_len, compare_int));

    heap_sort(list, sizeof(int), list_len, compare_int);

    print_list(list, list_len);
    printf("%d\n", is_sorted(list, sizeof(int), list_len, compare_int));
    */
    stack_int stack;
    stack_int_init(&stack);
    stack_int_push(&stack, 123);
    printf("> %d\n", stack.items[0]);
    stack_int_push(&stack, 321);
    printf("> %d\n", stack.items[1]);
    printf("< %d\n", stack_int_pop(&stack));
    printf("< %d\n", stack_int_pop(&stack));
    printf("< %d\n", stack_int_pop(&stack));

    return 0;
}
