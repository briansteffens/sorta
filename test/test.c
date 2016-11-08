#include <stdio.h>
#include <string.h>

#include "../src/sorto.h"

typedef void (*sort_function)(void*, int, int, compare_function);

bool sort(sort_function sort_func, void* list, int size, int len,
          compare_function compare, void* sorted)
{
    sort_func(list, size, len, compare_int);

    for (int i = 0; i < len; i++)
        if (compare(list + i * size, sorted + i * size) != 0)
            return false;

    return true;
}

const char* status(bool result)
{
    return result ? "pass" : "fail";
}

bool sort_odd(sort_function sort_func)
{
    int list[] = { 8, 3, 4, 1, 0, 5, 7, 6, 2 };
    int sorted[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

    return sort(sort_func, list, sizeof(int), 9, compare_int, sorted);
}

bool sort_even(sort_function sort_func)
{
    int list[] = { 4, 2, 8, 1, 3, 4, 5, 9, 0, 3 };
    int sorted[] = { 0, 1, 2, 3, 3, 4, 4, 5, 8, 9 };

    return sort(sort_func, list, sizeof(int), 10, compare_int, sorted);
}

void test(const char* name, sort_function sort_func)
{
    const int max_len = 25;
    char padded[max_len];
    strncpy(padded, name, max_len);

    const int name_len = strnlen(name, max_len);
    for (int i = name_len; i < max_len; i++)
        padded[i] = ' ';

    printf("%s (odd ): %s\n", padded, status(sort_odd(sort_func)));
    printf("%s (even): %s\n", padded, status(sort_even(sort_func)));
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

int main(int argc, char* argv[])
{
    test("insertion_sort", insertion_sort);
    test("selection_sort", selection_sort);
    test("bubble_sort", bubble_sort);
    test("shell_sort (gaps 531)", shell_531);
    test("shell_sort (gaps 321)", shell_321);
    test("merge_sort", merge_sort);

    return 0;
}
