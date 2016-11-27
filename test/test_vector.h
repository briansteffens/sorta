#include "../src/vector.h"

VECTOR_H(int, int)
VECTOR_C(int, int)

vector_int vec;

void reset_vector()
{
    vector_int_init(&vec);
    vector_int_add(&vec, 3);
    vector_int_add(&vec, 7);
}

void test_vector_init()
{
    vector_int vec2;
    vector_int_init(&vec2);

    CU_ASSERT(vec2.len == 0);
    CU_ASSERT(vec2.items != NULL);
}

void test_vector_free()
{
    reset_vector();

    vector_int_free(&vec);

    CU_ASSERT(vec.items == NULL);
}

void test_vector_add()
{
    reset_vector();

    int previous = vec.len;

    vector_int_add(&vec, 9);

    CU_ASSERT(vec.len = previous + 1);
    CU_ASSERT(vec.items[vec.len - 1] == 9);
}

int test_vector()
{
    CU_pSuite suite = CU_add_suite("vector", NULL, NULL);

    CU_add_test(suite, "init", test_vector_init);
    CU_add_test(suite, "free", test_vector_free);
    CU_add_test(suite, "add", test_vector_add);

    return CU_get_error();
}
