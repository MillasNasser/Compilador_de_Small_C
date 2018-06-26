#include "TresEnderecos.h"

int gen_temp = 0;
int gen_labl = 0;

void Gen_start(FILE *arq, ASTNode *arvAbstr){
    arvAbstr->gen3Addr(arq, arvAbstr);
}

string Gen_ASTNode(FILE *arq, ASTNode *self){
    ASTNode *this = (ASTNode*) self;
	int i;
	for(i = 0; i < this->filhos->qnt; i++){
		No *elmnt = this->filhos->get(this->filhos, i);
		ASTNode *no = elmnt->valor;
		no->gen3Addr(arq, no);
	}
    return "";
}

string Gen_ASTBloco(FILE *arq, ASTNode *self){
    return Gen_ASTNode(arq, self);
}

string Gen_Expr(FILE *arq, ASTNode *self){
    return Gen_ASTNode(arq, self);
}

string Gen_Idntf(FILE *arq, ASTNode *self){
    Idntf *this = (Idntf*) self;
	if(strcmp(self->nome, "Idntf_NULL") == 0){
		fprintf(arq, "Erro Gen3Addr: Identificador nao declarado\n");
		exit(4);
	}
    string lexema = calloc(str_size, sizeof(char));
    sprintf(lexema,"%s", this->id->lexema);
	return lexema;
}

string Gen_Numero(FILE *arq, ASTNode *self){
    Numero *this = (Numero*) self;
    string num = calloc(str_size, sizeof(char));
    if(this->type == tINT){
        sprintf(num,"%d", this->valorInteiro);
    }else{
        sprintf(num,"%f", this->valorFloat);
    }
    
	return num;
}

string Gen_LogicalOp(FILE *arq, ASTNode *self){
    LogicalOp *this = (LogicalOp*) self;

	/* Recebendo os valores dos operandos da operação */
	string v1 = ((ASTNode*)this->e1)
				->gen3Addr(arq, (ASTNode*)this->e1);

	string v2 = ((ASTNode*)this->e2)
				->gen3Addr(arq, (ASTNode*)this->e2);

	/* Caso um dos operandos não for inicializado */
	if(strlen(v1) == 0 || strlen(v2) == 0){
		fprintf(arq, "Erro Gen3Addr: um dos operandos não é um " \
					 "número, ou não foi inicializado\n");
		exit(1);
	}

    string temp = calloc(str_size, sizeof(char));
    sprintf(temp, "t%d", gen_temp); gen_temp++;
	/* Definindo as operações */
	if(strcmp("||",this->super.op) == 0){
        fprintf(arq,"    %s = %s || %s\n", temp, v1, v2);
        free(v1); free(v2);
		return temp;
	}else if(strcmp("&&",this->super.op) == 0){
        fprintf(arq,"    %s = %s && %s\n", temp, v1, v2);
        free(v1); free(v2);
		return temp;
	}

    /*TODO: Alterar o stdout da saida */
	/* Erro causados por essa função */
	fprintf(stdout, "Erro gen3Addr: operação não existente: %s\n", this->super.op);
	exit(1);
}

string Gen_RelOp(FILE *arq, ASTNode *self){
    RelOp *this = (RelOp*) self;

    /* Recebendo os valores dos operandos da operação */
	string v1 = ((ASTNode*)this->e1)
				->gen3Addr(arq, (ASTNode*)this->e1);

	string v2 = ((ASTNode*)this->e2)
				->gen3Addr(arq, (ASTNode*)this->e2);

	/* Caso um dos operandos não for inicializado */
	if(strlen(v1) == 0 || strlen(v2) == 0){
		fprintf(arq, "Erro Gen3Addr: um dos operandos não é um " \
					 "número, ou não foi inicializado\n");
		exit(1);
	}

    string temp = calloc(str_size, sizeof(char));
    sprintf(temp, "t%d", gen_temp); gen_temp++;
	/* Definindo as operações */
    if(strcmp("==",this->super.op) == 0){
        fprintf(arq,"    %s = %s == %s\n", temp, v1, v2);
        free(v1); free(v2);
		return temp;
	}else if(strcmp("!=",this->super.op) == 0){
        fprintf(arq,"    %s = %s != %s\n", temp, v1, v2);
        free(v1); free(v2);
		return temp;
	}else if(strcmp("<",this->super.op) == 0){
        fprintf(arq,"    %s = %s < %s\n", temp, v1, v2);
        free(v1); free(v2);
		return temp;
	}else if(strcmp("<=",this->super.op) == 0){
        fprintf(arq,"    %s = %s <= %s\n", temp, v1, v2);
        free(v1); free(v2);
		return temp;
	}else if(strcmp(">",this->super.op) == 0){
        fprintf(arq,"    %s = %s > %s\n", temp, v1, v2);
        free(v1); free(v2);
		return temp;
	}else if(strcmp(">=",this->super.op) == 0){
        fprintf(arq,"    %s = %s >= %s\n", temp, v1, v2);
        free(v1); free(v2);
		return temp;
	}

    /*TODO: Alterar o stdout da saida */
	/* Erro causados por essa função */
	fprintf(stdout, "Erro gen3Addr: operação não existente: %s\n", this->super.op);
	exit(1);
}

