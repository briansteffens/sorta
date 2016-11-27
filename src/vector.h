#ifndef _VECTOR_H
#define _VECTOR_H

#include <malloc.h>
#include <string.h>

#define VECTOR_H(name, type)                                                  \
    typedef struct                                                            \
    {                                                                         \
        int allocated;                                                        \
        int len;                                                              \
        type* items;                                                          \
    } vector_##name;                                                          \
                                                                              \
    void vector_##name##_init(vector_##name* vec);                            \
    void vector_##name##_add(vector_##name* vec, type val);                   \
    void vector_##name##_free(vector_##name* vec);

#define VECTOR_C(name, type)                                                  \
    void vector_##name##_init(vector_##name* vec)                             \
    {                                                                         \
        vec->allocated = 1;                                                   \
        vec->len = 0;                                                         \
        vec->items = malloc(sizeof(type) * vec->allocated);                   \
    }                                                                         \
                                                                              \
    void vector_##name##_add(vector_##name* vec, type val)                    \
    {                                                                         \
        if (vec->len == vec->allocated)                                       \
        {                                                                     \
            vec->allocated *= 2;                                              \
            vec->items = realloc(vec->items, sizeof(type) * vec->allocated);  \
        }                                                                     \
        memcpy(&vec->items[vec->len++], &val, sizeof(type));                  \
    }                                                                         \
                                                                              \
    void vector_##name##_free(vector_##name* vec)                             \
    {                                                                         \
        free(vec->items);                                                     \
        vec->items = NULL;                                                    \
    }

#endif
