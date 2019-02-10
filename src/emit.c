#include <stdio.h>

#include "emit.h"
#include "type.h"

void emitToFile(char *fileName) {
	targetFile = fopen(fileName, "w");
}

void emitProgramStart(Program *root){
	emitProgram(root);
}

void emitProgram(Program *p){
	
	switch (p->kind) {
		
		case k_programKindControlFlow:
			
			emitControlFlow(p->content.controlFlow.controlFlow);
			emitProgram(p->content.controlFlow.next);
		
			break;
			
		case k_programKindStatement:
			
			emitStatement(p->content.statement.statement);
			fprintf(targetFile, ";\n");
			emitProgram(p->content.statement.next);
			
			break;
			
	}
	
}