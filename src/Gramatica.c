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
	Decl_Comando();
	if(!match(RBRACE)) errSynt(RBRACE);
	return true;
}

void Decl_Comando (){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Declaracao), 
	 fst_size(FIRST_Declaracao))){
		Declaracao();
		Decl_Comando();
	}else
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Comando), 
	 fst_size(FIRST_Comando))){
		Comando();
		Decl_Comando();
	}
}

void Declaracao (){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Tipo), 
	 fst_size(FIRST_Tipo))){
		Tipo();
		if(!match(ID)) errSynt(ID);
		Decl2();
		return;
	}
	errSynt("de Declaracao");;
}

void Decl2 (){
	if(match(COMMA)){
		if(!match(ID)) errSynt(ID);
		Decl2();
		return;
	}else if(match(PCOMMA)){
		return;
	}else if(match(ATTR)){
		Expressao();
		Decl2();
		return;
	}
	errSynt("de Decl2");
}

void Tipo (){
	if(match(INT)) {
		return;
	}else if(match(FLOAT)) {
		return;
	}

	errSynt("de Tipo");
}

void Comando (){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Bloco), 
	 fst_size(FIRST_Bloco))){
		Bloco();
		return;
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Atribuicao), 
	 fst_size(FIRST_Atribuicao))){
		Atribuicao();
		return;
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoSe), 
	 fst_size(FIRST_ComandoSe))){
		ComandoSe();
		return;
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoEnquanto), 
	 fst_size(FIRST_ComandoEnquanto))){
		ComandoEnquanto();
		return;
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoRead), 
	 fst_size(FIRST_ComandoRead))){
		ComandoRead();
		return;
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoPrint), 
	 fst_size(FIRST_ComandoPrint))){
		ComandoPrint();
		return;
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoFor), 
	 fst_size(FIRST_ComandoFor))){
		ComandoFor();
		return;
	}
	
	errSynt("de Comando");
}

void Bloco (){
	if(!match(LBRACE)) errSynt(LBRACE);
	Decl_Comando();
	if(!match(RBRACE)) errSynt(RBRACE);
}

void Atribuicao (){
	if(!match(ID)) errSynt(ID);
	if(!match(ATTR)) errSynt(ATTR);
	Expressao();
	if(!match(PCOMMA)) errSynt(PCOMMA);
}

void ComandoSe (){
	if(!match(IF)) errSynt(IF);
	if(!match(LBRACKET)) errSynt(LBRACKET);
	Expressao();
	if(!match(RBRACKET)) errSynt(RBRACKET);
	Comando();
	ComandoSenao();
}

void ComandoSenao (){
	if(match(ELSE)){
		Comando();
	}
}

void ComandoEnquanto (){
	if(!match(WHILE)) errSynt(WHILE);
	if(!match(LBRACKET)) errSynt(LBRACKET);
	Expressao();
	if(!match(RBRACKET)) errSynt(RBRACKET);
	Comando();
}

void ComandoRead (){
	if(!match(READ)) errSynt(READ);
	if(!match(ID)) errSynt(ID);
	if(!match(PCOMMA)) errSynt(PCOMMA);
}

void ComandoPrint (){
	if(!match(PRINT)) errSynt(PRINT);
	if(!match(LBRACKET)) errSynt(LBRACKET);
	Expressao();
	if(!match(RBRACKET)) errSynt(RBRACKET);
	if(!match(PCOMMA)) errSynt(PCOMMA);
}

void ComandoFor(){
	if(!match(FOR)) errSynt(FOR);
	if(!match(LBRACKET)) errSynt(LBRACKET);
	AtribuicaoFor();
	if(!match(PCOMMA)) errSynt(PCOMMA);
	Expressao();
	if(!match(PCOMMA)) errSynt(PCOMMA);
	AtribuicaoFor();
	if(!match(RBRACKET)) errSynt(RBRACKET);
	Comando();
}

void AtribuicaoFor(){
	if(!match(ID)) errSynt(ID);
	if(!match(ATTR)) errSynt(ATTR);
	Expressao();
}

void Expressao (){
	Conjuncao();
	ExpressaoOpc();
}

void ExpressaoOpc (){
	if(match(OR)){
		Conjuncao();
		ExpressaoOpc();
	}
}

void Conjuncao(){
	Igualdade();
	ConjuncaoOpc();
}

void ConjuncaoOpc (){
	if(match(AND)){
		Igualdade();
		ConjuncaoOpc();
	}
}

void Igualdade (){
	Relacao();
	IgualdadeOpc();
}

void IgualdadeOpc(){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_IgualdadeOpc),
	 fst_size(FIRST_IgualdadeOpc))){    
		OpIgual();
		Relacao();
		IgualdadeOpc();
	}
}

void OpIgual (){
	if(match(EQ)){
		return;
	}else if(match(NE)){
		return;
	}

	errSynt("de OpIgual");
}

void Relacao (){
	Adicao();
	RelacaoOpc();
}

void RelacaoOpc (){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_RelacaoOpc),
	 fst_size(FIRST_RelacaoOpc))){
		OpRel();
		Adicao();
		RelacaoOpc();
	}
}

void OpRel (){
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

void Adicao (){
	Termo();
	AdicaoOpc();
}

void AdicaoOpc (){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_AdicaoOpc),
	 fst_size(FIRST_AdicaoOpc))){
		OpAdicao();
		Adicao();
		RelacaoOpc();
	}
}

void OpAdicao (){
	if(match(PLUS)){
		return;
	}else if(match(MINUS)){
		return;
	}

	errSynt("de OpAdicao");
}

void Termo (){
	Fator();
	TermoOpc();
}

void TermoOpc (){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_TermoOpc),
	 fst_size(FIRST_TermoOpc))){
		OpMult();
		Fator();
		TermoOpc();
	}
}

void OpMult (){
	if(match(MULT)){
		return;
	}else if(match(DIV)){
		return;
	}

	errSynt("de OpMult");
}

void Fator (){
	if(match(ID)){
		return;
	}else if(match(INTEGER_CONST)){
		return;
	}else if(match(FLOAT_CONST)){
		return;
	}else if(match(LBRACKET)){
		Expressao();
		if(!match(RBRACKET)) errSynt(RBRACKET);
		return;
	}

	printf("%s\n", getInLex());
	errSynt("de Fator");
}