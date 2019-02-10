all: lex.yy.o y.tab.o main.o tree.o pretty.o symbol.o type.o
	gcc -o minic lex.yy.o y.tab.o main.o tree.o pretty.o type.o -lfl

type.o:
	gcc -c type.c type.h

symbol.o:
	gcc -c symbol.c symbol.h type.h main.h

pretty.o:
	gcc -c pretty.c pretty.h
	
y.tab.o: y.tab.c 
	gcc -c y.tab.c y.tab.h
	
lex.yy.o: lex.yy.c y.tab.c
	gcc -c lex.yy.c y.tab.h
	
main.o:
	gcc -c main.c main.h pretty.h symbol.h
	
tree.o:
	gcc -c tree.c tree.h
	
lex.yy.c:
	flex min.l

y.tab.c:
	bison --yacc --verbose -d min.y

clean:
	rm lex.yy.c
	rm y.tab.*
	rm y.output
	rm *.o
	rm *.gch
	rm minic
