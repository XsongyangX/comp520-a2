/* This file contains the specifications of the grammar. */

/* Imports */
%{
#include <stdio.h>
#include <stdlib.h>

// AST .h
#include "tree.h"

// Scanner line number
extern int yylineno;

// AST root
extern Program *root;

// yylex() from flex
int yylex();

// The yyerror function is called on any syntax error. When using %error-verbose, this function
// takes a single argument (a string) which contains a detailed explanation of the error.
// Otherwise it takes no arguments and it is up to the user to format the error using a minimal
// description provided in yytext.
// Thank you github repo.
void yyerror(const char *s) {
	fprintf(stderr, "Error: (line %d) %s\n", yylineno, s);
	exit(1);
}
%}

/* The union directive defines the yylval union used for associating (a) terminals (tokens)
 * returned by flex with additional scanning data (such as identifier/constant values); and
 * optionally (b) non-terminals (variables in productions) with AST information if any.
 */
%union {
	int intval;
    float floatval;
    char *string;
	char *identifier;
	Program *program;
}

%type <program> programStart program 

/* Token directives define the token types to be returned by the scanner (excluding character
 * tokens). Each token definition takes [optionally, a reference to the associated field in the
 * yylval union] and an identifier. Multiple tokens can eb defined per directive by using a list
 * of identifiers separated by spaces.
 */

// values 
%token <intval> tINT
%token <identifier> tIDENTIFIER
%token <floatval> tFLOAT
%token <string> tSTRING

// comment
%token tCOMMENT 
// keywords
%token tVAR tKEYFLOAT tKEYINT tKEYSTRING tBOOLEAN tIF tELSE tWHILE tREAD tPRINT tTRUE tFALSE
// assignments
%token tCOLON tASSIGN tSEMICOLON
// math
%token tPLUS tMINUS tTIMES tDIVIDE tLPAREN tRPAREN
// boolean
%token tEQUAL tNEQUAL tGEQ tLEQ tGREATER tLESSER tAND tOR tNOT
// blocks
%token tLCURL tRCURL
// unused in scanner
%token UMINUS

/* Precedence directives resolve grammar ambiguities by breaking ties between shift/reduce
 * operations. Tokens are grouped into precedence levels, with lower precedence coming first
 * and then higher precedence in later directives. Tokens specified in the same directive have
 * the same precedence. Ties at the same level are broken using either %left or %right, which
 * denote left-associative and right-associative respectively.
 */
%left tOR
%left tAND
%left tGEQ tLEQ tGREATER tLESSER tEQUAL tNEQUAL
%left tPLUS tMINUS
%left tTIMES tDIVIDE
%left UMINUS tNOT

/* Start */
%start programStart

/* For line numbers while parsing */
%locations

/* Error messages */
%error-verbose

%code requires
{
	#include "tree.h"
}

/* Grammar rules */
%%

programStart: program {root = $1;}
	;

program : tCOMMENT program {$$ = $2;}
	| if program 
	| while program
    | statement tSEMICOLON program 
	| %empty {$$ = NULL;}
    ;

if : tIF tLPAREN expression tRPAREN tCOMMENT tLCURL program tRCURL ifelse
	| tIF tLPAREN expression tRPAREN tLCURL program tRCURL ifelse
	;

ifelse : tELSE tIF tLPAREN expression tRPAREN tCOMMENT tLCURL program tRCURL ifelse
	| tELSE tIF tLPAREN expression tRPAREN tLCURL program tRCURL ifelse
	| tELSE tCOMMENT tLCURL program tRCURL
	| tELSE tLCURL program tRCURL
	|
	;

while : tWHILE tLPAREN expression tRPAREN tCOMMENT tLCURL program tRCURL
	| tWHILE tLPAREN expression tRPAREN tLCURL program tRCURL
	;

statement : tREAD tLPAREN tIDENTIFIER tRPAREN
	| tPRINT tLPAREN expression tRPAREN
	| tVAR tIDENTIFIER tCOLON type tASSIGN expression
	| tVAR tIDENTIFIER tCOLON type
	| tIDENTIFIER tASSIGN expression
	;

type : tKEYINT
    | tKEYFLOAT
	| tKEYSTRING
	| tBOOLEAN
	;

expression : tTRUE | tFALSE | tINT | tFLOAT | tSTRING
	| expression tPLUS expression
	| expression tMINUS expression
	| expression tTIMES expression
	| expression tDIVIDE expression
	| tNOT expression
	| tMINUS expression	%prec UMINUS
	| tLPAREN expression tRPAREN
	| expression tGEQ expression
	| expression tLEQ expression
	| expression tGREATER expression
	| expression tLESSER expression
	| expression tEQUAL expression
	| expression tNEQUAL expression
	| expression tAND expression
	| expression tOR expression
	| tIDENTIFIER
	;

