#ifndef EMIT_H
#define EMIT_H

#include "tree.h"
#include <stdbool.h>

void emitToFile(char *fileName);

void emitProgramStart(Program *root);
void emitProgram(Program *p, int tabsSoFar);
void emitControlFlow(ControlFlow *cf, int tabsSoFar);
void emitStatement(Statement *s);
void emitExpression(Expression *e);

void fprintfTabs(int count);

bool appendX(char *word);
#endif 