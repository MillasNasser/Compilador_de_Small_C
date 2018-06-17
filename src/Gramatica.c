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

bool add_TabelaDeSimbolos(ASTNode *arv,string tipo){
	/* Adicionando na tabela de simbolos */
	index_entrada--;
	Token *tokenEntrada = (Token*)tknVec->get(tknVec,index_entrada)->valor;

	int adicionou = add_Tabela(new_EntradaTabela(
		tokenEntrada->linha,
		tokenEntrada->nome,
		tipo,
		NULL
	));

	/*Idntf *id = new_Idntf(
		(Token*)tknVec->get(tknVec,index_entrada)->valor
	);

	addChild(arv, (ASTNode*)id);*/
	index_entrada++;

	return adicionou;
}

void Gramatica_init(){
	new_Tabela();
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
	ASTNode *arv = new_ASTNode("ASTNode","ASTNode");
	Decl_Comando(arv);
	if(!match(RBRACE)) errSynt(RBRACE);

	arv->print(stdout, arv);
	arv->del(arv);
	return true;
}

void Decl_Comando (ASTNode *arv){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Declaracao), 
	 fst_size(FIRST_Declaracao))){
		Declaracao(arv);
		Decl_Comando(arv);
	}else
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Comando), 
	 fst_size(FIRST_Comando))){
		ASTNode *aux = Comando();
		addChild(arv, aux);
		Decl_Comando(arv);
	}
}

void Declaracao (ASTNode *arv){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Tipo), 
	 fst_size(FIRST_Tipo))){
		string tipo = Tipo();
		if(!match(ID)) errSynt(ID);

		add_TabelaDeSimbolos(arv, tipo);

		Decl2(arv, tipo);
		return;
	}
	errSynt(fst_toMtrx(FIRST_Declaracao)[0]);
}

void Decl2 (ASTNode *arv, string tipo){
	if(match(COMMA)){
		if(!match(ID)) errSynt(ID);

		add_TabelaDeSimbolos(arv,tipo);
		
		Decl2(arv, tipo);
		return;
	}else if(match(PCOMMA)){
		return;
	}else if(match(ATTR)){
		Idntf *id = new_Idntf(
			(Token*)tknVec->get(tknVec,index_entrada-2)->valor
		);
		Expr *expr = Expressao();
		Attr *attr = new_Attr(id,expr);
		addChild(arv, (ASTNode*) attr);
		Decl2(arv, tipo);
		return;
	}
	errSynt(fst_toMtrx(FIRST_Decl2)[0]);
}

string Tipo (){
	if(match(INT)) {
		return INT;
	}else if(match(FLOAT)) {
		return FLOAT;
	}

	errSynt(fst_toMtrx(FIRST_Tipo)[0]);
}

ASTNode* Comando (){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Bloco), 
	 fst_size(FIRST_Bloco))){
		return Bloco();
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_Atribuicao), 
	 fst_size(FIRST_Atribuicao))){
		return Atribuicao();
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoSe), 
	 fst_size(FIRST_ComandoSe))){
		return ComandoSe();
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoEnquanto), 
	 fst_size(FIRST_ComandoEnquanto))){
		return ComandoEnquanto();
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoRead), 
	 fst_size(FIRST_ComandoRead))){
		return ComandoRead();
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoPrint), 
	 fst_size(FIRST_ComandoPrint))){
		return ComandoPrint();
	}else 
	if(inFirst(getInLex(),fst_toMtrx(FIRST_ComandoFor), 
	 fst_size(FIRST_ComandoFor))){
		return ComandoFor();
	}
	
	errSynt(fst_toMtrx(FIRST_Comando)[0]);
}

ASTNode* Bloco (){
	ASTBloco *bloco = new_ASTBloco();
	if(!match(LBRACE)) errSynt(LBRACE);
	Decl_Comando(bloco);
	if(!match(RBRACE)) errSynt(RBRACE);
	return bloco;
}

