#include "ASTNodes.h"

void addChild(ASTNode *dest, ASTNode *novo){
	dest->filhos->add(dest->filhos,novo,sizeof(*novo),final);
}

/* Construtores */
	ASTNode new_ASTNode(char nome[str_size], char tipo[str_size]){
		ASTNode novo;
		strcpy(novo.nome, nome);
		strcpy(novo.tipo, tipo);
		novo.filhos = new_Lista();
		
		novo.print = print_ASTNode;
		novo.del = del_ASTNode;
		return novo;
	}

	ASTBloco new_ASTBloco(){
		ASTBloco novo = new_ASTNode("ASTBloco","ASTNode");
		strcpy(novo.nome, "BLOCO");

		novo.print = print_ASTBloco;
		novo.del = del_ASTBloco;
		return novo;
	}

	Expr new_Expr(char nome[str_size]){
		ASTNode super = new_ASTNode(nome,"Expr");
		Expr novo;
		build(&novo,&super);
		strcpy(novo.op,"");
		
		novo.super.print = print_Expr;
		novo.super.del = del_Expr;
		return novo;
	}

	Idntf new_Idntf(Token *tkn, char type[str_size]){
		Expr super = new_Expr("Idntf");
		Idntf novo;
		build(&novo,&super);
		novo.super.type = (strcmp(type,"INT")==0?tINT:tFLOAT);
		novo.super.valorFloat = novo.super.valorInteiro = 0;

		EntradaTabela *entrada = TabelaDeSimbolos->get(TabelaDeSimbolos,tkn->nome);
		novo.id = entrada;

		(*(ASTNode*)&novo).print = print_Idntf;
		(*(ASTNode*)&novo).del = del_Idntf;
		return novo;
	}

	Numero new_Numero(Token *entry, int type){
		Expr super = new_Expr("Num");
		Numero novo;
		build(&novo,&super);

		novo.type = type;
		novo.valorInteiro = atoi(entry->nome);
		novo.valorFloat = atof(entry->nome);

		(*(ASTNode*)&novo).print = print_Numero;
		(*(ASTNode*)&novo).del = del_Numero;
		return novo;
	}

	LogicalOp new_LogicalOp(char op[str_size], Expr *e1, Expr *e2){
		Expr super = new_Expr("LogicalOp");
		LogicalOp novo;
		build(&novo, &super);

		strcpy(novo.super.op,op);
		novo.super.type = e1->type || e2->type;
		/* TODO: calculate result of LogicalOp */
		
		novo.e1 = *e1;
		novo.e2 = *e2;

		addChild((ASTNode*)&novo, (ASTNode*)e1);
		addChild((ASTNode*)&novo, (ASTNode*)e2);

		(*(ASTNode*)&novo).print = print_LogicalOp;
		(*(ASTNode*)&novo).del = del_LogicalOp;
		return novo;
	}

	RelOp new_RelOp(char op[str_size], Expr *e1, Expr *e2){
		Expr super = new_Expr("RelOp");
		RelOp novo;
		build(&novo, &super);

		strcpy(novo.super.op,op);
		novo.super.type = e1->type || e2->type;
		/* TODO: calculate result of RelOp */
		
		novo.e1 = *e1;
		novo.e2 = *e2;

		addChild((ASTNode*)&novo, (ASTNode*)e1);
		addChild((ASTNode*)&novo, (ASTNode*)e2);

		(*(ASTNode*)&novo).print = print_RelOp;
		(*(ASTNode*)&novo).del = del_RelOp;
		return novo;
	}

	ArithOp new_ArithOp(char op[str_size], Expr *e1, Expr *e2){
		Expr super = new_Expr("ArithOp");
		ArithOp novo;
		build(&novo, &super);

		strcpy(novo.super.op,op);
		novo.super.type = e1->type || e2->type;
		/* TODO: calculate result of ArithOp */
		
		novo.e1 = *e1;
		novo.e2 = *e2;

		addChild((ASTNode*)&novo, (ASTNode*)e1);
		addChild((ASTNode*)&novo, (ASTNode*)e2);

		(*(ASTNode*)&novo).print = print_ArithOp;
		(*(ASTNode*)&novo).del = del_ArithOp;
		return novo;
	}

	Attr new_Attr(Idntf *id, Expr *e){
		ASTNode super = new_ASTNode("Attr","ASTNode");
		Attr novo;
		build(&novo, &super);

		novo.id = *id;
		novo.expr = *e;

		addChild((ASTNode*)&novo, (ASTNode*)id);
		addChild((ASTNode*)&novo, (ASTNode*)e);

		novo.super.print = print_Attr;
		novo.super.del = del_Attr;
		return novo;
	}

	If new_If(Expr *cond, ASTNode *ifTrue, ASTNode *ifFalse){
		ASTNode super = new_ASTNode("If","ASTNode");
		If novo;
		build(&novo, &super);

		novo.condicao = *cond;
		novo.ifTrue = *ifTrue;
		novo.ifFalse= *ifFalse;

		addChild((ASTNode*)&novo, (ASTNode*)cond);
		addChild((ASTNode*)&novo, (ASTNode*)ifTrue);
		addChild((ASTNode*)&novo, (ASTNode*)ifFalse);

		novo.super.print = print_If;
		novo.super.del = del_If;
		return novo;
	}

	While new_While(Expr *condicao, ASTNode *ifTrue){
		ASTNode super = new_ASTNode("While","ASTNode");
		While novo;
		build(&novo, &super);

		novo.condicao = *condicao;
		novo.ifTrue = *ifTrue;

		addChild((ASTNode*)&novo, (ASTNode*)condicao);
		addChild((ASTNode*)&novo, (ASTNode*)ifTrue);

		novo.super.print = print_While;
		novo.super.del = del_While;
		return novo;
	}

	For new_For(Attr *init, Expr *cond, Attr *incr, ASTNode *ifTrue){
		ASTNode super = new_ASTNode("For","ASTNode");
		For novo;
		build(&novo, &super);

		novo.init = *init;
		novo.condicao = *cond;
		novo.incrmnt = *incr;
		novo.ifTrue = *ifTrue;

		addChild((ASTNode*)&novo, (ASTNode*)init);
		addChild((ASTNode*)&novo, (ASTNode*)cond);
		addChild((ASTNode*)&novo, (ASTNode*)incr);
		addChild((ASTNode*)&novo, (ASTNode*)ifTrue);

		novo.super.print = print_For;
		novo.super.del = del_For;
		return novo;
	}

	Read new_Read(Idntf *id){
		ASTNode super = new_ASTNode("Read","ASTNode");
		Read novo;
		build(&novo, &super);

		novo.id = *id;

		addChild((ASTNode*)&novo, (ASTNode*)id);

		novo.super.print = print_Read;
		novo.super.del = del_Read;
		return novo;
	}

	Print new_Print(Expr *saida){
		ASTNode super = new_ASTNode("Print","ASTNode");
		Print novo;
		build(&novo, &super);

		novo.saida = *saida;

		addChild((ASTNode*)&novo, (ASTNode*)saida);

		novo.super.print = print_Print;
		novo.super.del = del_Print;
		return novo;
	}

