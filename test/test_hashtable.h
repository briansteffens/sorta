#include "../src/hashtable.h"

HASHTABLE_H(dict_string, char*, char*)
HASHTABLE_C(dict_string, char*, char*)

void test_hashtable_init()
{
    dict_string dict;
    dict_string_init(&dict);

    CU_ASSERT(dict.len == 0);
    CU_ASSERT(dict.buckets != NULL);
    CU_ASSERT(dict.hash_function != NULL);

    dict_string_free(&dict);
}

void test_hashtable_set_and_retrieve()
{
    dict_string dict;
    dict_string_init(&dict);

    CU_ASSERT(!dict_string_get(&dict, "somekey"));
    CU_ASSERT(dict.len == 0);

    char* value = "somevalue";

    dict_string_set(&dict, "somekey", value);

    CU_ASSERT(dict_string_get(&dict, "somekey") == value);
    CU_ASSERT(dict.len == 1);

    dict_string_free(&dict);
}

void test_hashtable_overwrite()
{
    dict_string dict;
    dict_string_init(&dict);

    char* value1 = "value1";
    char* value2 = "value2";

    dict_string_set(&dict, "somekey", value1);
    CU_ASSERT(dict_string_get(&dict, "somekey") == value1);
    CU_ASSERT(dict.len == 1);

    dict_string_set(&dict, "somekey", value2);
    CU_ASSERT(dict_string_get(&dict, "somekey") == value2);
    CU_ASSERT(dict.len == 1);

    dict_string_free(&dict);
}

void test_hashtable_auto_resize()
{
    dict_string dict;
    dict_string_init(&dict);

    CU_ASSERT(dict.allocated == 10);

    char* value = "1";

    dict_string_set(&dict, "a", value);
    dict_string_set(&dict, "b", "2");
    dict_string_set(&dict, "c", "3");
    dict_string_set(&dict, "d", "4");
    dict_string_set(&dict, "e", "5");
    dict_string_set(&dict, "f", "6");
    dict_string_set(&dict, "g", "7");
    dict_string_set(&dict, "h", "8");

    CU_ASSERT(dict.allocated == 20);
    CU_ASSERT(dict_string_get(&dict, "a") == value);

    dict_string_free(&dict);
}

int compare_strings(void* left, void* right)
{
    return strcmp(left, right);
}

void test_hashtable_custom_compare()
{
    dict_string dict;
    dict_string_init(&dict);
    dict.key_compare_function = compare_strings;

    char* key0 = "somekey";
    char* key1 = "somekey";
    char* value = "somevalue";

    dict_string_set(&dict, key0, value);
    CU_ASSERT(dict_string_get(&dict, key1) == value);

    dict_string_free(&dict);
}

int test_hashtable()
{
    CU_pSuite suite = CU_add_suite("hashtable", NULL, NULL);

    CU_add_test(suite, "init", test_hashtable_init);
    CU_add_test(suite, "set_and_retrieve", test_hashtable_set_and_retrieve);
    CU_add_test(suite, "overwrite", test_hashtable_overwrite);
    CU_add_test(suite, "auto_resize", test_hashtable_auto_resize);
    CU_add_test(suite, "custom_compare", test_hashtable_custom_compare);

    return CU_get_error();
}
