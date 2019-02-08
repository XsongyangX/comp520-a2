#include <stdio.h>
#include "pretty.h"

char *t_typeToString(TypeToken t_type){
	
	switch (t_type) {
		case t_int:
			return "int";
			break;
		case t_float:
			return "float";
			break;
		case t_boolean:
			return "boolean";
			break;
		case t_string:
			return "string";
			break;
	}
	
	return "typeNotFound";
}

void printTabs(int tabsSoFar) {
	for(int i = 0; i < tabsSoFar; i++){
		printf("\t");
	}
}

void prettyProgram(Program *p, int tabsSoFar) {
    
	// null case
	if (p == NULL) {
		printf("\n");
		return;
	}
	
	switch (p->kind) {
		
		case k_programKindControlFlow:
			
			prettyControlFlow(p->content.controlFlow.controlFlow, tabsSoFar);
			prettyProgram(p->content.controlFlow.next, tabsSoFar);
			
			break;
			
		case k_programKindStatement:
			
			prettyStatement(p->content.statement.statement, tabsSoFar);
			printf(";\n");
			printTabs(tabsSoFar);
			prettyProgram(p->content.statement.next, tabsSoFar);
			
			break;
	}
}

void prettyControlFlow(ControlFlow *cf, int tabsSoFar) {
	
	// null case
	if (cf == NULL) {
		printf("\n");
		return;
	}
	
	switch (cf->kind){
		
		case k_controlFlowKindIf:
			// if statement + expression
			printf("if ( ");
			prettyExpression(cf->content.continuing.condition, 0); // 0 for conditionals
			printf(" )\n");
			printTabs(tabsSoFar); // for positioning {
			printf("{\n");
			
			tabsSoFar++; // one nesting deeper, one more tab
			printTabs(tabsSoFar); // print tabs in anticipation
			
			prettyProgram(cf->content.continuing.block, tabsSoFar);
			
			tabsSoFar--; // if nesting over, one less tab
			printTabs(tabsSoFar); // correctly position the closing }
			printf("}\n");
			
			printTabs(tabsSoFar); // print tabs in anticipation
			prettyControlFlow(cf->content.continuing.elsePart, tabsSoFar);
			
			break;
			
		case k_controlFlowKindElseIf:
			
			// else if statement + expression, similar to previous case
			printf("else if ( ");
			prettyExpression(cf->content.continuing.condition, 0); // 0 for conditionals
			printf(" )\n");
			printTabs(tabsSoFar); // for the {
			printf("{\n");
			
			tabsSoFar++; // one nesting deeper
			printTabs(tabsSoFar);
			
			prettyProgram(cf->content.continuing.block, tabsSoFar);
			
			tabsSoFar--; // else if nesting over
			printTabs(tabsSoFar); // correctly position the }
			printf("}\n");
			
			printTabs(tabsSoFar); // print tabs in anticipation
			prettyControlFlow(cf->content.continuing.elsePart, tabsSoFar);
			
			break;
			
		case k_controlFlowKindElse:
			
			printf("else\n");
			printTabs(tabsSoFar);
			printf("{\n");
			
			tabsSoFar++; // one nesting deeper
			printTabs(tabsSoFar);
			
			prettyProgram(cf->content.block, tabsSoFar);
			
			tabsSoFar--; // one nesting over
			printTabs(tabsSoFar);
			printf("}\n");
			
			printTabs(tabsSoFar); // in anticipation
			
			break;
			
		case k_controlFlowKindWhile:
			
			printf("while ( ");
			prettyExpression(cf->content.whileLoop.condition, 0); // 0 for conditionals
			printf(" )\n");
			printTabs(tabsSoFar);
			printf("{\n");
			
			tabsSoFar++; // one nesting deeper
			printTabs(tabsSoFar); 
			
			prettyProgram(cf->content.whileLoop.block, tabsSoFar);
			
			tabsSoFar--;
			printTabs(tabsSoFar);
			printf("}\n");
			
			printTabs(tabsSoFar); // in anticipation
			
			break;
	}
	
}

void prettyStatement(Statement *s, int tabsSoFar) {
	
	switch (s->kind){
		
		case k_statementKindAssignment:
		
			printf("%s = ", s->content.assign.identifier);
			prettyExpression(s->content.assign.assignment, 0); // 0 for assignments
			// to verify whether to tab or not
			break;
			
		case k_statementKindInitialization:
		
			printf("var %s: %s = ", s->content.initialization.identifier, 
				t_typeToString(s->content.initialization.t_type));
			prettyExpression(s->content.initialization.assignment, 0); // 0 for assignments
			// to verify whether to tab or not
			break;
			
		case k_statementKindDeclaration:
			
			printf("var %s: %s", s->content.var.identifier,
				t_typeToString(s->content.var.t_type));
			// to verify whether to tab 
			
			break;
			
		case k_statementKindRead:
		
			printf("read( %s )", s->content.identifier);
			// to verify whether to tab 
			break;
			
		case k_statementKindPrint:
		
			printf("print( ");
			prettyExpression(s->content.printValue, 0);
			printf(" )");
			// to verify whether to tab 
			break;
	} 
	
}

char *getOperationSymbols(ExpressionKind kind){
	
	switch (kind) {
		
		case k_expressionKindAdd:
			return "+";
			break;
		
		case k_expressionKindMinus:
		case k_expressionKindUMinus:
			return "-";
			break;
			
		case k_expressionKindTimes:
			return "*";
			break;
			
		case k_expressionKindDivide:
			return "/";
			break;
			
		case k_expressionKindNot:
			return "!";
			break;
			
		case k_expressionKindGEQ:
			return ">=";
			break;
			
		case k_expressionKindLEQ:
			return "<=";
			break;
			
		case k_expressionKindGreater:
			return ">";
			break;
			
		case k_expressionKindLesser:
			return "<";
			break;
			
		case k_expressionKindEqual:
			return "==";
			break;
			
		case k_expressionKindNEqual:
			return "!=";
			break;
			
		case k_expressionKindAnd:
			return "&&";
			break;
			
		case k_expressionKindOr:
			return "||";
			break;
	}
	
	return "notASymbol";
}

void prettyExpression(Expression *e, int tabsSoFar) {
	
	
	
}
