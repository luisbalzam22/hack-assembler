#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./hashtable.h"
#include "../constants/exit-status-codes.h"


// Takes search value (token), hash table, and the array size. Returns found item, or null
hash_item* find_item(char *token, hash_table *table){
    unsigned int hash = hash_func(token, table->meta.size);

    hash_item *item = table->table[hash];

    while (
        item != NULL 
        && !strcmp(item->key, token) 
        && item->next != END_OF_INDEX_REFERENCING
        ){

        item = table->table[item->next];
    }
    
    if (item->key == token) return item;
    return NULL;
}

// Takes an item and tries to insert it into the provided hashtable, if it can't, it'll return NULL
hash_item* insert_item(item_to_hash item, hash_table *table){
    unsigned int hash = hash_func(item.key, table->meta.size);

    hash_item* array_item = table->table[hash];

    if (array_item == NULL)
    {
        table->table[hash] = hash_item_constructor(item);
        return table->table[hash];
    }
    else {
        // "Jumping" from item to item on the ones that have the same hash, until we find the "tail"
        while ( array_item->next != END_OF_INDEX_REFERENCING ) {
            array_item = table->table[array_item->next];
        }

        for (unsigned int index = 0; index < table->meta.size; index++) {
            if (table->table[index]->key == NULL){
                table->table[index] = hash_item_constructor(item);
                array_item->next = index;
                return table->table[index];
            }
        }
    }
    fprintf(stdout, "Couldn' insert item for key: %s\n", item.key);
    return NULL; // all the positions in the array are already occupied
}

// void test_find_item(){
//     hash_item oni = {"oni", "33", END_OF_INDEX_REFERENCING};
//     hash_item tengu = {"tengu", "44", END_OF_INDEX_REFERENCING};



//     hash_item* example[] = {
//         &oni,
//         &tengu
//     };

//     hash_item* one = find_item("tengu", example, 2);
//     if (one == NULL){
//         printf("NULL\n");
//         return;
//     }
//     printf("KEYYYY: %s\nVALUE: %s\nNEXT: %d\n-----------------\n", one->key, one->value, one->next);
// }

// void test_insert_item(){
//     hash_item oni = {"oni", "33", END_OF_INDEX_REFERENCING};
//     hash_item tengu = {"tengu", "44", END_OF_INDEX_REFERENCING};
//     hash_item witch = {"witch", "44", END_OF_INDEX_REFERENCING};
//     hash_item* example[2] = {
//         &oni
//     };

//     hash_item* witch_pointer = insert_item(&witch, example, 2);
//     if (witch_pointer == NULL){
//         printf("NULL\n");
//         return;
//     }
//     printf("KEYYYY: %s\nVALUE: %s\nNEXT: %d\n-----------------\n", witch_pointer->key, witch_pointer->value, witch_pointer->next);
// }

/*
// <<<INITIAL IMPLEMENTATION>>>
// Takes a hash table and a variable containing the unavailable indexes, returns found item, or null
hash_item* find_item(char* token, hash_item* hash_array[], unsigned int array_size, int inserted_items[]){
    unsigned int hash = hash_func(token, array_size);

    hash_item* item = &((*hash_array)[hash]);

    while (item != NULL && item->key != token && item->next != NULL){
        item = item->next;
    }
    return item;
}
*/

/*
//<<<SECOND IMPLEMENTATION>>>
// Takes search value (token), hash table, and the array size. Returns found item, or null
hash_item* find_item(char* token, hash_item* hash_array[], unsigned int array_size){
    unsigned int hash = hash_func(token, array_size);

    hash_item* item = &((*hash_array)[hash]);

    while (item != NULL && item->key != token && ((*hash_array)[item->next]).next != END_OF_INDEX_REFERENCING){
        item = &((*hash_array)[item->next]);
    }
    return item;
}
*/

/*
//<<<THIRD IMPLEMENTATION>>>
// Takes search value (token), hash table, and the array size. Returns found item, or null
hash_item* find_item(char* token, hash_item hash_array[], unsigned int array_size){
    unsigned int hash = hash_func(token, array_size);

    hash_item* item = &hash_array[hash];

    while (
        item != NULL 
        && item->key != token 
        && item->next != END_OF_INDEX_REFERENCING 
        ){

        item = &(hash_array[item->next]);
    }
    
    if (item->key == token) return item;
    return NULL;
}
*/


// A REALLY simple hash function; returns hash of the inputted string
unsigned int hash_func(char* token, unsigned int table_len){
    int token_length = strlen(token);
    unsigned int prehash;

    for (int index = 0; index < token_length; index++){
        prehash += token[index];
    }

    return (prehash * 100) % table_len;
}

hash_item *hash_item_constructor(item_to_hash item){
    hash_item *new_item = malloc(
        sizeof(*new_item)
        + (sizeof(char) * (strlen(item.key) + strlen(item.value)))
        );
    if (new_item != NULL){
        new_item->key = item.key;
        new_item->value = item.value;
        new_item->next = END_OF_INDEX_REFERENCING;
        return new_item;
    }
    fprintf(stdout, "Couldn't create item for key: %s\n", item.key);
    return NULL;
}

hash_table *hashtable_constructor(table_type type, item_to_hash items_for_table[], unsigned int item_count){
    hash_table* table = (hash_table*)malloc(
    sizeof(hash_table)
    + (sizeof(hash_item*) * item_count)
    );

    if (table != NULL){
        table->find_item = &find_item;
        table->insert_item = &insert_item;
        table->meta.size = item_count;
        table->meta.type = type;
        for (unsigned int index = 0; index < table->meta.size; index++){
            table->table[index] = NULL;
        }
        return table;
    }
    return NULL;
}

char hashtable_destructor(hash_table* table_to_delete){
    free(table_to_delete);
    if (table_to_delete == NULL){
        return SUCCESSFUL_EXIT_CODE;
    }
    return FAILED_EXIT_CODE;
}