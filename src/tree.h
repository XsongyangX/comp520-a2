#ifndef TREE_H
#define TREE_H

typedef enum {
	k_programKindProgram,
	k_programKindDeclaration,
	k_programKindStatement
} ProgramKind;

typedef enum {
	
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
#endif