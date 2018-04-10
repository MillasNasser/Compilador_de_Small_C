#include "AnalisadorLexico.h"

int main(int argc, char *argv[]){
    int i;
    AnalisadorLexico *ss = new_AnalisadorLexico(argv[1]);
    ss->start(ss);
    
	printf("Linha|    Lexema    |Valor\n");
	printf("-----+--------------+---------------\n");
    for(i = 0; i < tknVec->qnt; i++){
        No *saida = tknVec->get(tknVec,i);
        printf("%5lu| %13s| %s\n", ((Token*)saida->valor)->linha,
								 ((Token*)saida->valor)->lexema, 
								 ((Token*)saida->valor)->nome);
		printf("-----+--------------+---------------\n");
    }
    del_AnalisadorLexico(ss);
    return 0;
}