#include "AnalisadorLexico.h"

int main(){
    //printf("Saida\n");
    //IO *io = new_IO("./utils/cod.c");
    int i;
    AnalisadorLexico *ss = new_AnalisadorLexico("./utils/cod.c");
    ss->start(ss);
    
    for(i = 0; i < ss->tknVec->qnt; i++){
        No *saida = ss->tknVec->get(ss->tknVec,i);
        printf("%s %s\n", ((Token*)saida->valor)->lexema, ((Token*)saida->valor)->nome);
    }
    del_AnalisadorLexico(ss);
    return 0;
}
/*while(!feof(ss->io->sourceCode)){
        char saida = ss->io->getNextChar(ss->io);
        printf("%c",saida);
    }
*/