#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "symbol.h"

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
	TypeToken t_type, int lineno) {
		
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
	
	TypeToken t_conditional;
	SymbolTable *innerScope;
	
	switch (cf->kind) {
		
		case k_controlFlowKindIf:
		case k_controlFlowKindElseIf:
			
			t_conditional = symbolFromExpression(
				cf->content.continuing.condition, parent);
			
			// condition is not boolean
			if (t_conditional != t_boolean){
				
				// get line number
				int lineno = cf->content.continuing.condition->lineno;
				
				fprintf(stderr, 
					"Error: (line %d) condition is not of type boolean", 
					lineno);
				
				exit(1);
			}
			
			innerScope = scopeSymbolTable(parent);
			
			symbolFromProgram(cf->content.continuing.block, innerScope);
			symbolFromControlFlow(cf->content.continuing.elsePart, parent);
			
			break;
		
		case k_controlFlowKindElse:
			
			innerScope = scopeSymbolTable(parent);
			symbolFromProgram(cf->content.block, innerScope);
			
			break;
			
		case k_controlFlowKindWhile:
		
			innerScope = scopeSymbolTable(parent);
			
			t_conditional = symbolFromExpression(
				cf->content.whileLoop.condition, parent);
			
			// condition is not boolean
			if (t_conditional != t_boolean){
				
				// get line number
				int lineno = cf->content.continuing.condition->lineno;
				
				fprintf(stderr, 
					"Error: (line %d) condition is not of type boolean", 
					lineno);
				
				exit(1);
			}
			
			symbolFromProgram(cf->content.whileLoop.block, innerScope);
			
			break;
	}
}

void symbolFromStatement(Statement *s, SymbolTable *parent){
	
	char *name;
	
	switch (s->kind) {
		
		case k_statementKindAssignment:
		
			name = s->content.assign.identifier;
		
			Symbol *var = getSymbol(parent, name);
			
			// symbol not found
			if (var == NULL) {
				fprintf(stderr, "Identifier not found: %s\n", name);
				exit(1);
			}
			
			// check for type correspondence
			
			
			break;
		
		case k_statementKindDeclaration:
		
			name = s->content.var.identifier;
		
			break;
	}
	
}