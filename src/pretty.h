#ifndef PRETTY_H
#define PRETTY_H

#include "tree.h"

void prettyProgram(Program *p);
void prettyControlFlow(ControlFlow *cf);
void prettyStatement(Statement *s);
void prettyExpression(Expression *e);

#endif