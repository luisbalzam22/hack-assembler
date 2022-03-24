#include "../../interfaces/item-to-hash.h"

#ifndef ITEM_TO_HASH_FILE_SCANNER
#define ITEM_TO_HASH_FILE_SCANNER

typedef struct {
    unsigned int size;
    item_to_hash items[];
} item_to_hash_table;

item_to_hash_table *extract_items(char filepath[]);
FILE *file_opener(char file_path[]);
#endif