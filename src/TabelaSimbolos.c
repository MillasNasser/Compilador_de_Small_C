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
								string tipo, void*valor){
	EntradaTabela *new = malloc(sizeof(EntradaTabela));
	new->valor = valor;
	new->tipo = tipo;
	new->linha = linha;
	new->lexema = lexema;
	return new;
}

int add_Tabela(EntradaTabela *in){
	if(TabelaDeSimbolos->get(TabelaDeSimbolos,in->lexema) != NULL){
		printf("Variavel já criada: redefinição de %s na linha %lu\n", in->lexema, in->linha);
		return 0;
	}

	strcpy(lexemas[cont], in->lexema);
	cont++;
	return TabelaDeSimbolos->add(TabelaDeSimbolos,in->lexema,in,sizeof(*in));
}

void print_Tabela(){
	int i;
	char linha[] = "---------------";
	printf("+%1$s+%1$s+%1$s+%1$s+\n", linha);
	printf("|%2$*1$s|%3$*1$s|%4$*1$s|%5$*1$s|\n",
			15,"Linha","Tipo","Lexema","Valor");
	printf("+%1$s+%1$s+%1$s+%1$s+\n", linha);
	for(i = 0; i < cont; i++){
		EntradaTabela *aux = (EntradaTabela*)TabelaDeSimbolos->get(TabelaDeSimbolos,lexemas[i]);
		
		printf("|%2$*1$lu|%3$*1$s|%4$*1$s|%5$*1$p|\n", 
				15, aux->linha, aux->tipo, aux->lexema, aux->valor);
	}
	printf("+%1$s+%1$s+%1$s+%1$s+\n", linha);
}