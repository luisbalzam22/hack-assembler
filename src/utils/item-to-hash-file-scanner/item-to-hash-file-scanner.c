#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../regex-matcher/regex-matcher.h"
#include "./item-to-hash-file-scanner.h"

// Takes a filepath to a .json file, scans whole file, returns array item_to_hash structs (key, value)
// TODO: include preventive NULL pointer failure code for malloc and realloc
item_to_hash_table *extract_items(char file_path[]) {
    char key_val_token[500]; // TODO: find a way to improve this
    FILE* input_stream = file_opener(file_path);
    item_to_hash_table *items = malloc(sizeof(item_to_hash_table));
    items->size = 0;
    int current_scan;
    if(input_stream != NULL){
        // ! <<DEBUG>>
        int count = 0;
        while(current_scan != EOF){
            count++;
            // TODO: fix problem of not scanning to next line & on
            //current_scan = fscanf(input_stream, "%499[\"].+[\"]:[\"][0-1]+[\"]\n", key_val_token);
            current_scan = fscanf(input_stream, "%499[ {\n]+\n", key_val_token);
            current_scan = fscanf(input_stream, "%499[\"a-zA-Z0-9:-]+ *\n", key_val_token);
            current_scan = fscanf(input_stream, "%499[^\" ]+,", key_val_token);
            //printf("Current_scan: %d\n", current_scan);
            printf("String: %s\n", key_val_token);
            // items = realloc(items, sizeof(item_to_hash_table) + (sizeof(item_to_hash) * items->size));
            // items->size++;
        }
        return items;
    }
    return NULL;
}

// PRIVATE: opens a file from a specified path and returns a pointer to the opened file's stream
FILE *file_opener(char file_path[]) {
    char error_message[50];
    FILE* input_stream;

    // TODO: move the ".json" string to a constant, that'll make it more scalable
    if (!strcmp(".json", regex_matcher(file_path, ".[a-zA-Z0-9]+$")->matched_substr)){
        if (input_stream = fopen(file_path, "r")) {
            fprintf(stdout, "File successfully opened at filepath: %s\n", file_path);
            return input_stream;
        }
        strcpy(error_message, "File couldn't be openened");
    }
    else{
        strcpy(error_message, "Provided file is not a .json file");
    }
    fprintf(stderr, "Can't open file at filepath: %s\nErr:%s", file_path, error_message);
    return NULL;
}

int main(int argc, char const *argv[]){
    item_to_hash_table *tab = extract_items("./assets/instruction-sets/comp.json");
    return 0;
}