ASTNode* Atribuicao (){
	if(!match(ID)) errSynt(ID);
	Idntf *id = new_Idntf(
		(Token*)tknVec->get(tknVec,index_entrada-1)->valor
	);
	if(!match(ATTR)) errSynt(ATTR);
	Expr *expr = Expressao();
	if(!match(PCOMMA)) errSynt(PCOMMA);

	Attr *atrib = new_Attr(id,expr);
	return (ASTNode*)atrib;
}

ASTNode* ComandoSe (){
	if(!match(IF)) errSynt(IF);
	if(!match(LBRACKET)) errSynt(LBRACKET);
	Expr *expr = Expressao();
	if(!match(RBRACKET)) errSynt(RBRACKET);

	ASTNode *ifTrue = Comando();
	ASTNode *ifFalse = ComandoSenao();

	If *s_if = new_If(expr,ifTrue,ifFalse);
	return (ASTNode*)s_if;
}

ASTNode* ComandoSenao (){
	if(match(ELSE)){
		return Comando();
	}
	return NULL;
}

ASTNode* ComandoEnquanto (){
	if(!match(WHILE)) errSynt(WHILE);
	if(!match(LBRACKET)) errSynt(LBRACKET);
	Expr *expr = Expressao();
	if(!match(RBRACKET)) errSynt(RBRACKET);
	
	ASTBloco *ifTrue = Comando();

	While *s_while = new_While(expr,ifTrue);
	return (ASTNode*)s_while;
}

ASTNode* ComandoRead (){
	if(!match(READ)) errSynt(READ);
	if(!match(ID)) errSynt(ID);
	Idntf *id = new_Idntf(
		(Token*)tknVec->get(tknVec,index_entrada-1)->valor
	);
	if(!match(PCOMMA)) errSynt(PCOMMA);

	Read *read = new_Read(id);
	return (ASTNode*)read;
}

ASTNode* ComandoPrint (){
	if(!match(PRINT)) errSynt(PRINT);
	if(!match(LBRACKET)) errSynt(LBRACKET);
	Expr *expr = Expressao();
	if(!match(RBRACKET)) errSynt(RBRACKET);
	if(!match(PCOMMA)) errSynt(PCOMMA);
	Print *pr = new_Print(expr);
	return (ASTNode*)pr;
}

ASTNode* ComandoFor(){
	if(!match(FOR)) errSynt(FOR);
	if(!match(LBRACKET)) errSynt(LBRACKET);
	Attr *init = AtribuicaoFor();
	if(!match(PCOMMA)) errSynt(PCOMMA);
	Expr *expr = Expressao();
	if(!match(PCOMMA)) errSynt(PCOMMA);
	Attr *incrmnt = AtribuicaoFor();
	if(!match(RBRACKET)) errSynt(RBRACKET);
	ASTNode *ifTrue = NULL;
	ifTrue = Comando(ifTrue);
	
	For*s_for=new_For(init,expr,incrmnt,ifTrue);
	return (ASTNode*)s_for;
}

Attr* AtribuicaoFor(){
	if(!match(ID)) errSynt(ID);
	Idntf *id = new_Idntf(
		(Token*)tknVec->get(tknVec,index_entrada-1)->valor
	);
	if(!match(ATTR)) errSynt(ATTR);
	Expr *expr = Expressao();
	return new_Attr(id, expr);
}

Expr* Expressao (){
	Expr *op1 = Conjuncao();
	return ExpressaoOpc(op1);
}

Expr* ExpressaoOpc (Expr *op1){
	if(match(OR)){
		Expr *op2 = Conjuncao();
		op2 = ExpressaoOpc(op2);
		return (Expr *)new_LogicalOp("||", op1, op2);
	}
	return op1;
}

Expr* Conjuncao(){
	Expr *op1 = Igualdade();
	return ConjuncaoOpc(op1);
}

