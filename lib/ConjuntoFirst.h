#ifndef __CONJUNTO_FIRST_H_
#define __CONJUNTO_FIRST_H_
	#include "HeaderPadrao.h"

	/* Macros uteis */
	#define fst_size(NOME) (sizeof((char [][str_size]){NOME})\
							/str_size)

	#define fst_toMtrx(NOME) ((char[][str_size]){NOME})

	/* Definindo os FIRSTS */
	#define FIRST_Programa "INT"

	#define FIRST_Decl_Comando 	FIRST_Declaracao,\
								FIRST_Comando

	#define FIRST_Declaracao FIRST_Tipo

	#define FIRST_Decl2 	"COMMA",\
							"PCOMMA",\
							"ATTR"

	#define FIRST_Tipo 	"INT",\
						"FLOAT"

	#define FIRST_Comando 	FIRST_Bloco,\
							FIRST_Atribuicao,\
							FIRST_ComandoSe,\
							FIRST_ComandoEnquanto,\
							FIRST_ComandoRead,\
							FIRST_ComandoPrint,\
							FIRST_ComandoFor

	#define FIRST_Bloco	"LBRACE"

	#define FIRST_Atribuicao	"ID"

	#define FIRST_ComandoSe	"IF"
	
	#define FIRST_ComandoSenao	"ELSE"
	
	#define FIRST_ComandoEnquanto	"WHILE"
	
	#define FIRST_ComandoRead	"READ"
	
	#define FIRST_ComandoPrint	"PRINT"

	#define FIRST_ComandoFor "FOR"

	#define FIRST_AtribicaoFor "ID"
	
	#define FIRST_Expressao	FIRST_Conjuncao
	
	#define FIRST_ExpressaoOpc	"OR"
	
	#define FIRST_Conjuncao	FIRST_Igualdade
	
	#define FIRST_ConjuncaoOpc	"AND"
	
	#define FIRST_Igualdade	FIRST_Relacao
	
	#define FIRST_IgualdadeOpc	FIRST_OplIgual
	
	#define FIRST_OplIgual	"EQ", "NE"
	
	#define FIRST_Relacao	FIRST_Adicao
	
	#define FIRST_RelacaoOpc	FIRST_OpRel
	
	#define FIRST_OpRel	"LT",\
						"LE",\
						"GT",\
						"GE"
	
	#define FIRST_Adicao	FIRST_Termo
	
	#define FIRST_AdicaoOpc	FIRST_OpAdicao
	
	#define FIRST_OpAdicao	"PLUS",\
							"MINUS"
	
	#define FIRST_Termo	FIRST_Fator
	
	#define FIRST_TermoOpc	FIRST_OpMult
	
	#define FIRST_OpMult	"MULT",\
							"DIV"
	
	#define FIRST_Fator	"ID",\
						"INTEGER_CONST",\
						"FLOAT_CONST",\
						"LBRACKET"

	/* Metodos */
	/* Função que identifica um lexema no conjunto first 
		Ex: inFirst("INT", firstPass(FIRST_Programa));*/
	bool inFirst(string lex, char first[][str_size], unsigned int size);
#endif //__CONJUNTO_FIRST_H_