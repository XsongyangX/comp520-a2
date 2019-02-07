all: lex.yy.c y.tab.c main.o tree.o
	gcc -o minic lex.yy.c y.tab.h y.tab.c main.o tree.o -lfl

main.o:
	gcc -c main.c main.h
	
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
