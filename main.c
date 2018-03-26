#include "AnalisadorLexico.h"

int main(){
    //printf("Saida\n");
    //IO *io = new_IO("./utils/cod.c");
    int i;
    AnalisadorLexico *ss = new_AnalisadorLexico("./utils/cod.c");
    ss->start(ss);
    
	printf("Linha|    Lexema    |Valor\n");
	printf("-----+--------------+---------------\n");
    for(i = 0; i < ss->tknVec->qnt; i++){
        No *saida = ss->tknVec->get(ss->tknVec,i);
        printf("%5lu| %13s| %s\n", ((Token*)saida->valor)->linha,
								 ((Token*)saida->valor)->lexema, 
								 ((Token*)saida->valor)->nome);
		printf("-----+--------------+---------------\n");
    }
    del_AnalisadorLexico(ss);
    return 0;
}
/*while(!feof(ss->io->sourceCode)){
        char saida = ss->io->getNextChar(ss->io);
        printf("%c",saida);
    }
*/