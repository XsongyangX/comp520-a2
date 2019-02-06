#ifndef TREE_H
#define TREE_H

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
} Statement;

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
struct Program {
	int lineno;
	ProgramKind kind;
	struct {
		Program *program;
		Program *oneLine;
	} binary;
};

Program *makeProgram(ProgramKind kind, Program *program, Program *oneLine);
#endif