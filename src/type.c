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