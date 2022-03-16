parser: ./parser/parser.c ./parser/parser.h
	gcc -c ./parser/parser.c && mv parser.o ./parser/

hashtable-manager: ./common/hashtable-manager/hashtable-manager.c ./common/hashtable-manager/hashtable-manager.h
	gcc -c ./common/hashtable-manager/hashtable-manager.c && mv hashtable-manager.o ./common/hashtable-manager/

translator: ./translator/translator.c ./translator/translator.h
	gcc -c ./translator/translator.c && mv translator.o ./translator/

# symbol: ./symbol/symbol.c ./symbol/symbol.h
# 	gcc -c ./symbol/symbol.c && mv symbol.o ./symbol/

main: ./main.c ./main.h
	gcc -c ./main.c

# assembler: main parser translator symbol
# 	gcc ./main.o ./parser/parser.o ./translator/translator.o ./symbol/symbol.o -o assembler

assembler: main parser hashtable-manager translator
	gcc ./main.o ./parser/parser.o ./common/hashtable-manager/hashtable-manager.o ./translator/translator.o -o assembler

# quickly run manual tests with example file
example:
	./assembler ./assets/example.asm