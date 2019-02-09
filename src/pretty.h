#ifndef PRETTY_H
#define PRETTY_H

#include "tree.h"

void prettyProgram(Program *p, int tabsSoFar);
void prettyControlFlow(ControlFlow *cf, int tabsSoFar);
void prettyStatement(Statement *s);
void prettyExpression(Expression *e);

char *t_typeToString(Type t_type);
void printTabs(int tabsSoFar);
#endif