interfaces: ./src/interfaces/item-to-hash.h

constants: ./src/constants/hashtables-sourcefiles-paths.h ./src/constants/exit-status-codes.h

parser: ./src/parser/parser.c ./src/parser/parser.h constants
	gcc -c ./src/parser/parser.c && mv parser.o ./src/parser/
 
hashtable: ./src/hashtable/hashtable.c ./src/hashtable/hashtable.h constants interfaces
	gcc -c ./src/hashtable/hashtable.c && mv hashtable.o ./src/hashtable/

#item-to-hash-file-scanner: ./src/utils/item-to-hash-file-scanner/item-to-hash-file-scanner.c
#	gcc -c ./src/utils/item-to-hash-file-scanner/item-to-hash-file-scanner.c && mv item-to-hash-file-scanner.o ./src/utils/item-to-hash-file-scanner/

item-to-hash-file-scanner: ./src/utils/item-to-hash-file-scanner/item-to-hash-file-scanner.c
	gcc ./src/utils/item-to-hash-file-scanner/item-to-hash-file-scanner.c ./src/utils/regex-matcher/regex-matcher.c -o item-to-hash-file-scanner

translator: ./src/translator/translator.c ./src/translator/translator.h constants
	gcc -c ./src/translator/translator.c && mv translator.o ./src/translator/

main: ./src/main.c ./src/main.h constants item-to-hash-file-scanner
	gcc -c ./src/main.c && mv ./main.o ./src/

assembler: main parser hashtable translator 
	gcc ./src/main.o ./src/parser/parser.o ./src/hashtable/hashtable.o ./src/translator/translator.o ./src/utils/item-to-hash-file-scanner/item-to-hash-file-scanner.o -o assembler

# quickly run manual tests with example file
example:
	./src/assembler ./src/assets/example.asm