#include <stdio.h>
#include <string.h>

#include "emit.h"
#include "type.h"

FILE *targetFile;

void emitToFile(char *fileName) {
	targetFile = fopen(strcat(fileName, ".c"), "w");
}

void emitProgramStart(Program *root){
	// includes
	fprintf(targetFile, 
		"#include <stdio.h>\n#include <string.h>\n");
		
	// main function body
	fprintf(targetFile,
		"void main(){\n");
	emitProgram(root, 1);
	fprintf(targetFile, "}\n");
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
	
	
	Type readType;
	Type printType;
	
	switch (s->kind) {
		
		case k_statementKindDeclaration:
			
			// type identifier
			
			if (t_boolean == s->content.var.t_type)
				fprintf(targetFile, "int %s",
					s->content.var.identifier);
			else if (t_string == s->content.var.t_type);
				fprintf(targetFile, "char *%s",
					s->content.var.identifier);
			else
				fprintf(targetFile, "%s %s", 
					type,
					typeToString(s->content.var.t_type));
			break;
			
		case k_statementKindAssignment:
		
			fprintf(targetFile, "%s = ",
				s->content.assign.identifier);
			
			emitExpression(s->content.assign.assignment);
		
			break;
			
		case k_statementKindInitialization:
		
			// type identifier
			if (t_boolean == s->content.var.t_type)
				fprintf(targetFile, "int %s = ",
					s->content.var.identifier);
			else if (t_string == s->content.var.t_type);
				fprintf(targetFile, "char *%s = ",
					s->content.var.identifier);
			else
				fprintf(targetFile, "%s %s = ", 
					type,
					typeToString(s->content.var.t_type));
			
			emitExpression(s->content.initialization.assignment);
			
			break;
			
		case k_statementKindPrint:
		
			fprintf(targetFile, "printf(\"");
			
			printType = s->content.printValue->t_type;
			
			switch (printType) {
				case t_boolean:
					fprintf(targetFile, "%%d\",");
					break;
				case t_int:
					fprintf(targetFile, "%%d\",");
					break;
				case t_float:
					fprintf(targetFile, "%%f\",");
					break;
				case t_string:
					fprintf(targetFile, "%%s\",");
					break;
			}
			
			emitExpression(s->content.printValue);
			fprintf(targetFile, ")");
		
			break;
			
		case k_statementKindRead:
		
			fprintf(targetFile, "scanf(\"");
			
			readType = s->content.readVar.t_type;
			
			switch (readType) {
				case t_boolean:
					fprintf(targetFile, "%%d\",&");
					break;
				case t_int:
					fprintf(targetFile, "%%d\",&");
					break;
				case t_float:
					fprintf(targetFile, "%%f\",&");
					break;
				case t_string:
					fprintf(targetFile, "%%s\",");
					break;
			}
			
			fprintf(targetFile, "%s)", s->content.readVar.identifier);
		
			break;
	}
}

void emitExpression(Expression *e) {
	
	switch (e->kind) {
		case k_expressionKindAdd:
		case k_expressionKindMinus:
		case k_expressionKindTimes:
		case k_expressionKindDivide:
		case k_expressionKindGEQ:
		case k_expressionKindLEQ:
		case k_expressionKindGreater:
		case k_expressionKindLesser:
		case k_expressionKindEqual:
		case k_expressionKindNEqual:
		case k_expressionKindAnd:
		case k_expressionKindOr:
		
			emitExpression(e->content.binary.left);
			fprintf(targetFile, "%s", opToString(e->kind));
			emitExpression(e->content.binary.right);
			
			break;
			
		case k_expressionKindNot:
		case k_expressionKindUMinus:
		
			fprintf(targetFile, "%s", opToString(e->kind));
			emitExpression(e->content.unary);
			
			break;
			
		case k_expressionKindIdentifier:
			
			fprintf(targetFile, "%s", e->content.identifier);
			break;
			
		case k_expressionKindBooleanLiteral:
			
			if (e->content.boolean){
				fprintf(targetFile, "1");
			}
			else{
				fprintf(targetFile, "0");
			}
			break;
			
		case k_expressionKindIntLiteral:
		
			fprintf(targetFile, "%d", e->content.intVal);
			break;
			
		case k_expressionKindFloatLiteral:
		
			fprintf(targetFile, "%f", e->content.floatVal);
			break;
			
		case k_expressionKindStringLiteral:
		
			fprintf(targetFile, "%s", e->content.string);
			break;
			
	}
	
}