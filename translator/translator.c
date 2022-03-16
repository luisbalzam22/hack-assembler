/*
* Parse "Object/Class" (Module) to provide parsing functionality for the Hack Assembler 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./translator.h"

// Takes an array of filepaths to .json files, where each file will represent an instruction set, and therefore, a "hash table" to be constructed for the translator 
translator *constructor(char *filepaths[], int filepaths_count) {
    
    translator *translator_instance = malloc(sizeof(*translator_instance) + (sizeof(char) * filepaths_count));

    for (int index = 0; index < filepaths_count; index++){
    }
        if (translator_instance != 0){
            printf("SizeOf Translator in Bytes: %ld\nSize of array (tables): %d\n", sizeof translator_instance, filepaths_count);
        }
    return translator_instance;
    // takes the "table type" from the filename; pattern -> [^/.]$
}

char destructor(translator* this) {
    translator *translator_instance = malloc(sizeof(*translator_instance));

    if (translator_instance != 0){

    }
    // takes the "table type" from the filename; pattern -> [^/.]$
}

char* translate(parsed_line * instruction){
    char * translation;

    if (instruction->current_line_metadata.line_type == A_INSTRUCTION){

    }
    if (instruction->current_line_metadata.line_type == C_INSTRUCTION){

    }
    if (instruction->current_line_metadata.line_type == LABEL){

    }
}