#ifndef TYPE_H
#define TYPE_H

#include "tree.h"

void checkAssignCompatible(Type var, Type assigned, int lineno);

char *typeToString(Type t_type);
char *opToString(ExpressionKind kind);

Type checkBinaryOp(Type left, Type right, ExpressionKind kind, int lineno);
void printBinaryError(Type left, Type right, ExpressionKind kind, int lineno);

Type checkUnaryOp(Type unary, ExpressionKind kind, int lineno);
void printUnaryError(Type unary, ExpressionKind kind, int lineno);

Type typeOfExpression(Expression *e);
#endif
