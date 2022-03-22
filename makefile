# TODO: properly add/modify dependencies when fixing re-declaration errors from including same .h file across multiple files
constants: ./constants/hashtables-sourcefiles-paths.h ./constants/exit-status-codes.h

parser: ./parser/parser.c ./parser/parser.h constants
	gcc -c ./parser/parser.c && mv parser.o ./parser/
 
hashtable: ./hashtable/hashtable.c ./hashtable/hashtable.h constants
	gcc -c ./hashtable/hashtable.c && mv hashtable.o ./hashtable/

translator: ./translator/translator.c ./translator/translator.h
	gcc -c ./translator/translator.c && mv translator.o ./translator/

main: ./main.c ./main.h constants
	gcc -c ./main.c

# assembler: main parser translator symbol
# 	gcc ./main.o ./parser/parser.o ./translator/translator.o ./symbol/symbol.o -o assembler

assembler: main parser hashtable translator 
	gcc ./main.o ./parser/parser.o ./hashtable/hashtable.o ./translator/translator.o -o assembler

# quickly run manual tests with example file
example:
	./assembler ./assets/example.asm