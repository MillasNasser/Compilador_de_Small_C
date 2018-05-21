#include "AnalisadorSintatico.h"

int main(int argc, char *argv[]){
    AnalisadorLexico *ss = new_AnalisadorLexico("utils/cod.c");
    ss->start(ss);
	
    Gramatica_init();
    printf("%d\n",Programa());
    del_AnalisadorLexico(ss);
    return 0;
}
/* Impressão do vetor de Lexemas
    int i;
	for(i = 0; i < tknVec->qnt; i++){ 
        No *saida = tknVec->get(tknVec,i); 
        printf("%s %s\n", ((Token*)saida->valor)->lexema, ((Token*)saida->valor)->nome); 
        printf("%5lu| %13s| %s\n", ((Token*)saida->valor)->linha, 
                 ((Token*)saida->valor)->lexema,  
                 ((Token*)saida->valor)->nome); 
		printf("-----+--------------+---------------\n"); 
    }
*/