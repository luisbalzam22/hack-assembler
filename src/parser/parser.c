/*
* Parse "Object/Class" (Module) to provide parsing functionality for the Hack Assembler 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./parser.h"
#include "../constants/exit-status-codes.h"

// Opens a file taken from the path arg and returns a ReadStream
FILE* open_file (char file_path[], parser *parser_instance) {
    FILE* input_stream;
    if (input_stream = fopen(file_path, "r")) {
        fprintf(stdout, "File successfully opened at filepath: %s\n", file_path);
        parser_instance->current_file_pointer = input_stream;
        return parser_instance->current_file_pointer;
    }
    fprintf(stderr, "Can't open file at filepath: %s\n", file_path);
    return NULL;
}

// Takes readstream and struct's memory address, then modifies struct and returns it
parsed_line *get_next_line(parser *parser_instance){
    char line[100];
    char line_copy[100];
    char *token_pointer;
    // this would also work:
    // int parsed = fscanf(parser_instance->current_file_pointer, "%99[^/\n ;{}`~.!#$\\%]", line);
    // if (parsed && parsed != EOF){}
    int is_parsed = fscanf(parser_instance->current_file_pointer, "%99[^\n {}`~.!#$\\%/]", line);
    if (is_parsed != EOF){

        while (!(fscanf(parser_instance->current_file_pointer, "%99[^\n {}`~.!#$\\%/]", line))) {
            // scanning past empty lines
            fscanf(parser_instance->current_file_pointer, "%99[ \n]", line);

            // scanning past comments
            fscanf(parser_instance->current_file_pointer, "%99[/\n]+", line);
            if (strstr(line, "//"))
            {
                fscanf(parser_instance->current_file_pointer, "%99[^\n]+", line); // comment's text
            }
        }
        strcpy(line_copy, line);
        parsed_line_presetter(parser_instance->line);
 
        if (strstr(line, "(")){
            token_pointer = strtok(line_copy + 1 ,")");
            parser_instance->line->meta.line_type = LABEL;

            parser_instance->line->body.label = malloc(sizeof(char) * strlen(token_pointer));
            strcpy(parser_instance->line->body.label, token_pointer);
        }
        else if (strstr(line, "@"))
        {
            token_pointer = line + 1;
            parser_instance->line->meta.line_type = A_INSTRUCTION;
            // memory address from the 2d character & on
            parser_instance->line->body.address = malloc(sizeof(char) * strlen(token_pointer));
            strcpy(parser_instance->line->body.address, token_pointer);
        }
        else {
            // TODO: DEFINITELY improve this code (most likely by abstracting into a function)
            parser_instance->line->meta.line_type = C_INSTRUCTION;
            token_pointer = strtok(line_copy ,"=");
            parser_instance->line->body.instruction_fields.dest = malloc(sizeof(char) * strlen(token_pointer));
            strcpy(parser_instance->line->body.instruction_fields.dest, token_pointer);
            token_pointer = strtok(NULL ,";");
            parser_instance->line->body.instruction_fields.comp = malloc(sizeof(char) * strlen(token_pointer));
            strcpy(parser_instance->line->body.instruction_fields.comp, token_pointer);
            token_pointer = strchr(line, 'J');
            parser_instance->line->body.instruction_fields.jump = malloc(sizeof(char) * strlen(token_pointer));
            strcpy(parser_instance->line->body.instruction_fields.jump, token_pointer);
        }
        return parser_instance->line;
    }
    parser_instance->line->meta.line_type = END_OF_FILE;
    
    return parsed_line_cleaner(parser_instance->line);
}

parser *constructor(){
    parser *new_parser = malloc(sizeof(*new_parser));
    if (new_parser != NULL){
        new_parser->open_file = &open_file;
        new_parser->get_next_line = &get_next_line;
        new_parser->current_file_pointer = NULL;
        new_parser->line = malloc(sizeof(new_parser->line)); // TODO: develop generic preventive code on "allocation error"
        new_parser->line->meta.line_number = 0;
        return new_parser;
    }
    fprintf(stdout, "Couldn't create new parser\n");
    return NULL;
}

// TODO: find a way to combine this, and "parsed_line_cleaner" function
parsed_line *parsed_line_presetter(parsed_line *line){
    line->meta.line_number++;

    // From 2nd instruction parsed & on
    if (line->meta.line_number > 1){
        switch (line->meta.line_type) {
        case LABEL:
            free(line->body.label);
            break;
        case A_INSTRUCTION:
            free(line->body.address);
            break;
        case C_INSTRUCTION:
            free(line->body.instruction_fields.dest);
            free(line->body.instruction_fields.comp);
            free(line->body.instruction_fields.jump);
            break;
        default:
            break;
        }
    }
}

parsed_line *parsed_line_cleaner(parsed_line *line){
    free(line->body.label);
    free(line->body.address);
    free(line->body.instruction_fields.dest);
    free(line->body.instruction_fields.comp);
    free(line->body.instruction_fields.jump);
}


char destructor(parser *parser_to_delete){
    // in case we decide to destroy the parser before it has read its assigned file
    parsed_line_cleaner(parser_to_delete->line);
    free(parser_to_delete);
    if (parser_to_delete == NULL){
        return SUCCESSFUL_EXIT_CODE;
    }
    return FAILED_EXIT_CODE;
}