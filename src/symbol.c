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
	while (*name) hash = (hash << 1) + *str++;
	return hash & HashSize;
}

Symbol *putSymbol(SymbolTable *st, char *name, 
	TypeToken t_type) {
		
	int i = hash(name);
	for (Symbol *s = st->table[i]; s; s = s->next) {
		// error
		if (strcmp(s->name, name) == 0) {
			fprintf(stderr, 
			"Error: already declared symbol %s", name);
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
	for (Symbol *s = t->table[i]; s; s = s->next) {
		if (strcmp(s->name, name) == 0) return s;
	}
	
	// check for parent scope
	if (st->parent == NULL) return NULL;
	return getSymbol(st->parent, name);
}
