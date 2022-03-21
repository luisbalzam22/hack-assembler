// ? move this enum to its own "constants" file
typedef enum {
    LABEL,
    A_INSTRUCTION,
    C_INSTRUCTION,
    END_OF_FILE
} scanned_line_type;

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
    parsed_line (*get_next_line)(FILE *, parsed_line *);
    FILE *(*open_file)(char[]);
} parser;

typedef struct {
    parser *(*constructor)();
    char (*destructor)(parser *);
} parser_component;

FILE* open_file(char file_path[]);

parsed_line get_next_line(FILE *current_file_pointer, parsed_line *instruction);

