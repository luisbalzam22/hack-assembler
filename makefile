parser: ./parser/parser.c ./parser/parser.h
	gcc -c ./parser/parser.c && mv parser.o ./parser/

hashtable: ./hashtable/hashtable.c ./hashtable/hashtable.h
	gcc -c ./hashtable/hashtable.c && mv hashtable.o ./hashtable/

translator: ./translator/translator.c ./translator/translator.h
	gcc -c ./translator/translator.c && mv translator.o ./translator/

# symbol: ./symbol/symbol.c ./symbol/symbol.h
# 	gcc -c ./symbol/symbol.c && mv symbol.o ./symbol/

main: ./main.c ./main.h
	gcc -c ./main.c

# assembler: main parser translator symbol
# 	gcc ./main.o ./parser/parser.o ./translator/translator.o ./symbol/symbol.o -o assembler

assembler: main parser hashtable translator
	gcc ./main.o ./parser/parser.o ./hashtable/hashtable.o ./translator/translator.o -o assembler

# quickly run manual tests with example file
example:
	./assembler ./assets/example.asm