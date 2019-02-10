#ifndef EMIT_H
#define EMIT_H

#include "tree.h"

FILE *targetFile;

void emitToFile(char *fileName);

void emitProgramStart(Program *root);
void emitProgram(Program *p);
void emitControlFlow(ControlFlow *cf);
void emitStatement(Statement *s);
void emitExpression(Expression *e);

#endif 