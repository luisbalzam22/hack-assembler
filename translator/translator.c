/*
* Parse "Object/Class" (Module) to provide parsing functionality for the Hack Assembler 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "./translator.h"

// Takes an array of filepaths to .json files, where each file will represent an instruction set, and therefore, a "hash table" to be constructed for the translator 
translator *constructor(char *filepaths[], int filepaths_count) {
    
    translator *translator_instance = malloc(sizeof(*translator_instance) + (sizeof(char) * filepaths_count));
    char table_name[30]; // TODO: see if it's necessary to leave it like that, or avoid specifying array size
    
    // translator_instance construye su instancia LUEGO de que ya hayan hashtables con longitud determinada disponibles para 
    // TODO: turn this into a "parser_component" function/pseudo-method
    for (int path_index = 0; path_index < filepaths_count; path_index++){
        // use regex code to get name
        table_name = strstr()

        // <PLACEHOLDER> ----use parser to open file
        // <PLACEHOLDER> ----use table manager (with malloc) to create table
        // <PLACEHOLDER> ----add table to array of tables in translator struct
        fprintf(stdout, "Path: %s", (*filepaths) + 50);
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