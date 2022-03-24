#ifndef TABLE_TYPE
#define TABLE_TYPE
typedef enum {
    PRE_DEFINED,
    COMP,
    DEST,
    JUMP,
    ADDRESS // ? might not be necessary; use the PRE_DEFINED table for addresses instead
} table_type;
#endif