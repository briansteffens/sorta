#include "../src/heap.h"

#define DATA_LEN 8

int data[DATA_LEN];
heap target;

void reset()
{
    target.data = data;
    target.len = 0;
    target.size = sizeof(int);
    target.compare = compare_int;

    for (int i = 0; i < DATA_LEN; i++)
    {
        data[i] = 0;
    }
}

void test_add_node_1()
{
    reset();

    int item = 7;
    heap_add(&target, &item);

    CU_ASSERT(target.len == 1);
    CU_ASSERT(data[0] == 7);
}

void test_add_node_2_smaller()
{
    reset();
    data[0] = 7;
    target.len = 1;

    int item = 3;
    heap_add(&target, &item);

    CU_ASSERT(target.len == 2);
    CU_ASSERT(data[0] == 7);
    CU_ASSERT(data[1] == 3);
}

void test_add_node_2_larger()
{
    reset();
    data[0] = 7;
    target.len = 1;

    int item = 9;
    heap_add(&target, &item);

    CU_ASSERT(target.len == 2);
    CU_ASSERT(data[0] == 9);
    CU_ASSERT(data[1] == 7);
}

void test_add_node_3_smaller()
{
    reset();
    data[0] = 7;
    data[1] = 3;
    target.len = 2;

    int item = 2;
    heap_add(&target, &item);

    CU_ASSERT(target.len == 3);
    CU_ASSERT(data[0] == 7);
    CU_ASSERT(data[1] == 3);
    CU_ASSERT(data[2] == 2);
}

void test_add_node_3_larger()
{
    reset();
    data[0] = 7;
    data[1] = 3;
    target.len = 2;

    int item = 9;
    heap_add(&target, &item);

    CU_ASSERT(target.len == 3);
    CU_ASSERT(data[0] == 9);
    CU_ASSERT(data[1] == 3);
    CU_ASSERT(data[2] == 7);
}

void test_add_node_4_middle()
{
    reset();
    data[0] = 7;
    data[1] = 5;
    data[2] = 3;
    target.len = 3;

    int item = 6;
    heap_add(&target, &item);

    CU_ASSERT(target.len == 4);
    CU_ASSERT(data[0] == 7);
    CU_ASSERT(data[1] == 6);
    CU_ASSERT(data[2] == 3);
    CU_ASSERT(data[3] == 5);
}

void test_remove_nodes()
{
    reset();
    data[0] = 7;
    data[1] = 5;
    data[2] = 3;
    target.len = 3;

    heap_remove_first(&target);
    CU_ASSERT(target.len == 2);
    CU_ASSERT(data[0] == 5);
    CU_ASSERT(data[1] == 3);

    heap_remove_first(&target);
    CU_ASSERT(target.len == 1);
    CU_ASSERT(data[0] == 3);

    heap_remove_first(&target);
    CU_ASSERT(target.len == 0);
}

void test_heap_parent()
{
    CU_ASSERT(heap_parent(&target, 1) == 0);
    CU_ASSERT(heap_parent(&target, 2) == 0);
    CU_ASSERT(heap_parent(&target, 3) == 1);
    CU_ASSERT(heap_parent(&target, 4) == 1);
    CU_ASSERT(heap_parent(&target, 5) == 2);
    CU_ASSERT(heap_parent(&target, 6) == 2);
}

void test_heap_child_left()
{
    CU_ASSERT(heap_child_left(&target, 0) == 1);
    CU_ASSERT(heap_child_left(&target, 1) == 3);
    CU_ASSERT(heap_child_left(&target, 2) == 5);
    CU_ASSERT(heap_child_left(&target, 3) == 7);
}

void test_heap_child_right()
{
    CU_ASSERT(heap_child_right(&target, 0) == 2);
    CU_ASSERT(heap_child_right(&target, 1) == 4);
    CU_ASSERT(heap_child_right(&target, 2) == 6);
    CU_ASSERT(heap_child_right(&target, 3) == 8);
}

void test_heap_value()
{
    reset();
    data[0] = 7;
    data[1] = 5;
    target.len = 2;

    CU_ASSERT(heap_value(&target, 0) == &data[0]);
    CU_ASSERT(heap_value(&target, 1) == &data[1]);
}

void test_heap_child_count()
{
    target.len = 2;
    CU_ASSERT(heap_child_count(&target, 1) == 0);

    target.len = 3;
    CU_ASSERT(heap_child_count(&target, 1) == 0);

    target.len = 4;
    CU_ASSERT(heap_child_count(&target, 1) == 1);

    target.len = 5;
    CU_ASSERT(heap_child_count(&target, 1) == 2);
}

void test_heap_largest_child_1()
{
    reset();
    data[1] = 7;
    target.len = 2;

    CU_ASSERT(heap_largest_child(&target, 0) == 1);
}

void test_heap_largest_child_2()
{
    reset();
    data[1] = 7;
    data[2] = 9;
    target.len = 3;

    CU_ASSERT(heap_largest_child(&target, 0) == 2);
}

int test_heap()
{
    CU_pSuite suite = CU_add_suite("heap", NULL, NULL);

    CU_add_test(suite, "add_node_1", test_add_node_1);
    CU_add_test(suite, "add_node_2_smaller", test_add_node_2_smaller);
    CU_add_test(suite, "add_node_2_larger", test_add_node_2_larger);
    CU_add_test(suite, "add_node_3_smaller", test_add_node_3_smaller);
    CU_add_test(suite, "add_node_3_larger", test_add_node_3_larger);
    CU_add_test(suite, "add_node_4_middle", test_add_node_4_middle);
    CU_add_test(suite, "remove_nodes", test_remove_nodes);
    CU_add_test(suite, "heap_parent", test_heap_parent);
    CU_add_test(suite, "heap_child_left", test_heap_child_left);
    CU_add_test(suite, "heap_child_right", test_heap_child_right);
    CU_add_test(suite, "heap_value", test_heap_value);
    CU_add_test(suite, "heap_child_count", test_heap_child_count);
    CU_add_test(suite, "heap_largest_child_1", test_heap_largest_child_1);
    CU_add_test(suite, "heap_largest_child_2", test_heap_largest_child_2);

    return CU_get_error();
}
