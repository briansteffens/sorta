#include <stdio.h>
#include "sorta.h"


int main(int argc, char* argv[])
{
    int list[] = { 8, 3, 4, 1, 0, 5, 7, 6, 2 };
    //int sorted[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

    for (int i = 0; i < 9; i++)
    {
        printf("%d ", list[i]);
    }
    printf("\n");

    quick_sort(list, sizeof(int), 9, compare_int);

    for (int i = 0; i < 9; i++)
    {
        printf("%d ", list[i]);
    }
    printf("\n");

    return 0;
}
