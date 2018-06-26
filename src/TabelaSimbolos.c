#include "TabelaSimbolos.h"
#define qntLexemas 10000
char lexemas[qntLexemas][30] = {0};
int cont;

void new_Tabela(){
	if(TabelaDeSimbolos != NULL){
		del_Map(TabelaDeSimbolos);
	}
	cont = 0;
	TabelaDeSimbolos = new_Map(10000,100);
}

EntradaTabela* new_EntradaTabela( unsigned long int linha, string lexema, 
								string tipo, float valor){
	EntradaTabela *new = malloc(sizeof(EntradaTabela));
	new->valor = valor;
	new->tipo = tipo;
	new->linha = linha;
	new->lexema = lexema;
	return new;
}

int add_Tabela(EntradaTabela *in){
	if(TabelaDeSimbolos->get(TabelaDeSimbolos,in->lexema) != NULL){
		fprintf(logErro, "Erro variavel já criada: redefinição de %s na linha %lu\n", in->lexema, in->linha);
		return 0;
	}

	strcpy(lexemas[cont], in->lexema);
	cont++;
	return TabelaDeSimbolos->add(TabelaDeSimbolos,in->lexema,in,sizeof(*in));
}

void print_Tabela(){
	int i;
	FILE *arq = fopen(simbolTable,"w");
	fprintf(arq,"-------Symbol Table------------\n");
	for(i = 0; i < cont; i++){
		EntradaTabela *aux = (EntradaTabela*)TabelaDeSimbolos->get(TabelaDeSimbolos,lexemas[i]);
		
		fprintf(arq,"%d:  token: ID, lexema: %s, tipo: %s, valor: %d, line number: %lu\n",
					i,
					aux->lexema,
					aux->tipo,
					((aux->valor == NAN)?0:0),
					aux->linha);
	}
	fprintf(arq,"---------------------------------\n");
	fclose(arq);
}

void print_Tabela_shell(){
	int i;
	FILE *arq = stdout;
	fprintf(arq,"-------Symbol Table------------\n");
	for(i = 0; i < cont; i++){
		EntradaTabela *aux = (EntradaTabela*)TabelaDeSimbolos->get(TabelaDeSimbolos,lexemas[i]);
		
		fprintf(arq,"%d:  token: ID, lexema: %s, tipo: %s, valor: %g, line number: %lu\n",
					i,
					aux->lexema,
					aux->tipo,
					((aux->valor == NAN)?0:aux->valor),
					aux->linha);
	}
	fprintf(arq,"---------------------------------\n");
	fclose(arq);
}