string Gen_ArithOp(FILE *arq, ASTNode *self){
    ArithOp *this = (ArithOp*) self;
    
    /* Recebendo os valores dos operandos da operação */
	string v1 = ((ASTNode*)this->e1)
				->gen3Addr(arq, (ASTNode*)this->e1);

	string v2 = ((ASTNode*)this->e2)
				->gen3Addr(arq, (ASTNode*)this->e2);

	/* Caso um dos operandos não for inicializado */
	if(strlen(v1) == 0 || strlen(v2) == 0){
		fprintf(arq, "Erro Gen3Addr: um dos operandos não é um " \
					 "número, ou não foi inicializado\n");
		exit(1);
	}

    string temp = calloc(str_size, sizeof(char));
    sprintf(temp, "t%d", gen_temp); gen_temp++;
	/* Definindo as operações */
    if(strcmp("+",this->super.op) == 0){
        fprintf(arq,"    %s = %s + %s\n", temp, v1, v2);
        free(v1); free(v2);
		return temp;
	}else if(strcmp("-",this->super.op) == 0){
        fprintf(arq,"    %s = %s - %s\n", temp, v1, v2);
        free(v1); free(v2);
		return temp;
	}else if(strcmp("*",this->super.op) == 0){
        fprintf(arq,"    %s = %s * %s\n", temp, v1, v2);
        free(v1); free(v2);
		return temp;
	}else if(strcmp("/",this->super.op) == 0){
        fprintf(arq,"    %s = %s / %s\n", temp, v1, v2);
        free(v1); free(v2);
		return temp;
	}

    /*TODO: Alterar o stdout da saida */
	/* Erro causados por essa função */
	fprintf(stdout, "Erro gen3Addr: operação não existente: %s\n", this->super.op);
	exit(1);
}

string Gen_Attr(FILE *arq, ASTNode *self){
    Attr *this = (Attr*) self;

	/* Recebendo o id e expressão para a atribuição */
	Idntf *id = this->id;

	if(strcmp(id->super.super.nome, "Idntf_NULL") == 0){
		fprintf(arq, "Erro Interpretador: Identificador nao declarado\n");
		exit(4);
	}

	/* Recebendo o valor da expressão */
	string valor = ((ASTNode*)this->expr)->gen3Addr(arq,
		((ASTNode*)this->expr
	));

	/* Se não for uma expressão válida */
	if(strlen(valor) == 0){
		fprintf(arq, "Erro Interpretador: um dos operandos não é um " \
					 "número, ou não foi inicializado\n");
		exit(1);
	}

    fprintf(arq,"    %s = %s\n", id->id->lexema, valor);
	free(valor);

	return "";
}

string Gen_If(FILE *arq, ASTNode *self){
	If *this = (If*) self;

	string valor = ((ASTNode*)this->condicao)->gen3Addr(arq,
		((ASTNode*)this->condicao
	));

	string labelIsFalse = malloc(str_size * sizeof(char));
	sprintf(labelIsFalse,"IF%d", gen_labl);// gen_labl++;

	string labelExit = malloc(str_size * sizeof(char));
	sprintf(labelExit,"End%d", gen_labl); gen_labl++;

	fprintf(arq, "    if (%s == 0) goto %s\n", valor, labelIsFalse);
	this->ifTrue->gen3Addr(arq, this->ifTrue);
	fprintf(arq, "    goto %s\n", labelExit);
	if(this->ifFalse != NULL){
		fprintf(arq, "%s:\n", labelIsFalse);
		this->ifFalse->gen3Addr(arq, this->ifFalse);
	}
	fprintf(arq, "%s:\n", labelExit);

	free(valor);
	free(labelExit);
	free(labelIsFalse);
    return "";
}

