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

	
	checkAssignCompatible(var, assigned, lineno);
	
	switch (var) {
		
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
			
			// different types
			if (left != right) {
				
				// only int and float
				if ((left == t_int && right == t_float)
				|| (left == t_float && right == t_int)) return t_float;
				
				
			}
			
			break;
	}
	
}

void printBinaryError(Type left, Type right, ExpressionKind kind, int lineno) {
	
	fprintf(stderr, 
		"Error: (line %d) incompatible types for binary operation %s: %s and %s\n",
		lineno,
		opToString(kind),
		typeToString(left),
		typeToString(right));
}

char *opToString(ExpressionKind kind) {
	
	switch (kind) {
		case k_expressionKindAdd:
			return "+";
			break;
		case k_expressionKindMinus:
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
		case k_expressionKindUMinus:
			return "-";
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
}