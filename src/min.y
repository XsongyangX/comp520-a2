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
	Expression *expression;
	Statement *statement;
	ControlFlow *controlFlow;
}

// type definitions based on the AST
%type <program> programStart program 
%type <expression> expression
%type <statement> statement
%type <controlFlow> if while ifelse

/* Token directives define the token types to be returned by the scanner (excluding character
 * tokens). Each token definition takes [optionally, a reference to the associated field in the
 * yylval union] and an identifier. Multiple tokens can be defined per directive by using a list
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
	| if program {
		$$ = makeProgram_controlFlow($1, $2);
	}
	| while program {
		$$ = makeProgram_controlFlow($1, $2);
	}
	| statement tSEMICOLON program {
		$$ = makeProgram_statement($1, $3);
	}
	| %empty {$$ = NULL;}
    ;

if : tIF tLPAREN expression tRPAREN tCOMMENT tLCURL program tRCURL ifelse {
		$$ = makeControlFlow_continuing(k_controlFlowKindIf, $3, $7, $9);
	}
	| tIF tLPAREN expression tRPAREN tLCURL program tRCURL ifelse {
		$$ = makeControlFlow_continuing(k_controlFlowKindIf, $3, $6, $8);
	}
	;

ifelse : tELSE tIF tLPAREN expression tRPAREN tCOMMENT tLCURL program tRCURL ifelse {
		$$ = makeControlFlow_continuing(k_controlFlowKindElseIf, $4, $8, $10);
	}
	| tELSE tIF tLPAREN expression tRPAREN tLCURL program tRCURL ifelse {
		$$ = makeControlFlow_continuing(k_controlFlowKindElseIf, $4, $7, $9);
	}
	| tELSE tCOMMENT tLCURL program tRCURL {
		$$ = makeControlFlow_else($4);
	}
	| tELSE tLCURL program tRCURL {
		$$ = makeControlFlow_else($3);
	}
	| %empty {$$ = NULL;}
	;

while : tWHILE tLPAREN expression tRPAREN tCOMMENT tLCURL program tRCURL {
		$$ = makeControlFlow_while($3, $7);
	}
	| tWHILE tLPAREN expression tRPAREN tLCURL program tRCURL {
		$$ = makeControlFlow_while($3, $6);
	}
	;

statement : tREAD tLPAREN tIDENTIFIER tRPAREN {
		$$ = makeStatement_identifier(k_statementKindRead, $3);
	}
	| tPRINT tLPAREN expression tRPAREN {
		$$ = makeStatement_print($3);
	}
	| tVAR tIDENTIFIER tCOLON type tASSIGN expression {
		$$ = makeStatement_assign(k_statementKindInitialization, $2, $6);
	}
	| tVAR tIDENTIFIER tCOLON type {
		$$ = makeStatement_identifier(k_statementKindDeclaration, $2);
	}
	| tIDENTIFIER tASSIGN expression {
		$$ = makeStatement_assign(k_statementKindAssignment, $1, $3);
	}
	;

type : tKEYINT
	| tKEYFLOAT
	| tKEYSTRING
	| tBOOLEAN
	;

expression : tTRUE {$$ = makeExpression_boolean(true);}
	| tFALSE {$$ = makeExpression_boolean(false);}
	| tINT {$$ = makeExpression_int($1);}
	| tFLOAT {$$ = makeExpression_float($1);}
	| tSTRING {$$ = makeExpression_string($1);}
	| expression tPLUS expression {
		$$ = makeExpression_binary(k_expressionKindAdd, $1, $3);
	}
	| expression tMINUS expression {
		$$ = makeExpression_binary(k_expressionKindMinus, $1, $3);
	}
	| expression tTIMES expression {
		$$ = makeExpression_binary(k_expressionKindTimes, $1, $3);
	}
	| expression tDIVIDE expression {
		$$ = makeExpression_binary(k_expressionKindDivide, $1, $3);
	}
	| tNOT expression {
		$$ = makeExpression_unary(k_expressionKindNot, $2);
	}
	| tMINUS expression	%prec UMINUS {
		$$ = makeExpression_unary(k_expressionKindUMinus, $2);
	}
	| tLPAREN expression tRPAREN {
		$$ = $2;
	}
	| expression tGEQ expression {
		$$ = makeExpression_binary(k_expressionKindGEQ, $1, $3);
	}
	| expression tLEQ expression {
		$$ = makeExpression_binary(k_expressionKindLEQ, $1, $3);
	}
	| expression tGREATER expression {
		$$ = makeExpression_binary(k_expressionKindGreater, $1, $3);
	}
	| expression tLESSER expression {
		$$ = makeExpression_binary(k_expressionKindLesser, $1, $3);
	}
	| expression tEQUAL expression {
		$$ = makeExpression_binary(k_expressionKindEqual, $1, $3);
	}
	| expression tNEQUAL expression {
		$$ = makeExpression_binary(k_expressionKindNEqual, $1, $3);
	}
	| expression tAND expression {
		$$ = makeExpression_binary(k_expressionKindAnd, $1, $3);
	}
	| expression tOR expression {
		$$ = makeExpression_binary(k_expressionKindOr, $1, $3);
	}
	| tIDENTIFIER {
		$$ = makeExpression_identifier($1);
	}
	;

