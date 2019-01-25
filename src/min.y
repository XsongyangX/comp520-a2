/* This file contains the specifications of the grammar. */

/* Imports */
%{
#include <stdio.h>
#include <stdlib.h>

// Scanner line number
extern int yylineno;
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
}

/* Token directives define the token types to be returned by the scanner (excluding character
 * tokens). Each token definition takes [optionally, a reference to the associated field in the
 * yylval union] and an identifier. Multiple tokens can eb defined per directive by using a list
 * of identifiers separated by spaces.
 */

// values 
%token <intval> tINTVAL
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
%token tEQUAL tNEQUAL tGEQ tLEQ tGREATER tLESSER tAND tOR
// blocks
%token tLCURL tRCURL

/* Precedence directives resolve grammar ambiguities by breaking ties between shift/reduce
 * operations. Tokens are grouped into precendence levels, with lower precedence coming first
 * and then higher precedence in later directives. Tokens specified in the same directive have
 * the same precedence. Ties at the same level are broken using either %left or %right, which
 * denote left-associative and right-associative respectively.
 */
%left tPLUS tMINUS
%left tTIMES tDIVIDE

/* Start */
%start program

/* For line numbers while parsing */
%locations

/* Error messages */
%error-verbose

/* Grammar rules */
%%

program : tCOMMENT program 
        | statement tSEMICOLON program 
        | statement tSEMICOLON
        ;


%%