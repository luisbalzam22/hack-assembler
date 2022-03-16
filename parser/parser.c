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
    int is_parsed = fscanf(in_stream, "%99[^\n {}`~.!#$\\%/]", line);
    instruction->current_line_metadata.line_number = 0; // TODO: remove this later; it'll automatically set to 0 on "Construction" when moved to "object-like" code
    if (is_parsed != EOF)
    {

        while (!(fscanf(in_stream, "%99[^\n {}`~.!#$\\%/]", line)))
        {
            // scanning past empty lines
            fscanf(in_stream, "%99[ \n]", line);

            // scanning past comments
            fscanf(in_stream, "%99[/\n]+", line);
            if (strstr(line, "//"))
            {
                fscanf(in_stream, "%99[^\n]+", line); // comment's text
            }
        }
        strcpy(line_copy, line);
        instruction->current_line_metadata.line_number++;
        if (strstr(line, "(")){
            instruction->current_line_metadata.line_type = LABEL;
            instruction->body.label = strtok(line_copy + 1 ,")");
        }
        else if (strstr(line, "@"))
        {
            instruction->current_line_metadata.line_type = A_INSTRUCTION;
            instruction->body.address = line + 1; // memory address from the 2d character & on
        }
        else {
            instruction->current_line_metadata.line_type = C_INSTRUCTION;
            instruction->body.instruction_fields.dest = strtok(line_copy ,"=");
            instruction->body.instruction_fields.comp = strtok(NULL ,";");
            instruction->body.instruction_fields.jump = strchr(line, 'J');
        }
        return *instruction;
    }
    instruction->current_line_metadata.line_type = END_OF_FILE;
    return *instruction;
}

