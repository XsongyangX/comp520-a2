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

SymbolTable *initSymbolTable();
SymbolTable *scopeSymbolTable(SymbolTable *st);
int hash(char *name);
Symbol *putSymbol(SymbolTable *st, char *name, 
	TypeToken t_type);
Symbol *getSymbol(SymbolTable *st, char *name);


#endif