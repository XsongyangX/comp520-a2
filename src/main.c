#include <stdio.h>
#include "main.h"
#include <string.h>
#include "tree.h"

void yyparse();
int yylex();
int g_tokens;

Program *root;

// main
int main(int argc, char** argv)
{
	// check if an argument is provided
	if (argc != 2)
	{
		fprintf(stderr, "Must provide an argument: scan|tokens|parse\n");
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
		printf("OK\n");
		return 0;
	}
	else 
	{
		fprintf(stderr, "Valid arguments are scan|tokens|parse|pretty\n");
		return 1;
	}

}	
