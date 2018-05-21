#include "Gramatica.h"

#define errSynt(TKN) {printf("Erro: esperado %s, lexema encontrado %s\
				\nLinha: %lu\n", TKN, getInLex(),\
				((Token*)tknVec->get(tknVec,index_entrada)->valor)->linha);\
				exit(-1);}

string getInLex(){
	Token *tokenEntrada = (Token*)tknVec->get(tknVec,index_entrada)->valor;
	return tokenEntrada->lexema;
}

bool match(string token){
	Token *tokenEntrada = (Token*)tknVec->get(tknVec,index_entrada)->valor;
	if(strcmp(tokenEntrada->lexema, token) == 0){
		index_entrada++;
		return true;
	}
	return false;
}

void Gramatica_init(){
	//printf("%s\n",__func__);
	index_entrada = 0;
	if(tknVec == NULL) exit(-2);
}

/* Inicio das definições da gramatica*/
bool Programa (){
	if(!match(INT)) errSynt(INT);
	if(!match(MAIN)) errSynt(MAIN);
	if(!match(LBRACKET)) errSynt(LBRACKET);
	if(!match(RBRACKET)) errSynt(RBRACKET);
	if(!match(LBRACE)) errSynt(LBRACE);
	Decl_Comando(0);
	if(!match(RBRACE)) errSynt(RBRACE);
	printf("PQP\n");
	return true;
}

void Decl_Comando (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Declaracao), 
	 fst_size(FIRST_Declaracao))){
		Declaracao(nivel+1);
		Decl_Comando(nivel+1);
	}else
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Comando), 
	 fst_size(FIRST_Comando))){
		Comando(nivel+1);
		Decl_Comando(nivel+1);
	}
}

void Declaracao (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Tipo), 
	 fst_size(FIRST_Tipo))){
		Tipo(nivel+1);
		if(!match(ID)) errSynt(ID);
		Decl2(nivel+1);
		return;
	}
	errSynt("de Declaracao");;
}

void Decl2 (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(match(COMMA)){
		if(!match(ID)) errSynt(ID);
		Decl2(nivel+1);
		return;
	}else if(match(PCOMMA)){
		return;
	}else if(match(ATTR)){
		Expressao(nivel+1);
		Decl2(nivel+1);
		return;
	}
	errSynt("de Decl2");
}

void Tipo (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(match(INT)) {
		return;
	}else if(match(FLOAT)) {
		return;
	}

	errSynt("de Tipo");
}

void Comando (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Bloco), 
	 fst_size(FIRST_Bloco))){
		Bloco(nivel+1);
		return;
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Atribuicao), 
	 fst_size(FIRST_Atribuicao))){
		Atribuicao(nivel+1);
		return;
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoSe), 
	 fst_size(FIRST_ComandoSe))){
		ComandoSe(nivel+1);
		return;
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoEnquanto), 
	 fst_size(FIRST_ComandoEnquanto))){
		ComandoEnquanto(nivel+1);
		return;
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoRead), 
	 fst_size(FIRST_ComandoRead))){
		ComandoRead(nivel+1);
		return;
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoPrint), 
	 fst_size(FIRST_ComandoPrint))){
		ComandoPrint(nivel+1);
		return;
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoFor), 
	 fst_size(FIRST_ComandoFor))){
		ComandoFor(nivel+1);
		return;
	}
	errSynt("de Comando");
}

void Bloco (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(!match(LBRACE)) errSynt(LBRACE);
	Decl_Comando(nivel+1);
	if(!match(RBRACE)) errSynt(RBRACE);
}

void Atribuicao (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(!match(ID)) errSynt(ID);
	if(!match(ATTR)) errSynt(ATTR);
	Expressao(nivel+1);
	if(!match(PCOMMA)) errSynt(PCOMMA);
}

void ComandoSe (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(!match(IF)) errSynt(IF);
	if(!match(LBRACKET)) errSynt(LBRACKET);
	Expressao(nivel+1);
	if(!match(RBRACKET)) errSynt(RBRACKET);
	Comando(nivel+1);
	ComandoSenao(nivel+1);
}

void ComandoSenao (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(match(ELSE)){
		Comando(nivel+1);
	}
}

void ComandoEnquanto (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(!match(WHILE)) errSynt(WHILE);
	if(!match(LBRACKET)) errSynt(LBRACKET);
	Expressao(nivel+1);
	if(!match(RBRACKET)) errSynt(RBRACKET);
	Comando(nivel+1);
}

