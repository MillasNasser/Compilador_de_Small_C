#ifndef __TABELA_DE_SIMBOLOS_H_
#define __TABELA_DE_SIMBOLOS_H_
	#include "HeaderPadrao.h"
	#include "hashMap.h"

	typedef struct s_Entrada{
		unsigned long int linha;
		string lexema;
		string tipo;
		void *valor;
	}EntradaTabela;

	Map *TabelaDeSimbolos;

	void new_Tabela();

	EntradaTabela* new_EntradaTabela(	unsigned long int linha,
							string lexema,
							string tipo,
							void *valor);

	int add_Tabela(EntradaTabela*);

	void print_Tabela();
	
#endif //__TABELA_DE_SIMBOLO_H_