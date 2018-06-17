#ifndef __PRINT_AST_
#define __PRINT_AST_
	#include "HeaderPadrao.h"
	#include "ASTNodes.h"

	void printChild(FILE *arquivo, Lista *filhos);
	void print_ASTNode(FILE *arquivo, ASTNode* self);
	void print_ASTBloco(FILE *arquivo, ASTBloco* self);
	void print_Expr(FILE *arquivo, ASTNode *this);
	void print_Idntf(FILE *arquivo, ASTNode *this);
	void print_Numero(FILE *arquivo, ASTNode *this);
	void print_LogicalOp(FILE *arquivo, ASTNode* this);
	void print_RelOp(FILE *arquivo, ASTNode* this);
	void print_ArithOp(FILE *arquivo, ASTNode* this);
	void print_Attr(FILE *arquivo, ASTNode* this);
	void print_If(FILE *arquivo, ASTNode* this);
	void print_While(FILE *arquivo, ASTNode* this);
	void print_For(FILE *arquivo, ASTNode* this);
	void print_Read(FILE *arquivo, ASTNode* this);
	void print_Print(FILE *arquivo, ASTNode* this);
#endif //__PRINT_AST_