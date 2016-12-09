#include "hashtable.h"

HASHTABLE_H(dict_string, char*, char*)
HASHTABLE_C(dict_string, char*, char*)

int main(int argc, char* argv[])
{
    dict_string dict;
    dict_string_init(&dict);

    dict_string_set(&dict, "somekey", "somevalue");
    printf("%s\n", dict_string_get(&dict, "somekey"));
    dict_string_remove(&dict, "somekey");
    printf("%d\n", dict_string_get(&dict, "somekey") == NULL);

    dict_string_free(&dict);

    return 0;
}
