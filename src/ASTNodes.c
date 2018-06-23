#include "ASTNodes.h"

void addChild(ASTNode *dest, ASTNode *novo){
	dest->filhos->add(dest->filhos,novo,sizeof(*novo),final);
}

/* Construtores */
	ASTNode* new_ASTNode(char nome[str_size], char tipo[str_size]){
		ASTNode *novo = malloc(sizeof(ASTNode));
		strcpy(novo->nome, nome);
		strcpy(novo->tipo, tipo);
		novo->filhos = new_Lista();
		
		novo->print = XML_print_ASTNode;
		novo->interpret = Intpr_ASTNode;
		novo->del = del_ASTNode;
		return novo;
	}

	ASTBloco* new_ASTBloco(){
		ASTBloco *novo = new_ASTNode("ASTBloco","ASTNode");
		strcpy(novo->nome, "BLOCO");

		novo->print = XML_print_ASTBloco;
		novo->interpret = Intpr_ASTBloco;
		novo->del = del_ASTBloco;
		return novo;
	}

	Expr* new_Expr(char nome[str_size]){
		ASTNode *super = new_ASTNode(nome,"Expr");
		Expr *novo = malloc(sizeof(Expr));
		build(novo, super);
		free(super);
		strcpy(novo->op,"");
		
		novo->super.print = XML_print_Expr;
		novo->super.interpret = Intpr_Expr;
		novo->super.del = del_Expr;
		return novo;
	}

	Idntf* new_Idntf(Token *tkn){
		Expr *super = new_Expr("Idntf");
		Idntf *novo = malloc(sizeof(Idntf));
		build(novo, super);
		free(super);
		EntradaTabela *entry = 
			(EntradaTabela*)TabelaDeSimbolos
			->get(TabelaDeSimbolos,tkn->nome);
		if(entry == NULL){
			fprintf(logErro, "Erro Variavel '%s' nao declarada. Linha %lu\n", 
				tkn->nome, tkn->linha);
			
			strcpy((*(ASTNode*)novo).nome,"Idntf_NULL");
			(*(ASTNode*)novo).print = XML_print_Idntf;
			(*(ASTNode*)novo).interpret = Intpr_Idntf;
			(*(ASTNode*)novo).del = del_Idntf;
			return novo;
		}

		novo->super.type = (strcmp(entry->tipo,"INT")==0?tINT:tFLOAT);
		novo->super.valorFloat = novo->super.valorInteiro = 0;
 
		novo->id = entry;

		(*(ASTNode*)novo).print = XML_print_Idntf;
		(*(ASTNode*)novo).interpret = Intpr_Idntf;
		(*(ASTNode*)novo).del = del_Idntf;
		return novo;
	}

	Numero* new_Numero(Token *entry, int type){
		Expr *super = new_Expr("Num");
		Numero *novo = malloc(sizeof(Numero));
		build(novo, super);
		free(super);

		novo->type = type;
		novo->valorInteiro = atoi(entry->nome);
		novo->valorFloat = atof(entry->nome);

		(*(ASTNode*)novo).print = XML_print_Numero;
		(*(ASTNode*)novo).interpret = Intpr_Numero;
		(*(ASTNode*)novo).del = del_Numero;
		return novo;
	}

	LogicalOp* new_LogicalOp(char op[str_size], Expr *e1, Expr *e2){
		Expr *super = new_Expr("LogicalOp");
		LogicalOp *novo = malloc(sizeof(LogicalOp));
		build(novo, super);
		free(super);

		strcpy(novo->super.op,op);
		novo->super.type = e1->type || e2->type;
		/* TODO: calculate result of LogicalOp */
		
		novo->e1 = *e1;
		novo->e2 = *e2;

		addChild((ASTNode*)novo, (ASTNode*)e1);
		addChild((ASTNode*)novo, (ASTNode*)e2);

		(*(ASTNode*)novo).print = XML_print_LogicalOp;
		(*(ASTNode*)novo).interpret = Intpr_LogicalOp;
		(*(ASTNode*)novo).del = del_LogicalOp;
		return novo;
	}

	RelOp* new_RelOp(char op[str_size], Expr *e1, Expr *e2){
		Expr *super = new_Expr("RelOp");
		RelOp *novo = malloc(sizeof(RelOp));
		build(novo, super);
		free(super);

		strcpy(novo->super.op,op);
		novo->super.type = e1->type || e2->type;
		/* TODO: calculate result of RelOp */
		
		novo->e1 = *e1;
		novo->e2 = *e2;

		addChild((ASTNode*)novo, (ASTNode*)e1);
		addChild((ASTNode*)novo, (ASTNode*)e2);

		(*(ASTNode*)novo).print = XML_print_RelOp;
		(*(ASTNode*)novo).interpret = Intpr_RelOp;
		(*(ASTNode*)novo).del = del_RelOp;
		return novo;
	}

	ArithOp* new_ArithOp(char op[str_size], Expr *e1, Expr *e2){
		Expr *super = new_Expr("ArithOp");
		ArithOp *novo = malloc(sizeof(ArithOp));
		build(novo, super);
		free(super);

		strcpy(novo->super.op,op);
		novo->super.type = e1->type || e2->type;
		/* TODO: calculate result of ArithOp */
		
		novo->e1 = *e1;
		novo->e2 = *e2;

		addChild((ASTNode*)novo, (ASTNode*)e1);
		addChild((ASTNode*)novo, (ASTNode*)e2);

		(*(ASTNode*)novo).print = XML_print_ArithOp;
		(*(ASTNode*)novo).interpret = Intpr_ArithOp;
		(*(ASTNode*)novo).del = del_ArithOp;
		return novo;
	}

	Attr* new_Attr(Idntf *id, Expr *e){
		ASTNode *super = new_ASTNode("Attr","ASTNode");
		Attr *novo = malloc(sizeof(Attr));
		build(novo, super);
		free(super);

		novo->id = *id;
		novo->expr = *e;

		addChild((ASTNode*)novo, (ASTNode*)id);
		addChild((ASTNode*)novo, (ASTNode*)e);

		novo->super.print = XML_print_Attr;
		novo->super.interpret = Intpr_Attr;
		novo->super.del = del_Attr;
		return novo;
	}

	If* new_If(Expr *cond, ASTNode *ifTrue, ASTNode *ifFalse){
		ASTNode *super = new_ASTNode("If","ASTNode");
		If *novo = malloc(sizeof(If));
		build(novo, super);
		free(super);

		novo->condicao = *cond;
		novo->ifTrue = *ifTrue;

		addChild((ASTNode*)novo, (ASTNode*)cond);
		addChild((ASTNode*)novo, (ASTNode*)ifTrue);
		if(ifFalse != NULL){
			novo->ifFalse= *ifFalse;
			addChild((ASTNode*)novo, (ASTNode*)ifFalse);
		}
		novo->super.print = XML_print_If;
		novo->super.interpret = Intpr_If;
		novo->super.del = del_If;
		return novo;
	}

	While* new_While(Expr *condicao, ASTNode *ifTrue){
		ASTNode *super = new_ASTNode("While","ASTNode");
		While *novo = malloc(sizeof(While));
		build(novo, super);
		free(super);

		novo->condicao = *condicao;
		novo->ifTrue = *ifTrue;

		addChild((ASTNode*)novo, (ASTNode*)condicao);
		addChild((ASTNode*)novo, (ASTNode*)ifTrue);

		novo->super.print = XML_print_While;
		novo->super.interpret = Intpr_While;
		novo->super.del = del_While;
		return novo;
	}

	For* new_For(Attr *init, Expr *cond, Attr *incr, ASTNode *ifTrue){
		ASTNode *super = new_ASTNode("For","ASTNode");
		For *novo = malloc(sizeof(For));
		build(novo, super);
		free(super);

		novo->init = *init;
		novo->condicao = *cond;
		novo->incrmnt = *incr;
		novo->ifTrue = *ifTrue;

		addChild((ASTNode*)novo, (ASTNode*)init);
		addChild((ASTNode*)novo, (ASTNode*)cond);
		addChild((ASTNode*)novo, (ASTNode*)incr);
		addChild((ASTNode*)novo, (ASTNode*)ifTrue);

		novo->super.print = XML_print_For;
		novo->super.interpret = Intpr_For;
		novo->super.del = del_For;
		return novo;
	}

	Read* new_Read(Idntf *id){
		ASTNode *super = new_ASTNode("Read","ASTNode");
		Read *novo = malloc(sizeof(Read));
		build(novo, super);
		free(super);

		novo->id = *id;

		addChild((ASTNode*)novo, (ASTNode*)id);

		novo->super.print = XML_print_Read;
		novo->super.interpret = Intpr_Read;
		novo->super.del = del_Read;
		return novo;
	}

	Print* new_Print(Expr *saida){
		ASTNode *super = new_ASTNode("Print","ASTNode");
		Print *novo = malloc(sizeof(Print));
		build(novo, super);
		free(super);

		novo->saida = *saida;

		addChild((ASTNode*)novo, (ASTNode*)saida);

		novo->super.print = XML_print_Print;
		novo->super.interpret = Intpr_Print;
		novo->super.del = del_Print;
		return novo;
	}

