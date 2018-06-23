#include "Interpretador.h"

/* Funções do interpretador */
void Intrp_start(FILE *arq, ASTNode *arvSint){
	arvSint->interpret(arq, arvSint);
}

float Intpr_ASTNode(FILE *arq, ASTNode *self){
	ASTNode *this = (ASTNode*) self;
	int i;
	for(i = 0; i < this->filhos->qnt; i++){
		No *elmnt = this->filhos->get(this->filhos, i);
		ASTNode *no = elmnt->valor;
		no->interpret(arq, no);
	}
	return NAN;
}

float Intpr_ASTBloco(FILE *arq, ASTNode *self){
	//ASTBloco *this = (ASTBloco*) self;
	return Intpr_ASTNode(arq, self);
}

float Intpr_Expr(FILE *arq, ASTNode *self){
	//Expr *this = (Expr*) self;
	return Intpr_ASTNode(arq, self);
}

float Intpr_Idntf(FILE *arq, ASTNode *self){
	Idntf *this = (Idntf*) self;
	if(strcmp(self->nome, "Idntf_NULL") == 0){
		fprintf(arq, "Erro Interpretador: Identificador nao declarado\n");
		exit(4);
	}
	return this->id->valor;
}

float Intpr_Numero(FILE *arq, ASTNode *self){
	Numero *this = (Numero*) self;
	return this->valorFloat;
}

float Intpr_LogicalOp(FILE *arq, ASTNode *self){
	LogicalOp *this = (LogicalOp*) self;

	/* Recebendo os operandos da operação */
	Expr *expr1 = (Expr*)((ASTNode*)this)
					->filhos->get(
						((ASTNode*)this)->filhos,
						0
					)->valor;

	Expr *expr2 = (Expr*)((ASTNode*)this)
					->filhos->get(
						((ASTNode*)this)->filhos,
						1
					)->valor;
					
	float v1 = ((ASTNode*)expr1)
				->interpret(arq, (ASTNode*)expr1);
	float v2 = ((ASTNode*)expr2)
				->interpret(arq, (ASTNode*)expr2);

	/* Caso um dos operandos não for inicializado */
	if(v1 == NAN || v2 == NAN){
		fprintf(arq, "Erro Interpretador: um dos operandos não é um " \
					 "número, ou não foi inicializado\n");
		exit(1);
	}

	/* Definindo as operações */
	if(strcmp("||",this->super.op) == 0){
		return v1 || v2;
	}else if(strcmp("&&",this->super.op) == 0){
		return v1 && v2;
	}

	/*TODO: Alterar o stdout da saida */
	/* Erro causados por essa função */
	fprintf(stdout, "Erro Interpretador: operação não existente: %s\n", this->super.op);
	exit(1);
}

float Intpr_RelOp(FILE *arq, ASTNode *self){
	RelOp *this = (RelOp*) self;

	/* Recebendo os operandos da operação */
	Expr *expr1 = (Expr*)((ASTNode*)this)
					->filhos->get(
						((ASTNode*)this)->filhos,
						0
					)->valor;

	Expr *expr2 = (Expr*)((ASTNode*)this)
					->filhos->get(
						((ASTNode*)this)->filhos,
						1
					)->valor;
					
	float v1 = ((ASTNode*)expr1)
				->interpret(arq, (ASTNode*)expr1);
	float v2 = ((ASTNode*)expr2)
				->interpret(arq, (ASTNode*)expr2);

	/* Caso um dos operandos não for inicializado */
	if(v1 == NAN || v2 == NAN){
		fprintf(arq, "Erro Interpretador: um dos operandos não é um " \
					 "número, ou não foi inicializado\n");
		exit(1);
	}

	/* Definindo as operações */
	if(strcmp("==",this->super.op) == 0){
		return v1 == v2;
	}else if(strcmp("!=",this->super.op) == 0){
		return v1 != v2;
	}else if(strcmp("<",this->super.op) == 0){
		return v1 < v2;
	}else if(strcmp("<=",this->super.op) == 0){
		return v1 <= v2;
	}else if(strcmp(">",this->super.op) == 0){
		return v1 > v2;
	}else if(strcmp(">=",this->super.op) == 0){
		return v1 >= v2;
	}

	/*TODO: Alterar o stdout da saida */
	/* Erro causados por essa função */
	fprintf(stdout, "Erro Interpretador: operação não existente: %s\n", this->super.op);
	exit(1);
}

float Intpr_ArithOp(FILE *arq, ASTNode *self){
	ArithOp *this = (ArithOp*) self;

	/* Recebendo os operandos da operação */
	Expr *expr1 = (Expr*)((ASTNode*)this)
					->filhos->get(
						((ASTNode*)this)->filhos,
						0
					)->valor;

	Expr *expr2 = (Expr*)((ASTNode*)this)
					->filhos->get(
						((ASTNode*)this)->filhos,
						1
					)->valor;
					
	float v1 = ((ASTNode*)expr1)
				->interpret(arq, (ASTNode*)expr1);
	float v2 = ((ASTNode*)expr2)
				->interpret(arq, (ASTNode*)expr2);

	/* Caso um dos operandos não for inicializado */
	if(v1 == NAN || v2 == NAN){
		fprintf(arq, "Erro Interpretador: um dos operandos não é um " \
					 "número, ou não foi inicializado\n");
		exit(1);
	}

	/* Definindo as operações */
	if(strcmp("+",this->super.op) == 0){
		return v1 + v2;
	}else if(strcmp("-",this->super.op) == 0){
		return v1 - v2;
	}else if(strcmp("*",this->super.op) == 0){
		return v1 * v2;
	}else if(strcmp("/",this->super.op) == 0){
		if(v2 == 0){
			fprintf(stdout, "Erro Interpretador: divisao por 0\n");
			exit(3);
		}
		return v1 / v2;
	}

	/*TODO: Alterar o stdout da saida */
	/* Erro causados por essa função */
	fprintf(stdout, "Erro Interpretador: operação não existente: %s\n", this->super.op);
	exit(1);
}

