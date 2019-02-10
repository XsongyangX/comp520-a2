#include <stdio.h>

#include "emit.h"
#include "type.h"

FILE *targetFile;

void emitToFile(char *fileName) {
	targetFile = fopen(strcat(fileName, ".c"), "w");
}

void emitProgramStart(Program *root){
	emitProgram(root, 0);
}

void fprintTabs(int count){
	for (int i = 0; i < count; i++)
		fprintf(targetFile, "\t");
}

void emitProgram(Program *p, int tabs){
	
	switch (p->kind) {
		
		case k_programKindControlFlow:
			
			emitControlFlow(p->content.controlFlow.controlFlow, tabs);
			emitProgram(p->content.controlFlow.next, tabs);
		
			break;
			
		case k_programKindStatement:
			
			emitStatement(p->content.statement.statement);
			fprintf(targetFile, ";\n");
			fprintTabs(tabs);
			emitProgram(p->content.statement.next);
			
			break;
	}
}

void emitControlFlow(ControlFlow *cf, int tabs){
	
	switch (cf->kind)
	
}