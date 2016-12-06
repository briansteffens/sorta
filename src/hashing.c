#include "hashing.h"

unsigned hash_basic(const void* data)
{
    const unsigned char* bytes = data;
    unsigned ret = 0;

    while (*bytes)
    {
        ret = ret * 101 + (unsigned)*bytes++;
    }

    return ret;
}
