#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "symbol.h"
#include "type.h"
#include "main.h"

SymbolTable *initSymbolTable() {
	
	SymbolTable *st = malloc(sizeof(SymbolTable));
	
	for (int i = 0; i < HashSize; i++){
		st->table[i] = NULL;
	}
	
	st->parent = NULL;
	return st;
}

SymbolTable *scopeSymbolTable(SymbolTable *st) {
	
	SymbolTable *scoped = initSymbolTable();
	scoped->parent = st;
	return scoped;
}

int hash(char *name) {
	unsigned int hash = 0;
	while (*name) hash = (hash << 1) + *name++;
	return hash & HashSize;
}

// Putting a symbol does not initialize its value
Symbol *putSymbol(SymbolTable *st, char *name, 
	Type t_type, int lineno) {
		
	int i = hash(name);
	for (Symbol *s = st->table[i]; s; s = s->next) {
		// error
		if (strcmp(s->name, name) == 0) {
			fprintf(stderr, 
				"Error: (line %d) already declared symbol %s\n",
				lineno,
				name);
			exit(1);
		}
	}
		
	Symbol *s = malloc(sizeof(Symbol));
	s->name = name;
	s->t_type = t_type;
	s->next = st->table[i];
	st->table[i] = s;
	return s;
}
	
Symbol *getSymbol(SymbolTable *st, char *name){
	
	int i = hash(name);
	
	// check current scope
	for (Symbol *s = st->table[i]; s; s = s->next) {
		if (strcmp(s->name, name) == 0) return s;
	}
	
	// check for parent scope
	if (st->parent == NULL) return NULL;
	return getSymbol(st->parent, name);
}

SymbolTable *symbolFromProgramStart(Program *root){
	
	SymbolTable *globalScope = initSymbolTable();
	
	if (g_symbols) {
		printf("---SYMBOL TABLE BEGIN---\n");
	}
	
	symbolFromProgram(root, globalScope);
	
	return globalScope;
}

void symbolFromProgram(Program *p, SymbolTable *parent){
	
	if (p == NULL) return;
	
	switch (p->kind) {
		
		case k_programKindControlFlow:
			
			symbolFromControlFlow(p->content.controlFlow.controlFlow, parent);
			symbolFromProgram(p->content.controlFlow.next, parent);
			
			break;
		
		case k_programKindStatement:
		
			symbolFromStatement(p->content.statement.statement, parent);
			symbolFromProgram(p->content.statement.next, parent);
		
			break;
	}
}

void symbolFromControlFlow(ControlFlow *cf, SymbolTable *parent){
	
	if (cf == NULL) return;
	
	Type conditional;
	SymbolTable *innerScope;
	
	switch (cf->kind) {
		
		case k_controlFlowKindIf:
		case k_controlFlowKindElseIf:
			
			conditional = symbolFromExpression(
				cf->content.continuing.condition, parent);
			
			// condition is not boolean
			if (conditional != t_boolean){
				
				// get line number
				int lineno = cf->content.continuing.condition->lineno;
				
				fprintf(stderr, 
					"Error: (line %d) condition is not of type boolean\n", 
					lineno);
				
				exit(1);
			}
			
			innerScope = scopeSymbolTable(parent);
			
			if (g_symbols) {
				printf("**Inner table START{\n");
			}
			
			symbolFromProgram(cf->content.continuing.block, innerScope);
			
			if (g_symbols) {
				printf("**Inner table END}\n");
			}
			symbolFromControlFlow(cf->content.continuing.elsePart, parent);
			
			break;
		
		case k_controlFlowKindElse:
			
			innerScope = scopeSymbolTable(parent);
			
			if (g_symbols) {
				printf("**Inner table START{\n");
			}
			
			symbolFromProgram(cf->content.block, innerScope);
			
			if (g_symbols) {
				printf("**Inner table END}\n");
			}
			
			break;
			
		case k_controlFlowKindWhile:
			
			innerScope = scopeSymbolTable(parent);
			
			conditional = symbolFromExpression(
				cf->content.whileLoop.condition, parent);
			
			// condition is not boolean
			if (conditional != t_boolean){
				
				// get line number
				int lineno = cf->content.continuing.condition->lineno;
				
				fprintf(stderr, 
					"Error: (line %d) condition is not of type boolean\n", 
					lineno);
				
				exit(1);
			}
			
			if (g_symbols) {
				printf("**Inner table START{\n");
			}
			
			symbolFromProgram(cf->content.whileLoop.block, innerScope);
			
			if (g_symbols) {
				printf("**Inner table END}\n");
			}
			break;
	}
}

