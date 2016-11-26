#include "../src/stack.h"

STACK_H(int, int)
STACK_C(int, int)

void test_stack_typical_usage()
{
    stack_int target;
    stack_int_init(&target);

    CU_ASSERT(stack_int_is_empty(&target));

    stack_int_push(&target, 123);

    CU_ASSERT(!stack_int_is_empty(&target));

    stack_int_push(&target, 321);

    CU_ASSERT(stack_int_pop(&target) == 321);
    CU_ASSERT(stack_int_pop(&target) == 123);

    CU_ASSERT(stack_int_is_empty(&target));

    stack_int_free(&target);
}

int test_stack()
{
    CU_pSuite suite = CU_add_suite("stack", NULL, NULL);

    CU_add_test(suite, "typical_usage", test_stack_typical_usage);

    return CU_get_error();
}
