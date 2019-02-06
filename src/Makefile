all: lex.yy.c y.tab.c 
	gcc -o minic lex.yy.c y.tab.h y.tab.c main.h main.c tree.h tree.c -lfl

lex.yy.c:
	flex min.l

y.tab.c:
	bison --yacc --verbose -d min.y tree.h

clean:
	rm lex.yy.c
	rm y.tab.*
	rm y.output
	rm minic
