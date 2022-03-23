#include "../hashtable/hashtable.h"
#include "../parser/parser.h"

typedef struct {
    char *(*translate)(parsed_line);
    hash_table *(*add_tabble)(char [], item_to_hash[], unsigned int);
    // Array of pointers to hash tables (arrays of hash_items); for this Asssembler's case: the dest, comp, jump, and symbol tables
    unsigned int tables_length;
    hash_table *tables[];
} translator;

typedef struct {
    translator *(*translator_constructor)();
    char (*translator_destructor)(translator*);
} translator_component;

translator *translator_constructor();
char translator_destructor(translator* translator_to_delete);

char *translate(parsed_line *instruction);
// ? Change table_type for the ENUMS provided in the parser (instruction types)
hash_table *add_table(hash_table *table_to_add, translator *translator_instance);