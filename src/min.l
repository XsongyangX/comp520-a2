/* This file contains the specifications for automatically 
generating a scanner with flex.

Initial version: Only print out the tokens.
*/

/* Imports */
%{
	#include <stdio.h>
}%

/* Helper definitions */
BOOLEAN true|false
DIGIT [0-9]
INT 0|[1-9]{DIGIT}*
FLOAT {INT}.{DIGIT}*
SYMBOL [`~@#$%^&*][+-*/<>=_|]|['.,;:!?\{\}\[\]\(\)]|[///MISSING]
STRING [a-zA-Z_]([a-zA-Z0-9]|{SYMBOL})*

/* Additional options */
%option yylineno
