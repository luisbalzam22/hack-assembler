#include <stdio.h>
#include "./parser/parser.h"

int main(int argc, char *argv[])
{
    FILE* file = open_file(argv[1]);

    parsed_line line;

    get_next_line(file, &line);
    return 0;
}
