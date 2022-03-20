#include <stdio.h>
//#include "./parser/parser.h"
#include "./translator/translator.h"


int main(int argc, char *argv[]) {
    const translator_component TRANSLATOR = { &constructor, &destructor };

    FILE* file = open_file(argv[1]);

    parsed_line line;

    do {
        get_next_line(file, &line);
    } while (line.current_line_metadata.line_type != END_OF_FILE);

    // TODO: find a way to properly organize this constant
    char* test[] = {
        "./assets/instruction-sets/comp.json",
        "./assets/instruction-sets/dest.json",
        "./assets/instruction-sets/jump.json",
        "./assets/instruction-sets/predefined-symbols.json",
    };
    // test_insert_item();
    translator * translator_instance = TRANSLATOR.constructor(test, sizeof(test)/ (sizeof (char*)));

    return 0;
}


