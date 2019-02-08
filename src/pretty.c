#include <stdio.h>
#include "pretty.h"

void prettyProgram(Program *p) {
    
	// null case
	if (p == NULL) {
		printf("\n");
		return;
	}
	
	switch (p->kind) {
		
		case k_programKindControlFlow:
			
			prettyControlFlow(p->content.controlFlow.controlFlow);
			prettyProgram(p->content.controlFlow.next);
			
			break;
			
		case k_programKindStatement:
			
			prettyStatement(p->content.statement.statement);
			prettyProgram(p->content.statement.next);
			
			break;
	}
}

void prettyControlFlow(ControlFlow *cf) {
	
	// null case
	if (cf == NULL) {
		printf("\n");
		return;
	}
	
	switch (cf->kind){
		
		case k_controlFlowKindIf:
		case k_controlFlowKindElseIf:
			
			prettyExpression(cf->content.continuing.condition);
			prettyProgram(cf->content.continuing.block);
			prettyControlFlow(cf->content.continuing.elsePart);
			
			break;
			
		case k_controlFlowKindElse:
			
			prettyProgram(cf->content.block);
			
			break;
			
		case k_controlFlowKindWhile:
			
			prettyExpression(cf->content.whileLoop.condition);
			prettyProgram(cf->content.whileLoop.block);
			
			break;
	}
	
}

void prettyStatement(Statement *s) {
	
	switch (s->kind){
		
		case k_statementKindInitialization:
		case k_statementKindAssignment:
		
			printf();
		
			break;
	}
	
}
