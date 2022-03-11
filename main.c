#include <stdio.h>
#include "./parser/parser.h"

int main(int argc, char *argv[])
{
    FILE* file = open_file(argv[1]);

    parsed_line line;

    do {
        get_next_line(file, &line);
    } while (line.current_line_metadata != END_OF_FILE);

    
    return 0;
}
