/*
* Parse "Object/Class" (Module) to provide parsing functionality for the Hack Assembler 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./parser.h"

// Opens a file taken from the path arg and returns a ReadStream
FILE* open_file (char file_path[]) {
    FILE* input_stream;
    if (!(input_stream = fopen(file_path, "r"))) {
        fprintf(stderr, "Can't open file at filepath: %s\n", file_path);
        return NULL;
    }
    fprintf(stdout, "File successfully opened at filepath: %s\n", file_path);
    return input_stream;
}

// Takes readstream and struct's memory address, then modifies struct and returns it
parsed_line get_next_line(FILE* in_stream, parsed_line* instruction){
    char line[100];
    char line_copy[100];
    // this would also work:
    // int parsed = fscanf(in_stream, "%99[^/\n ;{}`~.!#$\\%]", line);
    // if (parsed && parsed != EOF)
    int is_parsed;
    while ((is_parsed = fscanf(in_stream, "%99[^/\n {}`~.!#$\\%]", line))) {
        is_parsed = fscanf(in_stream, "%99[^/\n {}`~.!#$\\%]", line);
                   fprintf(stdout, "The  line: %d\n", is_parsed);
    }
    if (is_parsed != EOF) {
        strcpy(line_copy, line);
        if (strstr(line, "@"))
        {
            instruction->current_line_metadata = A_INSTRUCTION;
            instruction->body.address = line + 1; // memory address from the 2d character & on
        }
        else {
            instruction->current_line_metadata = C_INSTRUCTION;
            instruction->body.instruction_fields.dest = strtok(line_copy ,"=");
            instruction->body.instruction_fields.comp = strtok(NULL ,";");
            instruction->body.instruction_fields.jump = strchr(line, 'J');
            fprintf(stdout, "The instruction's \"dest\" field: %s\n", instruction->body.instruction_fields.dest);
            fprintf(stdout, "The instruction's \"comp\" field: %s\n", instruction->body.instruction_fields.comp);
            fprintf(stdout, "The instruction's \"jump\" field: %s\n", instruction->body.instruction_fields.jump);
        }
        return *instruction;
    }
    instruction->current_line_metadata = END_OF_FILE;
    return *instruction;
}

