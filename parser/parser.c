/*
* Parse "Object/Class" (Module) to provide parsing functionality for the Hack Assembler 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./parser.h"

// Opens a file and returns a ReadStream
FILE* open_file (char file_path[]) {
    FILE* input_stream;
    if (!(input_stream = fopen(file_path, "r"))) {
        fprintf(stderr, "Can't open file at filepath: %s\n", file_path);
        return NULL;
    }
    fprintf(stdout, "File successfully opened at filepath: %s\n", file_path);
    return input_stream;
}

// Takes readstream and pointer to struct, then returns modified struct
parsed_line get_next_line(FILE* in_stream, parsed_line* instruction){
    char line[100];
    // this would also work:
    // int parsed = fscanf(in_stream, "%99[^/\n ;{}`~.!#$\\%]", line);
    // if (parsed && parsed != EOF)
    int parsed;
    if ((parsed = fscanf(in_stream, "%99[^/\n ;{}`~.!#$\\%]", line)) != EOF && parsed) {
        if(strstr(line, "@")) {
            instruction->current_line_metadata = A_INSTRUCTION;
            instruction->body.address = line + 1; // memory address from the 2d character & on
        }
        else {
            instruction->current_line_metadata = C_INSTRUCTION;
        }
        return *instruction;
    }
    instruction->current_line_metadata = END_OF_FILE;
    return *instruction;
}

