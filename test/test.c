#include <stdio.h>

#include "../src/sorto.h"

typedef void (*sort_function)(void*, int, int, compare_function);

bool test_sort(sort_function sort)
{
    const int list_len = 10;
    int list[] = { 4, 2, 8, 1, 3, 4, 5, 9, 0, 3 };

    sort(list, sizeof(int), list_len, compare_int);

    return is_sorted(list, sizeof(int), list_len, compare_int);
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

const char* status(bool result)
{
    return result ? "pass" : "fail";
}

int main(int argc, char* argv[])
{
    printf("test_insertion_sort: %s\n", status(test_sort(insertion_sort)));
    printf("test_selection_sort: %s\n", status(test_sort(selection_sort)));
    printf("test_bubble_sort: %s\n", status(test_sort(bubble_sort)));
    printf("test_shell_sort_531: %s\n", status(test_sort(shell_531)));
    printf("test_shell_sort_321: %s\n", status(test_sort(shell_321)));

    return 0;
}
