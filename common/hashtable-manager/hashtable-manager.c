#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./hashtable-manager.h"

// TODO: improve code implementation by using a struct with the array metadata, to avoid passing an "array_size" argument
// TODO: change interface, to make it "Object-like", like the "translator" component


// Takes search value (token), hash table, and the array size. Returns found item, or null
hash_item* find_item(char* token, hash_item* hash_array[], unsigned int array_size){
    unsigned int hash = hash_func(token, array_size);

    hash_item *item = hash_array[hash];

    while (
        item != NULL 
        && !strcmp(item->key, token) 
        && item->next != END_OF_INDEX_REFERENCING
        ){

        item = hash_array[item->next];
    }
    
    if (item->key == token) return item;
    return NULL;
}

// Takes an item and tries to insert it into the provided hashtable, if it can't, it'll return NULL
hash_item* insert_item(hash_item* item, hash_item* hash_array[], unsigned int array_size){
    unsigned int hash = hash_func(item->key, array_size);

    hash_item* array_item = hash_array[hash];
    if (array_item == NULL){
        hash_array[hash] = item;
        return item;
    }
    else {
        while ( array_item->next != END_OF_INDEX_REFERENCING ) {
            array_item = hash_array[item->next];
        }

        for (unsigned int index = 0; index < array_size; index++){
            if (hash_array[index] == NULL){
                hash_array[index] = item;
                array_item->next = index;
                return item;
            }
        }
    }
    return NULL; // All the positions in the array are already occupied
}

void test_find_item(){
    hash_item oni = {"oni", "33", END_OF_INDEX_REFERENCING};
    hash_item tengu = {"tengu", "44", END_OF_INDEX_REFERENCING};
    hash_item* example[] = {
        &oni,
        &tengu
    };

    hash_item* one = find_item("tengu", example, 2);
    if (one == NULL){
        printf("NULL\n");
        return;
    }
    printf("KEYYYY: %s\nVALUE: %s\nNEXT: %d\n-----------------\n", one->key, one->value, one->next);
}

void test_insert_item(){
    hash_item oni = {"oni", "33", END_OF_INDEX_REFERENCING};
    hash_item tengu = {"tengu", "44", END_OF_INDEX_REFERENCING};
    hash_item witch = {"witch", "44", END_OF_INDEX_REFERENCING};
    hash_item* example[2] = {
        &oni
    };

    hash_item* witch_pointer = insert_item(&witch, example, 2);
    if (witch_pointer == NULL){
        printf("NULL\n");
        return;
    }
    printf("KEYYYY: %s\nVALUE: %s\nNEXT: %d\n-----------------\n", witch_pointer->key, witch_pointer->value, witch_pointer->next);
}

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