/*--------------------------------------------------*/
/* Destrutores */
	int delNode(void* self){
		ASTNode no = *(ASTNode*) self;
		no.del(&no);
		return true;
	}

	int del_ASTNode(void* self){
		ASTNode this = *(ASTNode*) self;
		del_Lista(this.filhos,delNode);
		return 1;
	}

	int del_ASTBloco(void* self){
		ASTBloco this = *(ASTBloco*) self;
		del_ASTNode(&this);
		return 1;
	}

	int del_Expr(void *self){
		Expr this = *(Expr*)self;
		del_ASTNode((ASTNode*)&this);
		return 1;
	}

	int del_Idntf(void *self){
		Idntf this = *(Idntf*)self;
		del_Expr((Expr*)&this);
		return 1;
	}

	int del_Numero(void *self){
		Numero this = *(Numero*)self;
		del_Expr((Expr*)&this);
		return 1;
	}


	int del_LogicalOp(void *self){
		LogicalOp this = *(LogicalOp*) self;

		del_Expr((Expr*)&this);
		return 1;
	}
	int del_RelOp(void *self){
		RelOp this = *(RelOp*) self;

		del_Expr((Expr*)&this);
		return 1;
	}
	int del_ArithOp(void *self){
		ArithOp this = *(ArithOp*) self;

		del_Expr((Expr*)&this);
		return 1;
	}

	int del_Attr(void* self){
		Attr this = *(Attr*) self;
		del_ASTNode(&this);
		return 1;
	}

	int del_If(void* self){
		If this = *(If*) self;
		del_ASTNode(&this);
		return 1;
	}

	int del_While(void* self){
		While this = *(While*) self;
		del_ASTNode(&this);
		return 1;
	}

	int del_For(void* self){
		For this = *(For*) self;
		del_ASTNode(&this);
		return 1;
	}

	int del_Read(void* self){
		Read this = *(Read*) self;
		del_ASTNode(&this);
		return 1;
	}

	int del_Print(void* self){
		Print this = *(Print*) self;
		del_ASTNode(&this);
		return 1;
	}
