#include <stdlib.h>
#include "tree.h"

extern int yylineno;

/* Program nodes */
Program *makeProgram_controlFlow(ControlFlow *controlFlow, 
	Program *next){
	
	Program *p = malloc(sizeof(Program));
	p->lineno = yylineno;
	p->kind = k_programKindProgram;
	
	p->content.controlFlow.controlFlow = controlFlow;
	p->content.controlFlow.next = next;
	
	return p;
}

Program *makeProgram_statement(Statement *statement,
	Program *next){
	
	Program *p = malloc(sizeof(Program));
	p->lineno = yylineno;
	p->kind = k_programKindControlFlow;
	
	p->content.statement.statement = statement;
	p->content.statement.next = next;
	
	return p;
}

/* Control flow nodes */
ControlFlow *makeControlFlow_continuing(ControlFlowKind kind, 
	Expression *condition, Program *block, ControlFlow *elsePart){
	
	ControlFlow *cf = malloc(sizeof(ControlFlow));
	cf->lineno = yylineno;
	cf->kind = kind;
	
	cf->content.continuing.condition = condition;
	cf->content.continuing.block = block;
	cf->content.continuing.elsePart = elsePart;
	
	return cf;
}

ControlFlow *makeControlFlow_while(Expression *condition, Program *block){
	
	ControlFlow *cf = malloc(sizeof(ControlFlow));
	cf->lineno = yylineno;
	cf->kind = k_controlFlowKindWhile;
	
	cf->content.whileLoop.condition = condition;
	cf->content.whileLoop.block = block;
	
	return cf;
}

ControlFlow *makeControlFlow_else(Program *block){
	
	ControlFlow *cf = malloc(sizeof(ControlFlow));
	cf->lineno = yylineno;
	cf->kind = k_controlFlowKindElse;
	
	cf->content.block = block;
	
	return cf;
}

/* Statement nodes */
Statement *makeStatement_assign(StatementKind kind, char *identifier, 
	Expression *assignment){
	
	Statement *s = malloc(sizeof(Statement));
	s->lineno = yylineno;
	s->kind = kind;
	
	s->content.assign.identifier = identifier;
	s->content.assign.assignment = assignment;
	
	return s;
}

Statement *makeStatement_identifier(StatementKind kind, char* identifier){
	
	Statement *s = malloc(sizeof(Statement));
	s->lineno = yylineno;
	s->kind = kind;
	
	s->content.identifier = identifier;
	
	return s;
}

Statement *makeStatement_print(Expression *printValue){
	
	Statement *s = malloc(sizeof(Statement));
	s->lineno = yylineno;
	s->kind = k_statementKindPrint;
	
	s->content.printValue = printValue;
	
	return s;
}

/* Expression nodes */
Expression *makeExpression_binary(ExpressionKind kind, Expression *left,
	Expression *right){
	
	Expression *e = malloc(sizeof(Expression));
	e->lineno = yylineno;
	e->kind = kind;
	
	e->content.binary.left = left;
	e->content.binary.right = right;
	
	return e;
}

Expression *makeExpression_unary(ExpressionKind kind, Expression *unary){
	
	Expression *e = malloc(sizeof(Expression));
	e->lineno = yylineno;
	e->kind = kind;
	
	e->content.unary = unary;
	
	return e;
}

Expression *makeExpression_identifier(char *identifier){
	
	Expression *e = malloc(sizeof(Expression));
	e->lineno = yylineno;
	e->kind = k_expressionKindIdentifier;
	
	e->content.identifier = identifier;
	
	return e;
}

Expression *makeExpression_boolean(bool literal){
	
	Expression *e = malloc(sizeof(Expression));
	e->lineno = yylineno;
	e->kind = k_expressionKindBooleanLiteral;
	
	e->content.boolean = literal;
	
	return e;
}

Expression *makeExpression_int(int literal){
	
	Expression *e = malloc(sizeof(Expression));
	e->lineno = yylineno;
	e->kind = k_expressionKindIntLiteral;
	
	e->content.intVal = literal;
	
	return e;
}

Expression *makeExpression_float(float literal){
	
	Expression *e = malloc(sizeof(Expression));
	e->lineno = yylineno;
	e->kind = k_expressionKindFloatLiteral;
	
	e->content.floatVal = literal;
	
	return e;
}

Expression *makeExpression_string(char *string){
	
	Expression *e = malloc(sizeof(Expression));
	e->lineno = yylineno;
	e->kind = k_expressionKindStringLiteral;
	
	e->content.string = string;
	
	return e;
}
