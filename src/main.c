#include <stdio.h>

/* Global */
int g_tokens = 1;

void yyparse();
int yylex();

int main(void)
{
	if (g_tokens) while (yylex()) {};
	yyparse();
	return 0;
}	
