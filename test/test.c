#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "CUnit/Basic.h"

#define REPORT_LEN 32

#include "test_sorting.h"
#include "test_heap.h"
#include "test_stack.h"
#include "test_vector.h"

int main(int argc, char* argv[])
{
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    test_sorting();
    test_heap();
    test_stack();
    test_vector();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
