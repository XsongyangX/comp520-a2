#ifndef SYMBOL_H
#define SYMBOL_H

#include "tree.h"
#include <stdbool.h>

#define HashSize 317

typedef struct Symbol Symbol;
typedef struct SymbolTable SymbolTable;

struct Symbol {
	char *name;
	TypeToken t_type;
	union {
		char *string;
		bool boolean;
		int intVal;
		float floatVal;
	} value;
	struct Symbol *next; // for linked-list
};

struct SymbolTable {
	Symbol *table[HashSize];
	struct SymbolTable *parent;
};

// symbol table api
SymbolTable *initSymbolTable();
SymbolTable *scopeSymbolTable(SymbolTable *st);
int hash(char *name);
Symbol *putSymbol(SymbolTable *st, char *name, 
	TypeToken t_type, int lineno);
Symbol *getSymbol(SymbolTable *st, char *name);

// build symbol table
SymbolTable *symbolFromProgramStart(Program *root);
void symbolFromProgram(Program *p, SymbolTable *parent);
void symbolFromControlFlow(ControlFlow *cf, SymbolTable *parent);
void symbolFromStatement(Statement *s, SymbolTable *parent);
TypeToken symbolFromExpression(Expression *e, SymbolTable *parent);

#endif