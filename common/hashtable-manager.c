#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./hashtable-manager.h"

// takes search value (token), hash table, and the array size. Returns found item, or null
hash_item* find_item(char* token, hash_item hash_array[], unsigned int array_size){
    unsigned int hash = hash_func(token, array_size); //0

    hash_item* item = &hash_array[hash];

    while (
        item != NULL 
        && item->key != token 
        && item->next != END_OF_INDEX_REFERENCING 
        && (hash_array[item->next]).next != END_OF_INDEX_REFERENCING
        ){

        item = &(hash_array[item->next]);
    }
    
    if (item->key == token) return item;
    return NULL;
}


void test_find_item(){
    hash_item example[] = {
        {"oni", "33", END_OF_INDEX_REFERENCING},
    };
    
    hash_item* one = find_item("one", example, 1);
    if (one == NULL){
        printf("NULL\n");
        return;
    }
    printf("KEYYYY: %s\nVALUE: %s\nNEXT: %d\n-----------------\n", one->key, one->value, one->next);
}

/*
// <<<INITIAL IMPLEMENTATION>>>
// takes a hash table and a variable containing the unavailable indexes, returns found item, or null
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
// takes search value (token), hash table, and the array size. Returns found item, or null
hash_item* find_item(char* token, hash_item* hash_array[], unsigned int array_size){
    unsigned int hash = hash_func(token, array_size);

    hash_item* item = &((*hash_array)[hash]);

    while (item != NULL && item->key != token && ((*hash_array)[item->next]).next != END_OF_INDEX_REFERENCING){
        item = &((*hash_array)[item->next]);
    }
    return item;
}
*/


// a REALLY simple hash function; returns hash of the inputted string
unsigned int hash_func(char* token, unsigned int table_len){
    int token_length = strlen(token);
    unsigned int prehash;

    for (int index = 0; index < token_length; index++){
        prehash += token[index];
    }

    return (prehash * 123) % table_len;
}