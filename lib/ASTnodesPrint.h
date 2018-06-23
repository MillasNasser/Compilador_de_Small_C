#ifndef __PRINT_AST_
#define __PRINT_AST_
	#include "HeaderPadrao.h"
	#include "ASTNodes.h"

	void XML_printChild(FILE *arquivo, Lista *filhos);
	void XML_noprint(FILE *arquivo, ASTNode* self);

	void XML_print_ASTNode(FILE *arquivo, ASTNode* self);
	void XML_print_ASTBloco(FILE *arquivo, ASTBloco* self);
	void XML_print_Expr(FILE *arquivo, ASTNode *this);
	void XML_print_Idntf(FILE *arquivo, ASTNode *this);
	void XML_print_Numero(FILE *arquivo, ASTNode *this);
	void XML_print_LogicalOp(FILE *arquivo, ASTNode* this);
	void XML_print_RelOp(FILE *arquivo, ASTNode* this);
	void XML_print_ArithOp(FILE *arquivo, ASTNode* this);
	void XML_print_Attr(FILE *arquivo, ASTNode* this);
	void XML_print_If(FILE *arquivo, ASTNode* this);
	void XML_print_While(FILE *arquivo, ASTNode* this);
	void XML_print_For(FILE *arquivo, ASTNode* this);
	void XML_print_Read(FILE *arquivo, ASTNode* this);
	void XML_print_Print(FILE *arquivo, ASTNode* this);
#endif //__PRINT_AST_