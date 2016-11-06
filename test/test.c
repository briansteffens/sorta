#include <stdio.h>

#include "../src/shared.h"
#include "../src/insertion.h"
#include "../src/selection.h"

typedef void (*sort_function)(void*, int, int, compare_function);

bool test_sort(sort_function sort)
{
    const int list_len = 10;
    int list[] = { 4, 2, 8, 1, 3, 4, 5, 9, 0, 3 };

    sort(list, sizeof(int), list_len, compare_int);

    return is_sorted(list, sizeof(int), list_len, compare_int);
}

const char* status(bool result)
{
    return result ? "pass" : "fail";
}

int main(int argc, char* argv[])
{
    printf("test_insertion_sort: %s\n", status(test_sort(insertion_sort)));
    printf("test_selection_sort: %s\n", status(test_sort(selection_sort)));

    return 0;
}
