#include <stdlib.h>
#include "tree.h"

char *strdup(const char*);
extern int yylineno;

/* Program nodes */
Program *makeProgram_controlFlow(ControlFlow *controlFlow, 
	Program *next){
	
	Program *p = malloc(sizeof(Program));
	p->lineno = yylineno;
	p->kind = k_programKindControlFlow;
	
	p->content.controlFlow.controlFlow = controlFlow;
	p->content.controlFlow.next = next;
	
	return p;
}

Program *makeProgram_statement(Statement *statement,
	Program *next){
	
	Program *p = malloc(sizeof(Program));
	p->lineno = yylineno;
	p->kind = k_programKindStatement;
	
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
Statement *makeStatement_assign(char *identifier, Expression *assignment){
	
	Statement *s = malloc(sizeof(Statement));
	s->lineno = yylineno;
	s->kind = k_statementKindAssignment;
	
	s->content.assign.identifier = strdup(identifier);
	s->content.assign.assignment = assignment;
	
	return s;
}

Statement *makeStatement_initialization(char *identifier, Type t_type,
	Expression *assignment){
		
		Statement *s = malloc(sizeof(Statement));
		s->lineno = yylineno;
		s->kind = k_statementKindInitialization;
		
		s->content.initialization.identifier = strdup(identifier);
		s->content.initialization.t_type = t_type;
		s->content.initialization.assignment = assignment;
	}

Statement *makeStatement_declaration(char* identifier, Type t_type){
	
	Statement *s = malloc(sizeof(Statement));
	s->lineno = yylineno;
	s->kind = k_statementKindDeclaration;
	
	s->content.var.identifier = strdup(identifier);
	s->content.var.t_type = t_type;
	return s;
}

Statement *makeStatement_read(char *identifier){
	
	Statement *s = malloc(sizeof(Statement));
	s->lineno = yylineno;
	s->kind = k_statementKindRead;
	
	s->content.identifier = strdup(identifier);
	
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
	
	e->content.identifier = strdup(identifier);
	
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
	
	e->content.string = strdup(string);
	
	return e;
}
