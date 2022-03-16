#include "../common/hashtable-manager/hashtable-manager.h"
#include "../parser/parser.h"

typedef struct {
    char *(*translate)(char*);
    // Array of pointers to hash tables (arrays of hash_item's); for this Asssembler's case: the dest, comp, jump, and symbol
    hash_table tables[];
} translator;

typedef struct {
    translator *(*constructor)(char* [], int);
    char (*destructor)(translator*);
} translator_component;

translator *constructor(char *filepaths[], int filepaths_count);
char destructor(translator* this);