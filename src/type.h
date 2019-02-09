#ifndef TYPE_H
#define TYPE_H

#include "tree.h"
#include "symbol.h"

void checkAssignCompatible(Type var, Type assigned, int lineno);
void assign(Symbol *var, Symbol *assigned, int lineno);
char *typeToString(Type t_type);
#endif
