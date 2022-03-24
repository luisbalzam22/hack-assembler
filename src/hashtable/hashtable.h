#include "../parser/parser.h"
#ifndef HASHTABLE_H
#define HASHTABLE_H
#define END_OF_INDEX_REFERENCING -1
typedef struct {
    // type == title == name
    unsigned int size;
    scanned_line_or_table_type type; 
} hashtable_metadata;

typedef struct {
    char *key;
    char *value;
    unsigned int next;
} hash_item;

typedef struct {
    char *key;
    char *value;
} item_to_hash;

// forward-referencing the struct definition
typedef struct hash_table hash_table;
typedef struct hash_table {
    hash_item *(*find_item)(char*, hash_table*);
    hash_item *(*insert_item)(item_to_hash, hash_table*);
    hashtable_metadata meta;
    hash_item *table[];
} hash_table;

typedef struct {
    hash_table *(*hashtable_constructor)(scanned_line_or_table_type, item_to_hash [], unsigned int);
    char (*hashtable_destructor)(hash_table*);
} hashtable_component;


hash_item *find_item(char *token, hash_table *table);
hash_item *insert_item(item_to_hash item, hash_table *table);
void test_find_item();
void test_insert_item();

// ! the table_items[] will come from a loop running on another function, which'll count the total elements and size them correctly
hash_table *hashtable_constructor(scanned_line_or_table_type table_type, item_to_hash items_for_table[], unsigned int item_count);
char hashtable_destructor(hash_table *table_to_delete);
hash_item *hash_item_constructor(item_to_hash item);
unsigned int hash_func(char *token, unsigned int table_len);
#endif