void symbolFromStatement(Statement *s, SymbolTable *parent){
	
	char *name;
	Symbol *var;
	Type assigned;
	
	switch (s->kind) {
		
		case k_statementKindAssignment:
		
			name = s->content.assign.identifier;
			
			var = getSymbol(parent, name);
			
			// symbol not found
			if (var == NULL) {
				int lineno = s->lineno;
				fprintf(stderr,
					"Error: (line %d) identifier not found: %s\n",
					lineno,
					name);
				exit(1);
			}
			
			assigned = symbolFromExpression(s->content.assign.assignment,
				parent);
			
			// check for type compatibility inside the call
			checkAssignCompatible(var->t_type, assigned, s->lineno);
			
			break;
		
		case k_statementKindDeclaration:
		
			name = s->content.var.identifier;
			
			// declaration conflict handled in call
			putSymbol(parent, name, 
				s->content.var.t_type, 
				s->lineno);
			
			if (g_symbols) {
				printf("var %s: type %s\n",
					name,
					s->content.var.t_type
					);
			}
			
			break;
			
		case k_statementKindInitialization:
		
			name = s->content.var.identifier;
			
			// declaration conflict checked in call
			var = putSymbol(parent, name,
				s->content.initialization.t_type,
				s->lineno);
			
			assigned = symbolFromExpression(
				s->content.initialization.assignment,
				parent);
				
			// check for type compatibility
			checkAssignCompatible(var->t_type, assigned, s->lineno);
			
			if (g_symbols) {
				printf("var %s: type %s\n",
					name,
					s->content.initialization.t_type
					);
			}
			
			break;
			
		case k_statementKindRead:
			
			name = s->content.identifier;
			
			var = getSymbol(parent, name);
			
			// variable not found
			if (var == NULL) {
				int lineno = s->lineno;
				fprintf(stderr,
					"Error: (line %d) identifier not found: %s\n",
					lineno,
					name);
				exit(1);
			}
			
			break;
		
		case k_statementKindPrint:
			// all types allowed inside print
			/*
			assigned = symbolFromExpression(s->content.printValue,
				parent);
				
			// check if it is a string
			if (assigned != t_string) {
				int lineno = s->lineno;
				fprintf(stderr,
					"Error: (line %d) print value must be a string\n",
					lineno);
				exit(1);
			}
			*/
			break;
	}
	
}

Type symbolFromExpression(Expression *e, SymbolTable *parent){
	
	Type leftExpression;
	Type rightExpression;
	
	Symbol *var;
	
	switch (e->kind) {
		// binary operations
		case k_expressionKindAdd:
		case k_expressionKindMinus:
		case k_expressionKindTimes:
		case k_expressionKindDivide:
		case k_expressionKindGEQ:
		case k_expressionKindLEQ:
		case k_expressionKindGreater:
		case k_expressionKindLesser:
		case k_expressionKindEqual:
		case k_expressionKindNEqual:
		case k_expressionKindAnd:
		case k_expressionKindOr:
			
			leftExpression = symbolFromExpression(
				e->content.binary.left, parent);
			rightExpression = symbolFromExpression(
				e->content.binary.right, parent);
			
			// check type compatibility
			return checkBinaryOp(leftExpression, 
				rightExpression, e->kind, e->lineno);
			
			break;
			
		// unary operations
		case k_expressionKindNot:
		case k_expressionKindUMinus:
		
			leftExpression = symbolFromExpression(
				e->content.unary, parent);
			
			return checkUnaryOp(leftExpression, e->kind, e->lineno);
			
			break;
			
		// identifier
		case k_expressionKindIdentifier:
		
			var = getSymbol(parent, e->content.identifier);
			
			return var->t_type;
			
			break;
			
		// literals
		
		case k_expressionKindBooleanLiteral:
			
			return t_boolean;
			
			break;
			
		case k_expressionKindIntLiteral:
		
			return t_int;
			
			break;
			
		case k_expressionKindFloatLiteral:
		
			return t_float;
			
			break;
			
		case k_expressionKindStringLiteral:
		
			return t_string;
			
			break;
	}
}