all: lex.yy.c
	gcc -o minic lex.yy.c -lfl

lex.yy.c:
	flex min.l

clean:
	rm minic
	rm lex.yy.c
