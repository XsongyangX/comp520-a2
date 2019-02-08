#ifndef PRETTY_H
#define PRETTY_H

#include "tree.h"

void prettyProgram(Program *p, int tabsSoFar);
void prettyControlFlow(ControlFlow *cf, int tabsSoFar);
void prettyStatement(Statement *s, int tabsSoFar);
void prettyExpression(Expression *e, int tabsSoFar);

char *t_typeToString(TypeToken t_type);
void printTabs(int tabsSoFar);
char *getOperationSymbol(ExpressionKind kind);
#endif