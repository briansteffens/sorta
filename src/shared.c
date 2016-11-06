#include "shared.h"

int compare_int(void* left, void* right)
{
    return *(int*)left - *(int*)right;
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
