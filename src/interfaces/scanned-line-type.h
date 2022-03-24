#ifndef SCANNED_LINE_TYPE
#define SCANNED_LINE_TYPE
typedef enum {
    LABEL,
    A_INSTRUCTION,
    C_INSTRUCTION,
    END_OF_FILE
} scanned_line_type;
#endif