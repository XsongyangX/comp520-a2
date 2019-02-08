#include <stdio.h>
#include "pretty.h"

void prettyProgram(Program *program) {
    
	# null case
	if (program == NULL) {
		printf("\n");
		return;
	}
	
	switch (program->kind) {
		
		case k_programKindControlFlow:
			
			prettyControlFlow(program->content.controlFlow.controlFlow);
			prettyProgram(program->content.controlFlow.next);
			
			break;
			
		case k_programKindStatement:
			
			prettyStatement(program->content.statement.statement);
			prettyProgram(program->content.statement.next);
			
			break;
	}
}