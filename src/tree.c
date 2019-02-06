#include <stdlib.h>
#include "tree.h"

extern int yylineno;

Program *makeProgram(ProgramKind kind, Program *program, Program *next){
	
	Program *p = malloc(sizeof(Program));
	p->lineno = yylineno;
	p->kind = k_programKindProgram;
	p->list.program = program;
	p->list.next = next;
	return p;
}

