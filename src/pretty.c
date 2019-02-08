#include <stdio.h>
#include <string.h>
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

void prettyExpression(Expression *e, int tabsSoFar) {
	
	switch (e->kind) {
		// non-operation 
		case k_expressionKindIdentifier:
			printf("%s", e->content.identifier);
			break;
			
		case k_expressionKindBooleanLiteral:
			printf("%s", e->content.boolean);
			break;
			
		case k_expressionKindIntLiteral:
			printf("%s", e->content.intVal);
			break;
			
		case k_expressionKindFloatLiteral:
			printf("%s", e->content.floatVal);
			break;
			
		case k_expressionKindStringLiteral:
			printf("%s", e->content.string);
			break;
		
		// operations
		// unary
		case k_expressionKindNot:
			printf("!");
			prettyExpression(e->content.unary);
			break;
			
		case k_expressionKindUMinus:
			printf("-");
			prettyExpression(e->content.unary);
			break;
			
		// binary
		case k_expressionKindAdd:
			prettyExpression(e->content.binary.left);
			printf("+");
			prettyExpression(e->content.binary.right);
			break;
			
		case k_expressionKindMinus:
			prettyExpression(e->content.binary.left);
			printf("-");
			prettyExpression(e->content.binary.right);
			break;
			
		case k_expressionKindTimes:
			prettyExpression(e->content.binary.left);
			printf("*");
			prettyExpression(e->content.binary.right);
			break;
			
		case k_expressionKindDivide:
			prettyExpression(e->content.binary.left);
			printf("/");
			prettyExpression(e->content.binary.right);
			break;
			
		case k_expressionKindGEQ:
			prettyExpression(e->content.binary.left);
			printf(">=");
			prettyExpression(e->content.binary.right);
			break;
			
		case k_expressionKindLEQ:
			prettyExpression(e->content.binary.left);
			printf("<=");
			prettyExpression(e->content.binary.right);
			break;
			
		case k_expressionKindGreater:
			prettyExpression(e->content.binary.left);
			printf(">");
			prettyExpression(e->content.binary.right);
			break;
			
		case k_expressionKindLesser:
			prettyExpression(e->content.binary.left);
			printf("<");
			prettyExpression(e->content.binary.right);
			break;
			
		case k_expressionKindEqual:
			prettyExpression(e->content.binary.left);
			printf("==");
			prettyExpression(e->content.binary.right);
			break;
			
		case k_expressionKindNEqual:
			prettyExpression(e->content.binary.left);
			printf("!=");
			prettyExpression(e->content.binary.right);
			break;
			
		case k_expressionKindAnd:
			prettyExpression(e->content.binary.left);
			printf("&&");
			prettyExpression(e->content.binary.right);
			break;
			
		case k_expressionKindOr:
			prettyExpression(e->content.binary.left);
			printf("||");
			prettyExpression(e->content.binary.right);
			break;
	}
}
