#include <stdio.h>
#include <string.h>

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
	
	if (p == NULL) return;
	
	switch (p->kind) {
		
		case k_programKindControlFlow:
			
			emitControlFlow(p->content.controlFlow.controlFlow, tabs);
			emitProgram(p->content.controlFlow.next, tabs);
		
			break;
			
		case k_programKindStatement:
			
			emitStatement(p->content.statement.statement);
			fprintf(targetFile, ";\n");
			fprintTabs(tabs);
			emitProgram(p->content.statement.next, tabs);
			
			break;
	}
}

void emitControlFlow(ControlFlow *cf, int tabs){
	
	if (cf == NULL) return;
	
	switch (cf->kind) {
		
		case k_controlFlowKindIf:
		
			fprintf(targetFile, "if (");
			emitExpression(cf->content.continuing.condition);
			fprintf(targetFile, "){\n");
			fprintTabs(tabs+1);
			
			emitProgram(cf->content.continuing.block, tabs + 1);
			fprintTabs(tabs);
			fprintf(targetFile, "}\n");
			
			fprintTabs(tabs);
			emitControlFlow(cf->content.continuing.elsePart, tabs);
			
			break;
		
		case k_controlFlowKindElseIf:
		
			fprintf(targetFile, "else if (");
			emitExpression(cf->content.continuing.condition);
			fprintf(targetFile, "){\n");
			fprintTabs(tabs+1);
			
			emitProgram(cf->content.continuing.block, tabs + 1);
			fprintTabs(tabs);
			fprintf(targetFile, "}\n");
			
			fprintTabs(tabs);
			emitControlFlow(cf->content.continuing.elsePart, tabs);
			
			break;
			
		case k_controlFlowKindElse:
		
			fprintf(targetFile, "else {\n");
			fprintTabs(tabs);
			
			emitProgram(cf->content.block, tabs + 1);
			fprintTabs(tabs);
			fprintf(targetFile, "}\n");
			
			fprintTabs(tabs);
			
			break;
			
		case k_controlFlowKindWhile:
		
			fprintf(targetFile, "while (");
			emitExpression(cf->content.whileLoop.condition);
			fprintf(targetFile, "){\n");
			fprintTabs(tabs + 1);
			
			emitProgram(cf->content.whileLoop.block, tabs+1);
			fprintTabs(tabs);
			fprintf(targetFile, "}\n");
			
			fprintTabs(tabs);
			
			break;
	}
}

void emitStatement(Statement *s){
	
}

void emitExpression(Expression *e) {
	
}