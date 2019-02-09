#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

typedef enum {
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
	k_statementKindPrint,
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

typedef enum {
	t_int,
	t_float,
	t_boolean,
	t_string
} Type;

typedef struct Program Program;
typedef struct ControlFlow ControlFlow;
typedef struct Statement Statement;
typedef struct Expression Expression;


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
		// for assignment
		struct {
			char *identifier;
			Expression *assignment;
		} assign;
		// for initialization
		struct {
			char *identifier;
			Type t_type;
			Expression *assignment;
		} initialization;
		// for declaration
		struct {
			char *identifier;
			Type t_type;
		} var;
		// for read
		char *identifier;
		// for print
		Expression *printValue;
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

Program *makeProgram_controlFlow(ControlFlow *controlFlow, 
	Program *next);
Program *makeProgram_statement(Statement *statement,
	Program *next);
	
ControlFlow *makeControlFlow_continuing(ControlFlowKind kind, 
	Expression *condition, Program *block, ControlFlow *elsePart);
ControlFlow *makeControlFlow_while(Expression *condition,
	Program *block);
ControlFlow *makeControlFlow_else(Program *block);

// for assignment
Statement *makeStatement_assign(char *identifier, Expression *assignment);
// for initialization
Statement *makeStatement_initialization(char *identifier, Type t_type,
	Expression *assignment);
// declaration
Statement *makeStatement_declaration(char *identifier, Type t_type);
// for read
Statement *makeStatement_read(char *identifier);
// for print
Statement *makeStatement_print(Expression *printValue);

Expression *makeExpression_binary(ExpressionKind kind, Expression *left,
	Expression *right);
Expression *makeExpression_unary(ExpressionKind kind, Expression *unary);
Expression *makeExpression_identifier(char *identifier);
Expression *makeExpression_boolean(bool literal);
Expression *makeExpression_int(int literal);
Expression *makeExpression_float(float literal);
Expression *makeExpression_string(char *string);


#endif
