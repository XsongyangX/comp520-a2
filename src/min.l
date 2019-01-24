/* This file contains the specifications for automatically 
generating a scanner with flex.

Initial version: Only print out the tokens.
*/

/* Imports */
%{
	#include <stdio.h>
%}

/* Helper definitions */
DIGIT [0-9]
LETTER [a-zA-z]
INT 0|[1-9]{DIGIT}*
FLOAT {INT}\.{DIGIT}*
SYMBOL [`~@#$%^&\*][+\-/<>=_\|]|['\.,;:!?\{\}\[\]\(\)]|[\a\b\f\n\r\t\v\" ]
IDENTIFIER ({LETTER}|_)({LETTER}|{DIGIT}|_)*
KEYWORDS var|float|int|string|boolean|if|else|while|read|print|true|false

/* Additional options */
%option yylineno

/* Token recognition */
/* Reminder:
	- yyleng: Length of the scanned token
	- yytext: Matched text
	- yylineno: Variable for the line number
*/
%%
[\r\n]+		
[ \t]+ 		printf("Whitespace, length %lu\n", yyleng);

"//".*\n	printf("tCOMMENT\n");
{KEYWORDS} 	printf("tKEYWORD\n");
{IDENTIFIER} 	printf("tINDENTIFIER\n");
":"		printf("tCOLON\n");
"=" 		printf("tASSIGN\n");
{INT} 		printf("tINT\n");
{FLOAT} 	printf("tFLOAT\n");
\"({SYMBOL}|{LETTER}|{DIGIT})*\" 	printf("tSTRING\n");
";" 		printf("tSEMICOLON\n");

"+" 		printf("tPLUS\n");
"-"		printf("tMINUS\n");
"/"		printf("tDIVIDE\n");
"*"		printf("tTIMES\n");
"("		printf("tLPAREN\n");
")"		printf("tRPAREN\n");

"=="		printf("tEQUAL\n");
"!="		printf("tNEQUAL\n");
">="		printf("tGEQ\n");
"<="		printf("tLEQ\n");
">"		printf("tGREATER\n");
"<"		printf("tLESSER\n");
"&&"		printf("tAND\n");
"\|\|"		printf("tOR\n");

"\{" 		printf("tLCURL\n");
"\}"		printf("tRCURL\n");

. 		{ fprintf(stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }
%%

/* Main */
int main()
{
	yylex();
	return 0;
}
