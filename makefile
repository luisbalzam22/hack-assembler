constants: ./src/constants/hashtables-sourcefiles-paths.h ./src/constants/exit-status-codes.h

parser: ./src/parser/parser.c ./src/parser/parser.h constants
	gcc -c ./src/parser/parser.c && mv parser.o ./src/parser/
 
hashtable: ./src/hashtable/hashtable.c ./src/hashtable/hashtable.h constants
	gcc -c ./src/hashtable/hashtable.c && mv hashtable.o ./src/hashtable/

translator: ./src/translator/translator.c ./src/translator/translator.h constants
	gcc -c ./src/translator/translator.c && mv translator.o ./src/translator/

main: ./src/main.c ./src/main.h constants
	gcc -c ./src/main.c && mv ./main.o ./src/

assembler: main parser hashtable translator 
	gcc ./src/main.o ./src/parser/parser.o ./src/hashtable/hashtable.o ./src/translator/translator.o -o assembler

# quickly run manual tests with example file
example:
	./src/assembler ./src/assets/example.asm