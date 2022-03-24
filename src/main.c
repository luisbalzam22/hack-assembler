#include <stdio.h>
#include "./parser/parser.h"
#include "./translator/translator.h"
#include "./hashtable/hashtable.h"
#include "./constants/hashtables-sourcefiles-paths.h"


int main(int argc, char *argv[]) {
    const translator_component TRANSLATOR = { &translator_constructor, &translator_destructor };

    // FILE* file = open_file(argv[1]);

    // parsed_line line;

    // do {
    //     get_next_line(file, &line);
    // } while (line.current_line_metadata.line_type != END_OF_FILE);

    // test_insert_item();
    translator * translator_instance = TRANSLATOR.translator_constructor(HASHTABLES_SOURCEFILES_PATHS, sizeof(HASHTABLES_SOURCEFILES_PATHS)/ (sizeof (char*)));

    return 0;
}


