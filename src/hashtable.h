#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <malloc.h>
#include <string.h>

#include "sorta.h"
#include "hashing.h"

#define HASHTABLE_INITIAL_SIZE 10
#define HASHTABLE_DEFAULT_RESIZE_RATIO 0.7f

#define HASHTABLE_H(name, keytype, valuetype) \
    typedef struct name##_entry \
    { \
        keytype key; \
        valuetype value; \
        struct name##_entry* next; \
        struct name##_entry* previous; \
    } name##_entry; \
    \
    typedef struct \
    { \
        name##_entry** buckets; \
        int len; \
        int allocated; \
        hash_function hash_function; \
        compare_function key_compare_function; \
        float resize_ratio; \
    } name; \
    \
    void name##_init_size(name* h, int initial_allocated); \
    void name##_init(name* h); \
    void name##_free(name* h); \
    unsigned name##_index(name* h, keytype key); \
    name##_entry* name##_find_in_bucket(name* h, unsigned index, keytype key); \
    valuetype name##_get(name* h, keytype key); \
    void name##_set(name* h, keytype key, valuetype value); \
    void name##_resize(name* source, int new_size); \
    void name##_set(name* h, keytype key, valuetype value); \
    void name##_remove(name* h, keytype key);

#define HASHTABLE_C(name, keytype, valuetype) \
    void name##_init_size(name* h, int initial_allocated) \
    { \
        h->hash_function = hash_basic; \
        h->allocated = initial_allocated; \
        h->len = 0; \
        h->buckets = calloc(h->allocated, sizeof(name##_entry*)); \
        h->key_compare_function = NULL; \
        h->resize_ratio = HASHTABLE_DEFAULT_RESIZE_RATIO; \
    } \
    \
    void name##_init(name* h) \
    { \
        name##_init_size(h, HASHTABLE_INITIAL_SIZE); \
    } \
    \
    void name##_free(name* h) \
    { \
        /* Free bucket linked lists */ \
        for (int i = 0; i < h->allocated; i++) \
        { \
            name##_entry* entry = h->buckets[i]; \
            \
            while (entry) \
            { \
                name##_entry* temp = entry->next; \
                free(entry); \
                entry = temp; \
            } \
        } \
        \
        /* Free bucket array */ \
        free(h->buckets); \
    } \
    \
    unsigned name##_index(name* h, keytype key) \
    { \
        return h->hash_function(key) % h->allocated; \
    } \
    \
    name##_entry* name##_find_in_bucket(name* h, unsigned index, keytype key) \
    { \
        name##_entry* current = h->buckets[index]; \
        \
        while (current) \
        { \
            int differs; \
            \
            if (h->key_compare_function) \
            { \
                differs = h->key_compare_function(key, current->key); \
            } \
            else \
            { \
                differs = memcmp(&key, &current->key, sizeof(keytype)); \
            } \
            \
            if (!differs) \
            { \
                break; \
            } \
            \
            current = current->next; \
        } \
        \
        return current; \
    } \
    \
    valuetype name##_get(name* h, keytype key) \
    { \
        unsigned index = name##_index(h, key); \
        name##_entry* entry = name##_find_in_bucket(h, index, key); \
        return entry ? entry->value : NULL; \
    } \
    \
    void name##_set(name* h, keytype key, valuetype value); \
    \
    void name##_resize(name* source, int new_size) \
    { \
        /* Create a temp hashtable of the new size */ \
        name target; \
        name##_init_size(&target, new_size); \
        target.hash_function = source->hash_function; \
        target.key_compare_function = source->key_compare_function; \
        \
        /* Copy all pairs to the new hash */ \
        for (int i = 0; i < source->allocated; i++) \
        { \
            name##_entry* current = source->buckets[i]; \
            \
            while (current) \
            { \
                name##_set(&target, current->key, current->value); \
                \
                current = current->next; \
            } \
        } \
        \
        /* Only free the buckets array, not the buckets it contains */ \
        name##_free(source); \
        \
        /* Copy the new table's memory to the source */ \
        source->buckets = target.buckets; \
        source->allocated = target.allocated; \
    } \
    \
    void name##_set(name* h, keytype key, valuetype value) \
    { \
        unsigned index = name##_index(h, key); \
        name##_entry* first = h->buckets[index]; \
        name##_entry* existing = name##_find_in_bucket(h, index, key); \
        \
        /* Key exists: overwrite value */ \
        if (existing) \
        { \
            existing->value = value; \
            return; \
        } \
        \
        /* Key does not exist: grow storage if necessary */ \
        if ((float)(h->len + 1) / h->allocated >= h->resize_ratio) \
        { \
            name##_resize(h, h->allocated * 2); \
        } \
        \
        /* Add new entry */ \
        name##_entry* entry = malloc(sizeof(name##_entry)); \
        \
        memcpy(&entry->key, &key, sizeof(keytype)); \
        memcpy(&entry->value, &value, sizeof(valuetype)); \
        \
        /* Entries are already in this bucket: prepend new entry to list */ \
        if (first) \
        { \
            entry->next = first; \
            first->previous = entry; \
        } \
        else \
        { \
            entry->next = NULL; \
            entry->previous = NULL; \
        } \
        \
        h->buckets[index] = entry; \
        h->len++; \
    } \
    \
    void name##_remove(name* h, keytype key) \
    { \
        unsigned index = name##_index(h, key); \
        name##_entry* head = h->buckets[index]; \
        name##_entry* existing = name##_find_in_bucket(h, index, key); \
        \
        if (existing->previous) { \
            existing->previous->next = existing->next; \
        } \
        \
        if (existing->next) { \
            existing->next->previous = existing->previous; \
        } \
        \
        if (existing == head) { \
            h->buckets[index] = existing->next; \
        } \
        \
        free(existing); \
    }

#endif