void ComandoRead (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(!match(READ)) errSynt(READ);
	if(!match(ID)) errSynt(ID);
	if(!match(PCOMMA)) errSynt(PCOMMA);
}

void ComandoPrint (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(!match(PRINT)) errSynt(PRINT);
	if(!match(LBRACKET)) errSynt(LBRACKET);
	Expressao(nivel+1);
	if(!match(RBRACKET)) errSynt(RBRACKET);
	if(!match(PCOMMA)) errSynt(PCOMMA);
}

void ComandoFor(int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(!match(FOR)) errSynt(FOR);
	if(!match(LBRACKET)) errSynt(LBRACKET);
	AtribuicaoFor(nivel+1);
	if(!match(PCOMMA)) errSynt(PCOMMA);
	Expressao(nivel+1);
	if(!match(PCOMMA)) errSynt(PCOMMA);
	AtribuicaoFor(nivel+1);
	if(!match(RBRACKET)) errSynt(RBRACKET);
	Comando(nivel+1);
}

void AtribuicaoFor(int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(!match(ID)) errSynt(ID);
	if(!match(ATTR)) errSynt(ATTR);
	Expressao(nivel+1);
}

void Expressao (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	Conjuncao(nivel+1);
	ExpressaoOpc(nivel+1);
}

void ExpressaoOpc (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(match(OR)){
		Conjuncao(nivel+1);
		ExpressaoOpc(nivel+1);
	}
}

void Conjuncao(int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	Igualdade(nivel+1);
	ConjuncaoOpc(nivel+1);
}

void ConjuncaoOpc (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(match(AND)){
		Igualdade(nivel+1);
		ConjuncaoOpc(nivel+1);
	}
}

void Igualdade (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	Relacao(nivel+1);
	IgualdadeOpc(nivel+1);
}

void IgualdadeOpc(int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(inFirst(getInLex(),fst_toMtrx(FIRST_IgualdadeOpc),
	 fst_size(FIRST_IgualdadeOpc))){    
		OpIgual(nivel+1);
		Relacao(nivel+1);
		IgualdadeOpc(nivel+1);
	}
}

void OpIgual (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(match(EQ)){
		return;
	}else if(match(NE)){
		return;
	}

	errSynt("de OpIgual");
}

void Relacao (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	Adicao(nivel+1);
	RelacaoOpc(nivel+1);
}

void RelacaoOpc (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(inFirst(getInLex(),fst_toMtrx(FIRST_RelacaoOpc),
	 fst_size(FIRST_RelacaoOpc))){
		OpRel(nivel+1);
		Adicao(nivel+1);
		RelacaoOpc(nivel+1);
	}
}

void OpRel (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(match(LT)){
		return;
	}else if(match(LE)){
		return;
	}else if(match(GT)){
		return;
	}else if(match(GE)){
		return;
	}

	errSynt("de OpRel");
}

void Adicao (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	Termo(nivel+1);
	AdicaoOpc(nivel+1);
}

void AdicaoOpc (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(inFirst(getInLex(),fst_toMtrx(FIRST_AdicaoOpc),
	 fst_size(FIRST_AdicaoOpc))){
		OpAdicao(nivel+1);
		Adicao(nivel+1);
		RelacaoOpc(nivel+1);
	}
}

void OpAdicao (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(match(PLUS)){
		return;
	}else if(match(MINUS)){
		return;
	}

	errSynt("de OpAdicao");
}

void Termo (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	Fator(nivel+1);
	TermoOpc(nivel+1);
}

void TermoOpc (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(inFirst(getInLex(),fst_toMtrx(FIRST_TermoOpc),
	 fst_size(FIRST_TermoOpc))){
		OpMult(nivel+1);
		Fator(nivel+1);
		TermoOpc(nivel+1);
	}
}

void OpMult (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(match(MULT)){
		return;
	}else if(match(DIV)){
		return;
	}

	errSynt("de OpMult");
}

void Fator (int nivel){
	printf("%d%*c%s: %s\n",nivel,nivel,' ', __func__, getInLex());
	if(match(ID)){
		return;
	}else if(match(INTEGER_CONST)){
		return;
	}else if(match(FLOAT_CONST)){
		return;
	}else if(match(LBRACKET)){
		Expressao(nivel+1);
		if(!match(RBRACKET)) errSynt(RBRACKET);
	}

	errSynt("de Fator");
}