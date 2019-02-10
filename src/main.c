#include <stdio.h>
#include "main.h"
#include <string.h>
#include "tree.h"
#include "pretty.h"
#include "symbol.h"

void yyparse();
int yylex();
int g_tokens;
int g_symbols;
Program *root;

// main
int main(int argc, char** argv)
{
	// check if an argument is provided
	if (argc != 2)
	{
		fprintf(stderr, 
			"Must provide an argument: scan|tokens|parse|pretty|symbol|typecheck|codegen\n");
		return 1;
	}

	// get command line argument
	if ( 0 == strcmp(argv[1], "scan"))
	{
		g_tokens = 0;
		yylex();
		printf("OK\n");
		return 0;
	}
	else if ( 0 == strcmp(argv[1], "tokens"))
	{
		g_tokens = 1;
		while (yylex()) {}
		return 0;
	}
	else if ( 0 == strcmp(argv[1], "parse"))
	{
		g_tokens = 0;
		yyparse();
		printf("OK\n");
		return 0;
	}
	else if ( 0 == strcmp(argv[1], "pretty"))
	{
		g_tokens = 0;
		yyparse();
		prettyProgram(root, 0); // 0 for no tabs so far
		return 0;
	}
	else if ( 0 == strcmp(argv[1], "symbol"))
	{
		g_tokens = 0;
		g_symbols = 1;
		yyparse();
		symbolFromProgramStart(root);
		return 0;
	}
	else if ( 0 == strcmp(argv[1], "typecheck"))
	{
		g_tokens = 0;
		g_symbols = 0;
		yyparse();
		printf("OK\n");
		return 0;
	}
	else 
	{
		fprintf(stderr, 
			"Valid arguments are scan|tokens|parse|pretty|symbol|typecheck|codegen\n");
		return 1;
	}

}	
