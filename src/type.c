#include <stdio.h>
#include <stdlib.h>

#include "type.h"

char *typeToString(Type t_type){
	switch (t_type) {
		case t_boolean:
			return "boolean";
			break;
		case t_float:
			return "float";
			break;
		case t_int:
			return "int";
			break;
		case t_string:
			return "string";
			break;
	}
}

void checkAssignCompatible(Type var, Type assigned, int lineno){
	
	if ((var == t_int && assigned == t_int)
		|| (var == t_float && assigned == t_float)
		|| (var == t_float && assigned == t_int)
		|| (var == t_string && assigned == t_string)
		|| (var == t_boolean && assigned == t_boolean)
		);
	else {
		fprintf(stderr, 
			"Error: (line %d) incompatible types: %s and %s\n",
			lineno,
			typeToString(var),
			typeToString(assigned));
		exit(1);
	}
	
}

void assign(Symbol *var, Symbol *assigned, int lineno){
	
	checkAssignCompatible(var->t_type, assigned->t_type, lineno);
	
	switch (var->t_type) {
		
		case t_boolean:
			var->value.boolean = assigned->value.boolean;
			break;
			
		case t_int:
			var->value.intVal = assigned->value.intVal;
			break;
			
		case t_float:
			
			switch (assigned->t_type) {
				
				case t_int:
					var->value.floatVal = assigned->value.intVal;
					break;
				
				case t_float:
					var->value.floatVal = assigned->value.floatVal;
					break;
			}
			break;
			
		case t_string:
			var->value.string = assigned->value.string;
			break;
	}
}

Type checkBinaryOp(Type left, Type right, ExpressionKind kind,
	int lineno) {
	
	switch (kind) {
		case k_expressionKindAdd:
		case k_expressionKindMinus:
		case k_expressionKindTimes:
		case k_expressionKindDivide:
		
			// no boolean
			if (left == t_boolean || right == t_boolean){
				printBinaryError(left, right, kind, lineno);
				exit(1);
			}
			
			break;
	}
	
}

void printBinaryError(Type left, Type right, ExpressionKind kind, int lineno) {
	
	fprintf(stderr, 
		"Error: (line %d) incompatible types for binary %s: %s and %s\n",
		lineno,
		opToString(kind),
		typeToString(left),
		typeToString(right));
}

char *opToString(ExpressionKind kind) {
	
}