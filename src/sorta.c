#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "sorta.h"
#include "heap.h"

int compare_int(void* left, void* right)
{
    return *(int*)left - *(int*)right;
}

void mem_swap(void* dest, void* src, int bytes)
{
    unsigned char temp[bytes];

    memcpy(temp, dest, bytes);
    memcpy(dest, src, bytes);
    memcpy(src, temp, bytes);
}

void insertion_sort(void* list, int size, int items, compare_function compare)
{
    unsigned char temp[size];

    for (int i = 0; i < items; i++)
    {
        void* current = list + i * size;
        void* swap = list;

        for (int j = i - 1; j >= 0; j--)
        {
            void* previous = list + j * size;

            if (compare(current, previous) >= 0)
            {
                swap = previous + size;
                break;
            }
        }

        if (swap == current)
            continue;

        memcpy(temp, current, size);
        memmove(swap + size, swap, current - swap);
        memcpy(swap, temp, size);
    }
}

void selection_sort(void* list, int size, int items, compare_function compare)
{
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
            mem_swap(current, smallest, size);

        current += size;
    }
}

void bubble_sort(void* list, int size, int items, compare_function compare)
{
    for (int unsorted_len = items; unsorted_len > 1; unsorted_len--)
    {
        void* left = list;

        for (int i = 0; i < unsorted_len - 1; i++)
        {
            void* right = left + size;

            if (compare(left, right) > 0)
                mem_swap(left, right, size);

            left += size;
        }
    }
}

void shell_sort(void* list, int size, int len, compare_function compare,
                int gaps[], int gaps_len)
{
    unsigned char temp[size];

    // For each gap
    for (int gap_i = 0; gap_i < gaps_len; gap_i++)
    {
        int gap = gaps[gap_i];

        // Bytes between two nearby elements in a sublist with this gap size
        int gap_size = gap * size;

        // Insertion sort each sublist in the gap
        for (int sublist_start = 0; sublist_start < gap; sublist_start++)
        {
            int sublist_len = (len - sublist_start - 1) / gap + 1;

            for (int current_i = 1; current_i < sublist_len; current_i++)
            {
                void* current = list + size *
                                (current_i * gap + sublist_start);
                void* swap = list + size * sublist_start;

                // For each already-sorted item in the sublist, find the first
                // element that current is greater than.
                for (int check_i = current_i - 1; check_i >= 0; check_i--)
                {
                    void* check = list + size *
                                  (check_i * gap + sublist_start);

                    if (compare(current, check) > 0)
                    {
                        // Swap current to the position immediately following
                        // check.
                        swap = check + gap_size;
                        break;
                    }
                }

                if (current == swap)
                    continue;

                memcpy(temp, current, size);

                // Starting on the element before current, shift each element
                // forward one position until swap is reached.
                void* shift = current - gap_size;
                while (shift >= swap)
                {
                    memcpy(shift + gap_size, shift, size);
                    shift -= gap_size;
                }

                memcpy(swap, temp, size);
            }
        }
    }
}

void merge_sort_inner(void* source, void* target, int size, int len, int begin,
                      int end, compare_function compare)
{
    // Calculate mid-point to divide sublist into subsublists
    int middle = (begin + end) / 2;

    // Don't bother sorting sublists if the sets have only one item in them
    if (end - middle > 1 || middle - begin > 1)
    {
        merge_sort_inner(target, source, size, len, begin, middle, compare);
        merge_sort_inner(target, source, size, len, middle, end, compare);
    }

    int left_i = begin;
    int right_i = middle;

    for (int target_i = begin; target_i < end; target_i++)
    {
        void* left = NULL;
        void* right = NULL;

        if (left_i < middle)
            left = source + left_i * size;

        if (right_i < end)
            right = source + right_i * size;

        int take_i = 0;

        if (!left)
        {
            // If no items remain in left list, automatically take from right
            take_i = right_i++;
        }
        else if (!right)
        {
            // If no items remain in right list, automatically take from left
            take_i = left_i++;
        }
        else
        {
            // Items remain in both lists. Of the left-most items in each list,
            // take the smallest of the two.
            if (compare(left, right) < 0)
                take_i = left_i++;
            else
                take_i = right_i++;
        }

        memcpy(target + target_i * size, source + take_i * size, size);
    }
}

void merge_sort(void* list, int size, int len, compare_function compare)
{
    int bytes = len * size;
    unsigned char temp[bytes];
    memcpy(temp, list, bytes);

    merge_sort_inner(temp, list, size, len, 0, len, compare);
}

void heap_sort(void* list, int size, int len, compare_function compare)
{
    // Heapify the input list in-place by rebalancing a sub-heap starting
    // with only the last element and working backward until it includes the
    // entire array.
    heap heap;
    heap.data = list;
    heap.len = len;
    heap.size = size;
    heap.compare = compare;

    for (int i = len - 1; i >= 0; i--)
    {
        heap_rebalance_down(&heap, i);
    }

    // Now divide the underlying void* into two sections: the first is the
    // heap and the second is the output array. Repeatedly remove the root
    // (highest) node from the shrinking heap and move it into the growing
    // output array.
    void* output_start = list + (len - 1) * size;
    unsigned char temp[size];
    while (heap.len > 0)
    {
        // Copy root item into temp storage
        memcpy(temp, list, size);

        // Remove root item and rebalance
        heap_remove_first(&heap);

        // Copy old root into the output sub-array
        memcpy(output_start, temp, size);
        output_start -= size;
    }
}

void pivot_swap(void* list, int size, compare_function compare,
        int pivots[], const int left, const int right)
{
    void* left_addr = list + pivots[left] * size;
    void* right_addr = list + pivots[right] * size;

    if (compare(left_addr, right_addr) > 0) {
        mem_swap(left_addr, right_addr, size);
    }
}

void quick_sort(void* list, int size, int len, compare_function compare)
{
    if (len <= 1)
    {
        return;
    }

    // Select pivot as the median of the first, middle, and last element
    int pivots[] = {0, len / 2, len - 1};

    // Sort pivot samples
    pivot_swap(list, size, compare, pivots, 0, 2);
    pivot_swap(list, size, compare, pivots, 0, 1);
    pivot_swap(list, size, compare, pivots, 1, 2);

    // Swap the pivot with the last element
    void* pivot = list + (len - 1) * size;
    mem_swap(list + pivots[1] * size, pivot, size);

    void* swap_target = list;
    void* current = list;

    // Linear pass across list to identify the pivot's sorted position and
    // move everything smaller than the pivot to the left of that final
    // sorted position
    while (current < pivot)
    {
        // If current is less than the pivot
        if (compare(current, pivot) < 0)
        {
            if (current != swap_target)
            {
                mem_swap(current, swap_target, size);
            }

            swap_target += size;
        }

        current += size;
    }

    // Swap the pivot into its sorted position
    if (pivot != swap_target)
    {
        mem_swap(pivot, swap_target, size);
    }

    // Pointer math to figure out the index of the pivot's sorted position
    size_t pivot_index = swap_target - list;
    if (pivot_index > 0)
    {
        pivot_index /= size;
    }

    // Sort the left sub-list
    quick_sort(list, size, pivot_index, compare);

    // Sort the right sub-list
    quick_sort(list + (pivot_index + 1) * size, size, len - pivot_index - 1,
            compare);
}
