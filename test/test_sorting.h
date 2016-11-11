#include "../src/sorta.h"

typedef void (*sort_function)(void*, int, int, compare_function);

void sort(sort_function sort_func, void* list, int size, int len,
          compare_function compare, void* sorted)
{
    sort_func(list, size, len, compare_int);

    for (int i = 0; i < len; i++)
        CU_ASSERT(compare(list + i * size, sorted + i * size) == 0);
}

void sort_odd(sort_function sort_func)
{
    int list[] = { 8, 3, 4, 1, 0, 5, 7, 6, 2 };
    int sorted[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

    sort(sort_func, list, sizeof(int), 9, compare_int, sorted);
}

void sort_even(sort_function sort_func)
{
    int list[] = { 4, 2, 8, 1, 3, 4, 5, 9, 0, 3 };
    int sorted[] = { 0, 1, 2, 3, 3, 4, 4, 5, 8, 9 };

    sort(sort_func, list, sizeof(int), 10, compare_int, sorted);
}

void shell_531(void* list, int size, int len, compare_function compare)
{
    int gaps[] = { 5, 3, 1 };
    shell_sort(list, size, len, compare, gaps, 3);
}

void shell_321(void* list, int size, int len, compare_function compare)
{
    int gaps[] = { 3, 2, 1 };
    shell_sort(list, size, len, compare, gaps, 3);
}

void insertion_sort_odd()
{
    sort_odd(insertion_sort);
}

void insertion_sort_even()
{
    sort_even(insertion_sort);
}

void selection_sort_odd()
{
    sort_odd(selection_sort);
}

void selection_sort_even()
{
    sort_even(selection_sort);
}

void bubble_sort_odd()
{
    sort_odd(bubble_sort);
}

void bubble_sort_even()
{
    sort_even(bubble_sort);
}

void shell_531_sort_odd()
{
    sort_odd(shell_531);
}

void shell_531_sort_even()
{
    sort_even(shell_531);
}

void shell_321_sort_odd()
{
    sort_odd(shell_321);
}

void shell_321_sort_even()
{
    sort_even(shell_321);
}

void merge_sort_odd()
{
    sort_odd(merge_sort);
}

void merge_sort_even()
{
    sort_even(merge_sort);
}

void heap_sort_odd()
{
    sort_odd(heap_sort);
}

void heap_sort_even()
{
    sort_even(heap_sort);
}

int test_sorting()
{
    CU_pSuite suite = CU_add_suite("sorting", NULL, NULL);

    CU_add_test(suite, "insertion_sort odd", insertion_sort_odd);
    CU_add_test(suite, "insertion_sort even", insertion_sort_even);

    CU_add_test(suite, "selection_sort odd", selection_sort_odd);
    CU_add_test(suite, "selection_sort even", selection_sort_even);

    CU_add_test(suite, "bubble_sort odd", bubble_sort_odd);
    CU_add_test(suite, "bubble_sort even", bubble_sort_even);

    CU_add_test(suite, "shell_531_sort odd", shell_531_sort_odd);
    CU_add_test(suite, "shell_531_sort even", shell_531_sort_even);

    CU_add_test(suite, "shell_321_sort odd", shell_321_sort_odd);
    CU_add_test(suite, "shell_321_sort even", shell_321_sort_even);

    CU_add_test(suite, "merge_sort odd", merge_sort_odd);
    CU_add_test(suite, "merge_sort even", merge_sort_even);

    CU_add_test(suite, "heap_sort odd", heap_sort_odd);
    CU_add_test(suite, "heap_sort even", heap_sort_even);

    return CU_get_error();
}
