#define END_OF_INDEX_REFERENCING -1

// Forward declaring type declaration
typedef struct hash_item hash_item;
typedef struct hash_item {
    char* key;
    char* value;
    unsigned int next;
} hash_item;

hash_item *find_item(char *token, hash_item *hash_array[], unsigned int array_size);
unsigned int hash_func(char *token, unsigned int table_len);
void test_find_item();
void test_insert_item();