string Gen_While(FILE *arq, ASTNode *self){
    While *this = (While*) self;

	/* Gerando o label de retorno para o while */
	string labelisTrue = malloc(str_size * sizeof(char));
	sprintf(labelisTrue, "WHILE%d", gen_labl);// gen_labl++;
	fprintf(arq, "%s:\n", labelisTrue);

	/* Gerando o label de saida para o while */
	string labelExit = malloc(str_size * sizeof(char));
	sprintf(labelExit,"End%d", gen_labl); gen_labl++;

	/* Pegando a condição do while */
	string valor = ((ASTNode*)this->condicao)->gen3Addr(arq,
		((ASTNode*)this->condicao
	));


	/* Imprimindo o teste da condição */
	fprintf(arq, "    if (%s == 0) goto %s\n", valor, labelExit);

	/* Imprimindo o conteúdo dentro do while */
	this->ifTrue->gen3Addr(arq, this->ifTrue);

	/* Salto incondicional para o label de retorno */
	fprintf(arq, "    goto %s\n", labelisTrue);

	/* Imprimindo o label de saida do while */
	fprintf(arq, "%s:\n", labelExit);

	free(valor);
	free(labelExit);
	free(labelisTrue);
    return "";
}

string Gen_For(FILE *arq, ASTNode *self){
	For *this = (For*) self;

	((ASTNode*)this->init)->gen3Addr(arq,
		((ASTNode*)this->init
	));

	string labelisTrue = malloc(str_size * sizeof(char));
	sprintf(labelisTrue, "FOR%d", gen_labl); //gen_labl++;
	fprintf(arq, "%s:\n", labelisTrue);

	string labelExit = malloc(str_size * sizeof(char));
	sprintf(labelExit,"End%d", gen_labl); gen_labl++;

	string valor = ((ASTNode*)this->condicao)->gen3Addr(arq,
		((ASTNode*)this->condicao
	));



	fprintf(arq, "    if (%s == 0) goto %s\n", valor, labelExit);
	this->ifTrue->gen3Addr(arq, this->ifTrue);

	((ASTNode*)this->incrmnt)->gen3Addr(arq,
		((ASTNode*)this->incrmnt
	));
	fprintf(arq, "    goto %s\n", labelisTrue);

	fprintf(arq, "%s:\n", labelExit);

	free(valor);
	free(labelExit);
	free(labelisTrue);
    return "";
}

string Gen_Read(FILE *arq, ASTNode *self){
	Read *this = (Read*) self;
	Idntf *id = this->id;

	if(strcmp(id->super.super.nome, "Idntf_NULL") == 0){
		fprintf(arq, "Erro gen3Addr: Identificador nao declarado\n");
		exit(4);
	}

	fprintf(arq, "    @sys _sys_input_\n");
	fprintf(arq, "    %s = __IO_INPUT__\n", id->id->lexema);

    return "";
}

string Gen_Print(FILE *arq, ASTNode *self){
	Print *this = (Print*) self;

	/* Recebendo o valor da expressão */
	string valor = ((ASTNode*)this->saida)->gen3Addr(arq,
		((ASTNode*)this->saida
	));

	/* Se não for uma expressão válida */
	if(strlen(valor) == 0){
		fprintf(arq, "Erro Interpretador: um dos operandos não é um " \
					 "número, ou não foi inicializado\n");
		exit(1);
	}

	fprintf(arq, "    __IO_OUTPUT__ = %s\n", valor);
	fprintf(arq, "    @sys _sys_output_\n");

    return "";
}

/* Contrutores e destrutores */
Gerador* new_Gerador3Enderecos(){
    Gerador *novo = malloc(sizeof(Gerador));
    novo->start = Gen_start;
    return novo;
}

void del_Gerador3Enderecos(Gerador *self);