float Intpr_Attr(FILE *arq, ASTNode *self){
	Attr *this = (Attr*) self;

	/* Recebendo o id e expressão para a atribuição */
	Idntf *id = (Idntf*) &(this->id);
	Expr *expr = (Expr*)((ASTNode*)this)
		->filhos->get(
			((ASTNode*)this)->filhos,
			1
		)->valor;

	if(strcmp(id->super.super.nome, "Idntf_NULL") == 0){
		fprintf(arq, "Erro Interpretador: Identificador nao declarado\n");
		exit(4);
	}

	/* Recebendo o valor da expressão */
	float valor = ((ASTNode*)expr)->interpret(arq,
		((ASTNode*)expr
	));

	/* Se não for uma expressão válida */
	if(valor == NAN){
		fprintf(arq, "Erro Interpretador: um dos operandos não é um " \
					 "número, ou não foi inicializado\n");
		exit(1);
	}

	/* Realizando a atribuição do valor em id (Tabela de símbolos) */
	id->id->valor = valor;

	return NAN;
}

float Intpr_If(FILE *arq, ASTNode *self){
	If *this = (If*) self;

	/* Pegando a expressão da condição */
	Expr *expr = (Expr*)((ASTNode*)this)
		->filhos->get(
			((ASTNode*)this)->filhos,
			0
		)->valor;

	/* Recebendo o valor da expressão */
	float valor = ((ASTNode*)expr)->interpret(arq,
		((ASTNode*)expr
	));

	/* Se não for uma expressão válida */
	if(valor == NAN){
		fprintf(arq, "Erro Interpretador: um dos operandos não é um " \
					 "número, ou não foi inicializado\n");
		exit(1);
	}

	/* Bloco executado quando verdadeiro */
	if(valor != 0){
		this->ifTrue.interpret(arq, &(this->ifTrue));
	}
	/* Bloco executado quando falso */
	else{
		/* Se houver um else para ser executado */
		if(((ASTNode*)this)->filhos->qnt > 2){
			this->ifTrue.interpret(arq, &(this->ifFalse));
		}
	}

	return NAN;
}

/*@Err: Possível erro ao calcular a volta do while */
float Intpr_While(FILE *arq, ASTNode *self){
	While *this = (While*) self;

	/* Pegando a expressão da condição */
	Expr *expr = (Expr*)((ASTNode*)this)
		->filhos->get(
			((ASTNode*)this)->filhos,
			0
		)->valor;

	/* Recebendo o valor da expressão */
	float valor = ((ASTNode*)expr)->interpret(arq,
		((ASTNode*)expr
	));

	/* Se não for uma expressão válida */
	if(valor == NAN){
		fprintf(arq, "Erro Interpretador: um dos operandos não é um " \
					 "número, ou não foi inicializado\n");
		exit(1);
	}

	while(valor != 0){
		this->ifTrue.interpret(arq, &(this->ifTrue));
		valor = expr->super.interpret(arq,((ASTNode*)expr));
	}

	return NAN;
}

float Intpr_For(FILE *arq, ASTNode *self){
	For *this = (For*) self;
	
	Expr *expr = (Expr*)((ASTNode*)this)
	->filhos->get(
		((ASTNode*)this)->filhos,
		1
	)->valor;
	
	((ASTNode*)&this->init)->interpret(arq, ((ASTNode*)&this->init));
	float valor = expr->super.interpret(arq,(ASTNode*)expr);
	while(valor != 0){
		this->ifTrue.interpret(arq, &(this->ifTrue));

		((ASTNode*)&this->incrmnt)->interpret(arq, ((ASTNode*)&this->incrmnt));
		valor = expr->super.interpret(arq,(ASTNode*)expr);
	}

	return NAN;
}

float Intpr_Read(FILE *arq, ASTNode *self){
	Read *this = (Read*) self;
	Idntf *id = (Idntf*) &(this->id);

	if(strcmp(id->super.super.nome, "Idntf_NULL") == 0){
		fprintf(arq, "Erro Interpretador: Identificador nao declarado\n");
		exit(4);
	}

	scanf("%f", &(id->id->valor));
	return NAN;
}

float Intpr_Print(FILE *arq, ASTNode *self){
	//Print *this = (Print*) self;

	/* Pegando a expressão da condição */
	Expr *expr = (Expr*) self->filhos->get(self->filhos, 0)->valor;

	/* Recebendo o valor da expressão */
	float valor = ((ASTNode*)expr)->interpret(arq,
		((ASTNode*)expr
	));

	/* Se não for uma expressão válida */
	if(valor == NAN){
		fprintf(arq, "Erro Interpretador: um dos operandos não é um " \
					 "número, ou não foi inicializado\n");
		exit(1);
	}

	/* Exibindo o valor conforme o tipo da variável*/
	if(expr->type == tINT){
		fprintf(arq, "%d\n", (int) valor);
	}else{
		fprintf(arq, "%.30g\n", valor);
	}

	return NAN;
}

/* Construtores */
Interpretador* new_Interpretador(){
	Interpretador *novo = malloc(sizeof(Interpretador));
	novo->start = Intrp_start;
	return novo;
}

/* Destrutores */
void del_Interpretador(Interpretador *self){
	
}
