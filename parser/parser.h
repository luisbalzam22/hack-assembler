typedef enum {
    LABEL,
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
    char* address;
    char* label;
} instruction_body;

typedef struct {
    line_metadata current_line_metadata;
    instruction_body body;
} parsed_line;

FILE* open_file(char file_path[]);

parsed_line get_next_line(FILE *in_stream, parsed_line *instruction);