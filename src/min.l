/* This file contains the specifications for automatically 
generating a scanner with flex.

Initial version: Only print out the tokens.
*/

/* Imports */
%{
	#include "y.tab.h" // from bison
	#include <string.h>
	#include <stdlib.h>
	#include "main.h"
%}

/* Helper definitions */
DIGIT [0-9]
LETTER [a-zA-z]
INT 0|([1-9]{DIGIT}*)
FLOAT {INT}\.{DIGIT}+
SYMBOL [`~@#\$%\^&\*\+\-/\<>\=_\|'\.,;:\!\?\{\}\[\]\(\) ]
IDENTIFIER ({LETTER}|_)({LETTER}|{DIGIT}|_)*

/* Additional options */
%option yylineno

/* Token recognition */
/* Reminder:
	- yyleng: Length of the scanned token
	- yytext: Matched text
	- yylineno: Variable for the line number
	- yylval: Storing extra data from scanning
*/
%%
[\r\n]+		
[ \t]+ 		//printf("Whitespace, length %lu\n", yyleng);

"//".*\n	{if (g_tokens) printf("tCOMMENT\n"); return(tCOMMENT);}

var 	{if (g_tokens) printf("tVAR\n"); return(tVAR);}
float 	{if (g_tokens) printf("tKEYFLOAT\n"); return(tKEYFLOAT);}
int 	{if (g_tokens) printf("tKEYINT\n"); return(tKEYINT);}
string 	{if (g_tokens) printf("tKEYSTRING\n"); return(tKEYSTRING);}
boolean {if (g_tokens) printf("tBOOLEAN\n"); return(tBOOLEAN);}
if 		{if (g_tokens) printf("tIF\n"); return(tIF);}
else 	{if (g_tokens) printf("tELSE\n"); return(tELSE);}
while 	{if (g_tokens) printf("tWHILE\n"); return(tWHILE);}
read 	{if (g_tokens) printf("tREAD\n"); return(tREAD);}
print 	{if (g_tokens) printf("tPRINT\n"); return(tPRINT);}
true 	{if (g_tokens) printf("tTRUE\n"); return(tTRUE);}
false 	{if (g_tokens) printf("tFALSE\n"); return(tFALSE);}

{IDENTIFIER} 	{if (g_tokens) printf("tIDENTIFIER(%s)\n", yytext); return(tIDENTIFIER);}
":"		{if (g_tokens) printf("tCOLON\n"); return(tCOLON);}
"=" 		{if (g_tokens) printf("tASSIGN\n"); return(tASSIGN);}
{INT} 		{if (g_tokens) printf("tINT(%s)\n", yytext); return(tINT);}
{FLOAT} 	{if (g_tokens) printf("tFLOAT(%s)\n", yytext); return(tFLOAT);}
\"({LETTER}|{DIGIT}|{SYMBOL})*\"	 	{if (g_tokens) printf("tSTRING(%s)\n", yytext); return(tSTRING);}
";" 		{if (g_tokens) printf("tSEMICOLON\n"); return(tSEMICOLON);}

"+" 		{if (g_tokens) printf("tPLUS\n"); return(tPLUS);}
"-"		{if (g_tokens) printf("tMINUS\n"); return(tMINUS);}
"/"		{if (g_tokens) printf("tDIVIDE\n"); return(tDIVIDE);}
"*"		{if (g_tokens) printf("tTIMES\n"); return(tTIMES);}
"("		{if (g_tokens) printf("tLPAREN\n"); return(tLPAREN);}
")"		{if (g_tokens) printf("tRPAREN\n"); return(tRPAREN);}

"!" 		{if (g_tokens) printf("tNOT\n"); return(tNOT);}
"=="		{if (g_tokens) printf("tEQUAL\n"); return(tEQUAL);}
"!="		{if (g_tokens) printf("tNEQUAL\n"); return(tNEQUAL);}
">="		{if (g_tokens) printf("tGEQ\n"); return(tGEQ);}
"<="		{if (g_tokens) printf("tLEQ\n"); return(tLEQ);}
">"		{if (g_tokens) printf("tGREATER\n"); return(tGREATER);}
"<"		{if (g_tokens) printf("tLESSER\n"); return(tLESSER);}
"&&"		{if (g_tokens) printf("tAND\n"); return(tAND);}
"\|\|"		{if (g_tokens) printf("tOR\n"); return(tOR);}

"\{" 		{if (g_tokens) printf("tLCURL\n"); return(tLCURL);}
"\}"		{if (g_tokens) printf("tRCURL\n"); return(tRCURL);}

. 		{ fprintf(stderr, "Error: (line %d) unexpected character '%s', length of scanned token '%lu'\n", yylineno, yytext, yyleng); exit(1); }
%%

int g_tokens;
