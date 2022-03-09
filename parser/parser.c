/*
* Parse "Object/Class" (Module) to provide parsing functionality for the Hack Assembler 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./parser.h"

typedef enum {
    A_INSTRUCTION,
    C_INSTRUCTION,
    END_OF_FILE
} line_metadata;

typedef struct {
    char* dest;
    char* comp;
    char* jump;
} c_instruction_fields;

typedef union {
    c_instruction_fields instruction_fields;
    char* address; //veamos como funciona
} instruction_body;

typedef struct {
    line_metadata current_line_metadata;
    instruction_body body;
} parsed_line;

// Opens a file and returns a ReadStream
FILE* open_file (char file_path[]) {
    FILE* input_stream;
    if (!(input_stream = fopen(file_path, "r"))) {
        fprintf(stderr, "Can't open file at filepath: %s\n", file_path);
        return NULL;
    }
    printf("File opened at filepath: %s\n", file_path);
    return input_stream;
}

// Take readstream and pointer to struct
parsed_line get_next_line(FILE* in_stream, parsed_line* instruction){
    char line[100];
    if (fscanf(in_stream, "%99[^ (//)]\n" , line )!= EOF ){

        // if(strstr(line, "@")){
        //     instruction->current_line_metadata = A_INSTRUCTION;
        //     instruction->body.address = &line + 1; // memory address from the 2d character & on
        // }
        // else {
        
        // }
        printf("Scanned Line: %s", line);
        return *instruction;
    }
    instruction->current_line_metadata = END_OF_FILE;
    return *instruction;
}

