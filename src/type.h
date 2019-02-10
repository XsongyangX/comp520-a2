#ifndef TYPE_H
#define TYPE_H

#include "tree.h"
#include "symbol.h"

void checkAssignCompatible(Type var, Type assigned, int lineno);
void assign(Symbol *var, Symbol *assigned, int lineno);

char *typeToString(Type t_type);
char *opToString(ExpressionKind kind);

Type checkBinaryOp(Type left, Type right, ExpressionKind kind, int lineno);
void printBinaryError(Type left, Type right, ExpressionKind kind, int lineno);
#endif
