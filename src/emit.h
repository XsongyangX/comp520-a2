#ifndef EMIT_H
#define EMIT_H

#include "tree.h"


void emitToFile(char *fileName);

void emitProgramStart(Program *root);
void emitProgram(Program *p, int tabsSoFar);
void emitControlFlow(ControlFlow *cf, int tabsSoFar);
void emitStatement(Statement *s);
void emitExpression(Expression *e);

void fprintfTabs(int count);

char *appendX(char *word);
#endif 