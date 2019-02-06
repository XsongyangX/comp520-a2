#include <stdlib.h>
#include "tree.h"

extern int yylineno;

Program *makeProgram(ProgramKind kind, Program *program, Program *oneLine){
	
	Program *p = malloc(sizeof(Program));
	p->lineno = yylineno;
	p->kind = k_programKindProgram;
	p->binary.program = program;
	p->binary.oneLine = oneLine;
	return p;
}