/*--------------------------------------------------*/
/* Destrutores */
	int delNode(void* self){
		ASTNode *no = (ASTNode*) self;
		no->del(no);
		return true;
	}

	int del_ASTNode(void* self){
		ASTNode *this = (ASTNode*) self;
		del_Lista(this->filhos,delNode);
		free(this);
		return 1;
	}

	int del_ASTBloco(void* self){
		ASTBloco *this = (ASTBloco*) self;
		del_ASTNode(this);
		return 1;
	}

	int del_Expr(void *self){
		Expr *this = (Expr*)self;
		del_ASTNode((ASTNode*)this);
		return 1;
	}

	int del_Idntf(void *self){
		Idntf *this = (Idntf*)self;
		del_Expr((Expr*)this);
		return 1;
	}

	int del_Numero(void *self){
		Numero *this = (Numero*)self;
		del_Expr((Expr*)this);
		return 1;
	}


	int del_LogicalOp(void *self){
		LogicalOp *this = (LogicalOp*) self;

		del_Expr((Expr*)this);
		return 1;
	}
	int del_RelOp(void *self){
		RelOp *this = (RelOp*) self;

		del_Expr((Expr*)this);
		return 1;
	}
	int del_ArithOp(void *self){
		ArithOp *this = (ArithOp*) self;

		del_Expr((Expr*)this);
		return 1;
	}

	int del_Attr(void* self){
		Attr *this = (Attr*) self;
		del_ASTNode(this);
		return 1;
	}

	int del_If(void* self){
		If *this = (If*) self;
		del_ASTNode(this);
		return 1;
	}

	int del_While(void* self){
		While *this = (While*) self;
		del_ASTNode(this);
		return 1;
	}

	int del_For(void* self){
		For *this = (For*) self;
		del_ASTNode(this);
		return 1;
	}

	int del_Read(void* self){
		Read *this = (Read*) self;
		del_ASTNode(this);
		return 1;
	}

	int del_Print(void* self){
		Print *this = (Print*) self;
		del_ASTNode(this);
		return 1;
	}
