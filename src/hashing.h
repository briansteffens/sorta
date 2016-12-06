#ifndef _HASHING_H
#define _HASHING_H

typedef unsigned (*hash_function)(const void*);

unsigned hash_basic(const void* data);

#endif
