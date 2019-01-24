all: lex.yy.c
	gcc -o min lex.yy.c -lfl

lex.yy.c:
	flex min.l

clean:
	rm min
	rm lex.yy.c
