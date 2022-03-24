// ? move this enum to its own "constants" file
#include "../interfaces/scanned-line-type.h"
#ifndef PARSER_H
#define PARSER_H

typedef struct {
    unsigned int line_number;
    scanned_line_type line_type;
} line_metadata;

typedef struct {
    char* dest;
    char* comp;
    char* jump;
} c_instruction_fields;

typedef union {
    c_instruction_fields instruction_fields;
    char* address;
    char* label;
} instruction_body;

typedef struct {
    line_metadata meta;
    instruction_body body;
} parsed_line;

typedef struct parser parser;
typedef struct parser{
    parsed_line *line;
    FILE *current_file_pointer;
    FILE *(*open_file)(char[], parser *);
    parsed_line *(*get_next_line)(parser *);
} parser;

typedef struct {
    parser *(*parser_constructor)();
    char (*parser_destructor)(parser *);
} parser_component;


FILE* open_file(char file_path[], parser *parser_instance);
parsed_line *get_next_line(parser *parser_instance);

parser *parser_constructor();
char parser_destructor(parser *parser_to_delete);

parsed_line *parsed_line_presetter(parsed_line *line);
parsed_line *parsed_line_cleaner(parsed_line *line);
#endif