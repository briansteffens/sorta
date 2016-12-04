#include <stdio.h>
#include <string.h>

#include "sorta.h"
#include "heap.h"
#include "stack.h"
#include "vector.h"

STACK_H(int, int)
STACK_C(int, int)

VECTOR_H(int, int)
VECTOR_C(int, int)

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

unsigned hash_function_basic(const void* data)
{
    const unsigned char* bytes = data;
    unsigned ret = 0;

    while (*bytes)
    {
        ret = ret * 101 + (unsigned)*bytes++;
    }

    return ret;
}

typedef unsigned (*hash_function)(const void*);

typedef struct hash_entry
{
    char* key;
    char* value;
    struct hash_entry* next;
} hash_entry;

typedef struct
{
    hash_entry** entries;
    int len;
    int allocated;
    hash_function hash_function;
} hash;

void hash_init_size(hash* h, int initial_allocated)
{
    h->hash_function = hash_function_basic;
    h->allocated = initial_allocated;
    h->len = 0;
    h->entries = calloc(h->allocated, sizeof(hash_entry*));
}

void hash_init(hash* h)
{
    hash_init_size(h, 10);
}

void hash_free(hash* h)
{
    // Free bucket linked lists
    for (int i = 0; i < h->allocated; i++)
    {
        hash_entry* entry = h->entries[i];

        while (entry)
        {
            hash_entry* temp = entry->next;
            free(entry);
            entry = temp;
        }
    }

    // Free bucket array
    free(h->entries);
}

unsigned hash_index(hash* h, char* key)
{
    return h->hash_function(key) % h->allocated;
}

hash_entry* hash_find_in_bucket(hash* h, unsigned index, char* key)
{
    hash_entry* current = h->entries[index];

    while (current && strcmp(current->key, key) != 0)
    {
        current = current->next;
    }

    return current;
}

char* hash_get(hash* h, char* key)
{
    unsigned index = hash_index(h, key);
    hash_entry* entry = hash_find_in_bucket(h, index, key);
    return entry ? entry->value : NULL;
}

void hash_set(hash* h, char* key, char* value);

void hash_resize(hash* source, int new_size)
{
    hash target;
    hash_init_size(&target, new_size);
    target.hash_function = source->hash_function;

    for (int i = 0; i < source->allocated; i++)
    {
        hash_entry* current = source->entries[i];

        while (current)
        {
            hash_set(&target, current->key, current->value);

            current = current->next;
        }
    }

    // Only free the entries array, not the bucket lists it contains
    hash_free(source);
    source->entries = target.entries;
    source->allocated = target.allocated;
}

void hash_set(hash* h, char* key, char* value)
{
    unsigned index = hash_index(h, key);
    hash_entry* first = h->entries[index];
    hash_entry* existing = hash_find_in_bucket(h, index, key);

    // Key exists: overwrite value
    if (existing)
    {
        existing->value = value;
        return;
    }

    // Key does not exist: grow storage if necessary
    if ((float)(h->len + 1) / h->allocated >= 0.7f)
    {
        printf("Grow!\n");
        hash_resize(h, h->allocated * 2);
    }

    // Add new entry
    hash_entry* entry = malloc(sizeof(hash_entry));
    entry->key = key;
    entry->value = value;

    // Entries are already in this bucket: prepend new entry to linked list
    if (first)
    {
        printf("Collision!\n");
        entry->next = first;
    }

    h->entries[index] = entry;
    h->len++;
}

int main(int argc, char* argv[])
{
    hash h;
    hash_init(&h);

    hash_set(&h, "Greetings!", "Salutations!");
    hash_set(&h, "Goodbye!", "Superbu!");
    hash_set(&h, "Bongo!", "Songo!");
    hash_set(&h, "A", "1");
    hash_set(&h, "B", "2");
    hash_set(&h, "C", "3");
    hash_set(&h, "D", "4");
    hash_set(&h, "E", "5");
    hash_set(&h, "F", "6");
    hash_set(&h, "G", "7");
    hash_set(&h, "H", "8");
    hash_set(&h, "I", "9");
    hash_set(&h, "J", "10");
    hash_set(&h, "K", "11");
    hash_set(&h, "M", "12");
    hash_set(&h, "N", "13");
    hash_set(&h, "O", "14");
    hash_set(&h, "P", "15");

    printf("%s\n", hash_get(&h, "Greetings!"));
    printf("%s\n", hash_get(&h, "Goodbye!"));
    printf("%s\n", hash_get(&h, "Bongo!"));

    printf("%d\n", hash_get(&h, "Not there") == NULL);

    hash_free(&h);

    return 0;
}
