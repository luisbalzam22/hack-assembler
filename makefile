parser: ./parser/parser.c ./parser/parser.h
	gcc -c ./parser/parser.c && mv parser.o ./parser/

# translator: ./translator/translator.c ./translator/translator.h
# 	gcc -c ./translator/translator.c && mv translator.o ./translator/

# symbol: ./symbol/symbol.c ./symbol/symbol.h
# 	gcc -c ./symbol/symbol.c && mv symbol.o ./symbol/

main: ./main.c ./main.h
	gcc -c ./main.c

# assembler: main parser translator symbol
# 	gcc ./main.o ./parser/parser.o ./translator/translator.o ./symbol/symbol.o -o assembler

assembler: main parser
	gcc ./main.o ./parser/parser.o -o assembler