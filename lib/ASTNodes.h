#ifndef __ASTNodes_H_
#define __ASTNodes_H_
	#include "HeaderPadrao.h"
	#include "TabelaSimbolos.h"
	#include "Token.h"
	#include "lista.h"

	#define tINT 0
	#define tFLOAT 1

/* Nós da árvore de sintaxe abstrata */
	/* Nó genérico */
	typedef struct s_ASTNode{
		char nome[str_size]; //Nome do no
		char tipo[str_size]; //Tipo de nó: ArithOp, Compound, etc
		Lista *filhos; //Filhos que o nó possui
		void (*print)(FILE *arq, struct s_ASTNode *self);
		int (*del)(void*);
	}ASTNode;

	/* Nó bloco */
	typedef ASTNode ASTBloco;

	/* Extrutura para as expressões */
	/* Nó genérico Expressão */
	typedef struct s_Expr{
		ASTNode super;
		char op[str_size];
		int type;
		int valorInteiro;
		float valorFloat;
	}Expr;

	/* Nó identificador */
	typedef struct s_Idntf{
		Expr super;
		EntradaTabela *id;
	}Idntf;

	/* Nó constante numérica */
	typedef Expr Numero;

	/* Operador Lógico */
	typedef struct s_LogicalOp{
		Expr super;
		Expr e1;
		Expr e2;
	}LogicalOp;

	/* Operador Relacional */
	typedef struct s_RelOp{
		Expr super;
		Expr e1;
		Expr e2;
	}RelOp;

	/* Operador Aritimético */
	typedef struct s_ArithOp{
		Expr super;
		Expr e1;
		Expr e2;
	}ArithOp;

	/* Nó de atribuição */
	typedef struct s_Attr{
		ASTNode super;
		Idntf id;
		Expr expr;
	}Attr;

	/* Nó condicional if */
	typedef struct s_If{
		ASTNode super;
		Expr condicao;
		ASTNode ifTrue;
		ASTNode ifFalse;
	}If;

	/* Nó laço While */
	typedef struct s_While{
		ASTNode super;
		Expr condicao;
		ASTNode ifTrue;
	}While;

	/* Nó laço For */
	typedef struct s_For{
		ASTNode super;
		Attr init;
		Expr condicao;
		Attr incrmnt;
		ASTNode ifTrue;
	}For;

	/* Nó de input Read */
	typedef struct s_Read{
		ASTNode super;
		Idntf id;
	}Read;

	/* Nó de output Print */
	typedef struct s_Print{
		ASTNode super;
		Expr saida;
	}Print;

/* Funções */
	void addChild(ASTNode *dest, ASTNode *novo);

/* Construtores */
	ASTNode* new_ASTNode(char nome[str_size], char tipo[str_size]);

	ASTBloco* new_ASTBloco();

	Expr* new_Expr(char nome[str_size]);

	Idntf* new_Idntf(Token *entry);

	Numero* new_Numero(Token *entry, int type);

	LogicalOp* new_LogicalOp(char op[str_size], Expr *e1, Expr *e2);

	RelOp* new_RelOp(char op[str_size], Expr *e1, Expr *e2);

	ArithOp* new_ArithOp(char op[str_size], Expr *e1, Expr *e2);

	Attr* new_Attr(Idntf *id, Expr *e);

	If* new_If(Expr *cond, ASTNode *ifTrue, ASTNode *ifFalse);

	While* new_While(Expr *condicao, ASTNode *ifTrue);

	For* new_For(Attr *init, Expr *cond, Attr *incr, ASTNode *ifTrue);

	Read* new_Read(Idntf *id);

	Print* new_Print(Expr *saida);

/* Destrutores */
	int del_ASTNode(void* self);
	int del_ASTBloco(void* self);
	int del_Expr(void* self);
	int del_Idntf(void* self);
	int del_Numero(void* self);
	int del_LogicalOp(void* self);
	int del_RelOp(void* self);
	int del_ArithOp(void* self);
	int del_Attr(void* self);
	int del_If(void* self);
	int del_While(void* self);
	int del_For(void* self);
	int del_Read(void* self);
	int del_Print(void* self);

#include "ASTnodesPrint.h"
#endif //__ASTNodes_H_