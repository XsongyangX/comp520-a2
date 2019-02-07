#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

typedef enum {
	k_programKindProgram,
	k_programKindControlFlow,
	k_programKindStatement
} ProgramKind;

typedef enum {
	k_controlFlowKindIf,
	k_controlFlowKindElseIf,
	k_controlFlowKindElse,
	k_controlFlowKindWhile
} ControlFlowKind;

typedef enum {
	k_statementKindDeclaration,
	k_statementKindAssignment,
	k_statementKindInitialization,
	k_statememtKindPrint,
	k_statementKindRead
} StatementKind;

typedef enum {
	k_expressionKindAdd,
	k_expressionKindMinus,
	k_expressionKindTimes,
	k_expressionKindDivide,
	k_expressionKindNot,
	k_expressionKindUMinus,
	k_expressionKindGEQ,
	k_expressionKindLEQ,
	k_expressionKindGreater,
	k_expressionKindLesser,
	k_expressionKindEqual,
	k_expressionKindNEqual,
	k_expressionKindAnd,
	k_expressionKindOr,
	k_expressionKindIdentifier,
	k_expressionKindBooleanLiteral,
	k_expressionKindIntLiteral,
	k_expressionKindFloatLiteral,
	k_expressionKindStringLiteral
} ExpressionKind;

typedef struct Program Program;
typedef struct Expression Expression;
typedef struct ControlFlow ControlFlow;
typedef struct Statement Statement;


struct Program {
	int lineno;
	ProgramKind kind;
	union {
		// for control flows
		struct {
			ControlFlow *controlFlow;
			Program *next;
		} controlFlow;
		// for statements
		struct {
			Statement *statement;
			Program *next;
		} statement;
	} content;
	
};

struct Expression {
	int lineno;
	ExpressionKind kind;
	union {
		// for binary operations
		struct {
			Expression *left;
			Expression *right;
		} binary;
		// for unary operations
		Expression *unary;
		// for identifier
		char *identifier;
		// for literals
		bool boolean;
		int intVal;
		float floatVal;
		char *string;
	} content;
};

struct ControlFlow {
	int lineno;
	ControlFlowKind kind;
	union {
		// for a starting if statement and continuing else-if statement
		struct {
			Expression *condition;
			Program *block;
			ControlFlow *elsePart;
		} continuing;
		// for a terminating else statement
		Program *block;
		// for a while loop
		struct {
			Expression *condition;
			Program *block;
		} whileLoop;
	} content;
};

struct Statement {
	int lineno;
	StatementKind kind;
	union {
		// for initialization and assignment
		struct {
			char *identifier;
			Expression *assignment;
		} initialization;
		// for declaration and read
		char *identifier;
		// for print
		Expression *printValue;
	} content;
};


Program *makeProgram_controlFlow(ProgramKind kind, ControlFlow *controlFlow, 
	Program *next);
Program *makeProgram_statement(ProgramKind kind, Statement *statement,
	Program *next);
	
ControlFlow *makeControlFlow_if(ControlFlowKind kind, Expression *condition, 
	Program *block, ControlFlow *elsePart);
ControlFlow *makeControlFlow_while(ControlFlowKind kind, Expression *condition,
	Program *block);
#endif