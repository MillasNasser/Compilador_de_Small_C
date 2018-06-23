#include "ASTNodes.h"

int count = 0;

/* Impressão */
void XML_printChild(FILE *arquivo, Lista *filhos){
	int i;
	for(i = 0; i < filhos->qnt; i++){
		No *no = filhos->get(filhos,i);
		if(no == NULL){continue;}
		ASTNode *valor= (ASTNode*)no->valor;
		valor->print(arquivo, valor);
	}
}

void XML_noprint(FILE *arquivo, ASTNode* self){}

void printSpaces(FILE *arquivo){
	int i;
	for(i = 0; i < count; i++)
		fprintf(arquivo,"    ");
}

void XML_print_ASTNode(FILE *arquivo, ASTNode* self){
	Lista *filhos = ((ASTNode*)self)->filhos;

	printSpaces(arquivo);count++;
	fprintf(arquivo,"<AST>\n");
	
	XML_printChild(arquivo, filhos);

	count--;printSpaces(arquivo);
	fprintf(arquivo,"</AST>\n");
}

void XML_print_ASTBloco(FILE *arquivo, ASTBloco* self){
	Lista *filhos = ((ASTNode*)self)->filhos;

	printSpaces(arquivo);count++;
	fprintf(arquivo,"<Bloco>\n");
	
	XML_printChild(arquivo, filhos);

	count--;printSpaces(arquivo);
	fprintf(arquivo,"</Bloco>\n");
}

void XML_print_Expr(FILE *arquivo, ASTNode *this){
	Expr* self = (Expr*) this;
	Lista *filhos = ((ASTNode*)self)->filhos;

	printSpaces(arquivo);count++;
	fprintf(arquivo,"<Expr>\n");
	
	XML_printChild(arquivo, filhos);

	count--;printSpaces(arquivo);
	fprintf(arquivo,"</Expr>\n");
}

void XML_print_Idntf(FILE *arquivo, ASTNode *this){
	Idntf *self = (Idntf*)this;

	printSpaces(arquivo);count++;

	if(strcmp(((ASTNode*)self)->nome,"Idntf_NULL") == 0){
		fprintf(arquivo,"<Id/>\n");
		count--; return;
	}
	char tipo[50];
	if(strcmp(self->id->tipo,"INT") == 0){
		strcpy(tipo, "integer");
	}else{
		strcpy(tipo, "float");
	}
	fprintf(arquivo,"<Id lexema='%s' type='%s' />\n",
					self->id->lexema, tipo);
	count--;		
}

void XML_print_Numero(FILE *arquivo, ASTNode *this){
	Numero *self = (Numero*)this;
	if(self->type == tINT){
		printSpaces(arquivo);count++;
		fprintf(arquivo,"<Num value=%d type='%s' />\n",
				self->valorInteiro,"integer");
		count--;					
	}else{
		printSpaces(arquivo);count++;
		fprintf(arquivo,"<Num value=%.6g type='%s' />\n",
				self->valorFloat, "float");
		count--;					
	}       
}

void XML_print_LogicalOp(FILE *arquivo, ASTNode* this){
	LogicalOp *self = (LogicalOp*)this;
	Lista *filhos = ((ASTNode*)self)->filhos;

	printSpaces(arquivo);count++;
	fprintf(arquivo,"<LogicalOp op='%s'>\n",((Expr*)self)->op);
	
	XML_printChild(arquivo, filhos);

	count--;printSpaces(arquivo);
	fprintf(arquivo,"</LogicalOp>\n");
}

void XML_print_RelOp(FILE *arquivo, ASTNode* this){
	RelOp* self = (RelOp*) this;
	Lista *filhos = ((ASTNode*)self)->filhos;

	printSpaces(arquivo);count++;
	fprintf(arquivo,"<RelOp op='%s'>\n", ((Expr*)self)->op);
	
	XML_printChild(arquivo, filhos);

	count--;printSpaces(arquivo);
	fprintf(arquivo,"</RelOp>\n");
	
}

void XML_print_ArithOp(FILE *arquivo, ASTNode* this){
	ArithOp* self = (ArithOp*) this;
	Lista *filhos = ((ASTNode*)self)->filhos;

	printSpaces(arquivo);count++;
	fprintf(arquivo,"<ArithOp op='%s'>\n", ((Expr*)self)->op);
	
	XML_printChild(arquivo, filhos);

	count--;printSpaces(arquivo);
	fprintf(arquivo,"</ArithOp>\n");
}

void XML_print_Attr(FILE *arquivo, ASTNode* this){
	Attr* self = (Attr*) this;
	Lista *filhos = ((ASTNode*)self)->filhos;

	printSpaces(arquivo);count++;
	fprintf(arquivo,"<Attr>\n");
	
	XML_printChild(arquivo, filhos);

	count--;printSpaces(arquivo);
	fprintf(arquivo,"</Attr>\n");
}

void XML_print_If(FILE *arquivo, ASTNode* this){
	If* self = (If*) this;
	Lista *filhos = ((ASTNode*)self)->filhos;

	printSpaces(arquivo);count++;
	fprintf(arquivo,"<If>\n");
	
	XML_printChild(arquivo, filhos);

	count--;printSpaces(arquivo);
	fprintf(arquivo,"</If>\n");
}

void XML_print_While(FILE *arquivo, ASTNode* this){
	While* self = (While*) this;
	Lista *filhos = ((ASTNode*)self)->filhos;

	printSpaces(arquivo);count++;
	fprintf(arquivo,"<While>\n");
	
	XML_printChild(arquivo, filhos);

	count--;printSpaces(arquivo);
	fprintf(arquivo,"</While>\n");
}

void XML_print_For(FILE *arquivo, ASTNode* this){
	For* self = (For*) this;
	Lista *filhos = ((ASTNode*)self)->filhos;

	printSpaces(arquivo);count++;
	fprintf(arquivo,"<For>\n");
	
	XML_printChild(arquivo, filhos);

	count--;printSpaces(arquivo);
	fprintf(arquivo,"</For>\n");
}

void XML_print_Read(FILE *arquivo, ASTNode* this){
	Read* self = (Read*) this;
	Lista *filhos = ((ASTNode*)self)->filhos;

	printSpaces(arquivo);count++;
	fprintf(arquivo,"<Read>\n");
	
	XML_printChild(arquivo, filhos);

	count--;printSpaces(arquivo);
	fprintf(arquivo,"</Read>\n");
}

void XML_print_Print(FILE *arquivo, ASTNode* this){
	Print* self = (Print*) this;
	Lista *filhos = ((ASTNode*)self)->filhos;

	printSpaces(arquivo);count++;
	fprintf(arquivo,"<Print>\n");
	
	XML_printChild(arquivo, filhos);

	count--;printSpaces(arquivo);
	fprintf(arquivo,"</Print>\n");
}