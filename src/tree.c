#include <stdlib.h>
#include "tree.h"

extern int yylineno;

Program *makeProgram_controlFlow(ProgramKind kind, ControlFlow *controlFlow, 
	Program *next){
	
	Program *p = malloc(sizeof(Program));
	p->lineno = yylineno;
	p->kind = k_programKindProgram;
	
	p->content.controlFlow.controlFlow = controlFlow;
	p->content.controlFlow.next = next;
	
	return p;
}

