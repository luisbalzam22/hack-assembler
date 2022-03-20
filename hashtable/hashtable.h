#define END_OF_INDEX_REFERENCING -1

typedef struct {
    char *key;
    char *value;
    unsigned int next;
} hash_item;

typedef struct {
    hash_item *table;
    char *table_type;
    unsigned int table_size;
    hash_item *(*find_item)(char*);
    hash_item *(*insert_item)();
} hash_table;

typedef struct {
    hash_table *(*constructor)(hash_item* []);
    char (*destructor)(hash_item*);
} hashtable_manager;


hash_item *find_item(char *token, hash_item *hash_array[], unsigned int array_size);
unsigned int hash_func(char *token, unsigned int table_len);
void test_find_item();
void test_insert_item();