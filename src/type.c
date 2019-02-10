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

	
Type checkBinaryOp(Type left, Type right, ExpressionKind kind,
	int lineno) {
	
	switch (kind) {
		// standard math + string concat
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
				
				// everything else is incorrect
				else printBinaryError(left, right, kind, lineno);
			}
			// same type
			else return left;
			
			break;
			
		// comparisons
		case k_expressionKindGEQ:
		case k_expressionKindLEQ:
		case k_expressionKindGreater:
		case k_expressionKindLesser:
		case k_expressionKindEqual:
		case k_expressionKindNEqual:
		
			if (left == right) return left;
			else printBinaryError(left, right, kind, lineno);
			
			break;
			
		// strictly boolean binary op
		case k_expressionKindAnd:
		case k_expressionKindOr:
			
			if ((left == t_boolean) && (right == t_boolean)) 
				return t_boolean;
			else printBinaryError(left, right, kind, lineno);
			
			break;
	}
	
}

Type checkUnaryOp(Type unary, ExpressionKind kind, int lineno){
	
	switch (kind) {
		case k_expressionKindNot:
			
			if (unary != t_boolean) 
				printUnaryError(unary, kind, lineno);
			else return t_boolean;
			
			break;
			
		case k_expressionKindUMinus:
		
			if (unary == t_int) return t_int;
			else if (unary == t_float) return t_float;
			else printUnaryError(unary, kind, lineno);
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