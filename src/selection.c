#include <string.h>

#include "selection.h"

void selection_sort(void* list, int size, int items, compare_function compare)
{
    unsigned char temp[size];

    void* current = list;

    for (int i = 0; i < items; i++)
    {
        void* smallest = current;

        for (int j = i + 1; j < items; j++)
        {
            void* check = list + j * size;

            if (compare(check, smallest) < 0)
                smallest = check;
        }

        if (current != smallest)
        {
            memcpy(temp, current, size);
            memcpy(current, smallest, size);
            memcpy(smallest, temp, size);
        }

        current += size;
    }
}
