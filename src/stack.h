#ifndef _STACK_H
#define _STACK_H

#include <malloc.h>
#include <string.h>
#include <stdbool.h>

#define STACK_H(name, type)                                                   \
    typedef struct                                                            \
    {                                                                         \
        int allocated;                                                        \
        int len;                                                              \
        type* items;                                                          \
    } stack_##name;                                                           \
                                                                              \
    stack_##name vec_##name##_new();                                          \
    type* stack_##name##_add(stack_##type* stack);                            \

#define STACK_C(name, type)                                                   \
    void stack_##name##_init(stack_##name* stack)                             \
    {                                                                         \
        stack->allocated = 1;                                                 \
        stack->len = 0;                                                       \
        stack->items = malloc(sizeof(type) * stack->allocated);               \
    }                                                                         \
                                                                              \
    void stack_##name##_push(stack_##name* stack, type value)                 \
    {                                                                         \
        if (stack->len == stack->allocated)                                   \
        {                                                                     \
            stack->allocated *= 2;                                            \
            stack->items =                                                    \
                realloc(stack->items, sizeof(type) * stack->allocated);       \
        }                                                                     \
                                                                              \
        memcpy(&stack->items[stack->len++], &value, sizeof(type));            \
    }                                                                         \
                                                                              \
    type stack_##name##_pop(stack_##name* stack)                              \
    {                                                                         \
        type ret;                                                             \
                                                                              \
        memcpy(&ret, &stack->items[--stack->len], sizeof(type));              \
                                                                              \
        return ret;                                                           \
    }                                                                         \
                                                                              \
    void stack_##name##_free(stack_##name* stack)                             \
    {                                                                         \
        free(stack->items);                                                   \
    }                                                                         \
                                                                              \
    bool stack_##name##_is_empty(stack_##name* stack)                         \
    {                                                                         \
        return !stack->len;                                                   \
    }

#endif
