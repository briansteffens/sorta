#include <stdio.h>
#include <string.h>

#include "insertion.h"

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

int main(int argc, char* argv[])
{
    const int list_len = 10;
    int list[] = { 4, 2, 8, 1, 3, 4, 5, 9, 0, 3 };

    print_list(list, list_len);
    printf("%d\n", is_sorted(list, sizeof(int), list_len, compare_int));

    insertion_sort(list, sizeof(int), list_len, compare_int);

    print_list(list, list_len);
    printf("%d\n", is_sorted(list, sizeof(int), list_len, compare_int));

    return 0;
}
