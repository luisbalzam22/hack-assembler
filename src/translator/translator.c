/*
* Parse "Object/Class" (Module) to provide parsing functionality for the Hack Assembler 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "../constants/exit-status-codes.h"
#include "./translator.h"

hash_table *add_table(hash_table *table_to_add, translator *translator_instance){
    translator_instance->tables_length++;
    translator_instance = realloc(translator_instance,sizeof(*translator_instance) + (sizeof(hash_table*) * translator_instance->tables_length));

    if (translator_instance != NULL){
        translator_instance->tables[translator_instance->tables_length - 1] = table_to_add;
        return translator_instance->tables[translator_instance->tables_length - 1];
    }
    return NULL;
}

// Takes an array of filepaths to .json files, where each file will represent an instruction set, and therefore, a "hash table" to be constructed for the translator 
translator *translator_constructor() {
    
    translator *translator_instance = malloc(sizeof(*translator_instance));
    if (translator_instance != NULL) {
        translator_instance->tables_length = 0;
        return translator_instance;
    }
    fprintf(stdout, "Couldn't create new translator\n");
    return NULL;
}

char translator_destructor(translator *translator_to_delete) {
    free(translator_to_delete->tables);
    free(translator_to_delete);
    if (translator_to_delete->tables == NULL && translator_to_delete == NULL)
    {
        return SUCCESSFUL_EXIT_CODE;
    }
    return FAILED_EXIT_CODE;
}

// This helper function avoids having to create a hashtable just to find the correct pointer to 
// the hashtable where the translation'll come from
hash_table *find_table(parsed_line *instruction, translator *translator_instance){
    for (int index = 0; index < translator_instance->tables_length; index++){
        if (translator_instance->tables[index]->meta.type == instruction->meta.line_type) {
            return translator_instance->tables[index];
        }
    }
    return NULL;
}

char* translate(parsed_line *instruction, translator *translator_instance){
    // It shouldn't be more than 100 characters long
    char *translation = malloc(sizeof(char) * 100);
    hash_table *respective_instruction_table = find_table(instruction ,translator_instance);

    if (instruction->meta.line_type == A_INSTRUCTION){
        return respective_instruction_table->find_item(instruction->body.address, respective_instruction_table)->value;
    }
    if (instruction->meta.line_type == C_INSTRUCTION){
        strcat(translation, respective_instruction_table->find_item(instruction->body.instruction_fields.dest, respective_instruction_table)->value);
        strcat(translation, respective_instruction_table->find_item(instruction->body.instruction_fields.comp, respective_instruction_table)->value);
        strcat(translation, respective_instruction_table->find_item(instruction->body.instruction_fields.jump, respective_instruction_table)->value);
        return translation;
    }
    if (instruction->meta.line_type == LABEL){
        return respective_instruction_table->find_item(instruction->body.label, respective_instruction_table)->value;
    }
}

//
char release_memory_from_translation(char* translation){
    free(translation);
    if (translation == NULL){
        return SUCCESSFUL_EXIT_CODE;
    }
    return FAILED_EXIT_CODE;
}