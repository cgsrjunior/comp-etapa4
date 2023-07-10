#
# UFRGS - Compiladores - Etapa 1
# Cleiber Rodrigues e Cintia Valente
# Cartões 00270139 - 00228540
#
# Makefile for single compiler call

FLAGS=-Wall -g
COMP=g++ -std=c++17

etapa2: compile_font
	${COMP} ${FLAGS} -o etapa3 lex.yy.o parser.tab.o tree.o main.o -lfl
compile_font: parser.tab.c lex.yy.c
	${COMP} ${FLAGS} -c parser.tab.c lex.yy.c tree.cc main.c	
parser.tab.c: parser.y
	bison -d parser.y
lex.yy.c: scanner.l
	flex scanner.l


clean:
	rm *.o lex.yy.c parser.tab.* *.hh.gch etapa2