Expr* ConjuncaoOpc (Expr *op1){
	if(match(AND)){
		Expr *op2 = Igualdade();
		op2 = ConjuncaoOpc(op2);
		return (Expr *)new_LogicalOp("&&", op1, op2);
	}
	return op1;
}

Expr* Igualdade (){
	Expr *op1 = Relacao();
	return IgualdadeOpc(op1);
}

Expr* IgualdadeOpc(Expr *op1){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_IgualdadeOpc),
	 fst_size(FIRST_IgualdadeOpc))){    
		string op = OpIgual();
		Expr *op2 = Relacao();
		op2 = IgualdadeOpc(op2);
		return (Expr *)new_RelOp(op, op1, op2);
	}
	return op1;
}

string OpIgual (){
	if(match(EQ)){
		return "==";
	}else if(match(NE)){
		return "!=";
	}

	errSynt(fst_toMtrx(FIRST_OplIgual)[0]);
}

Expr* Relacao (){
	Expr *op1 = Adicao();
	return RelacaoOpc(op1);
}

Expr* RelacaoOpc (Expr *op1){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_RelacaoOpc),
	 fst_size(FIRST_RelacaoOpc))){
		string op = OpRel();
		Expr *op2 = Adicao();
		op2 = RelacaoOpc(op2);
		return (Expr *)new_RelOp(op, op1, op2);
	}
	return op1;
}

string OpRel (){
	if(match(LT)){
		return "<";
	}else if(match(LE)){
		return "<=";
	}else if(match(GT)){
		return ">";
	}else if(match(GE)){
		return ">=";
	}

	errSynt(fst_toMtrx(FIRST_OpRel)[0]);
}

Expr* Adicao (){
	Expr *op1 = Termo();
	return AdicaoOpc(op1);
}

Expr* AdicaoOpc (Expr *op1){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_AdicaoOpc),
	 fst_size(FIRST_AdicaoOpc))){
		string op = OpAdicao();
		Expr *op2 = Termo();
		op2 = AdicaoOpc(op2);
		return (Expr *)new_ArithOp(op, op1, op2);
	}
	return op1;
}

string OpAdicao (){
	if(match(PLUS)){
		return  "+";
	}else if(match(MINUS)){
		return  "-";
	}

	errSynt(fst_toMtrx(FIRST_OpAdicao)[0]);
}

Expr* Termo (){
	Expr *op1 = Fator();
	return TermoOpc(op1);
}

Expr* TermoOpc (Expr *op1){
	if(inFirst(getInLex(),fst_toMtrx(FIRST_TermoOpc),
	 fst_size(FIRST_TermoOpc))){
		string op = OpMult();
		Expr *op2 = Fator();
		op2 = TermoOpc(op2);

		return (Expr *)new_ArithOp(op, op1, op2);
	}
	return op1;
}

string OpMult (){
	if(match(MULT)){
		return "*";
	}else if(match(DIV)){
		return "/";
	}

	errSynt(fst_toMtrx(FIRST_OpMult)[0]);
}

Expr* Fator (){
	if(match(ID)){
		Idntf *id = new_Idntf(
			(Token*)tknVec->get(tknVec,index_entrada-1)->valor
		);
		return (Expr*)id;
	}else if(match(INTEGER_CONST)){
		Numero *num = new_Numero(
			(Token*)tknVec->get(tknVec,index_entrada-1)->valor,
			tINT
		);
		return (Expr*)num;
	}else if(match(FLOAT_CONST)){
		Numero *num = new_Numero(
			(Token*)tknVec->get(tknVec,index_entrada-1)->valor,
			tFLOAT
		);
		return (Expr*)num;
	}else if(match(LBRACKET)){
		Expr *expr = Expressao();
		if(!match(RBRACKET)) errSynt(RBRACKET);
		return expr;
	}

	printf("%s\n", getInLex());
	errSynt(fst_toMtrx(FIRST_Fator)[0]);
}