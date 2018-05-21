#include "AnalisadorSintatico.h"

int main(int argc, char *argv[]){
    AnalisadorLexico *ss = new_AnalisadorLexico(argv[1]);
    ss->start(ss);

    Gramatica_init();
    printf("%d\n",Programa());
    del_AnalisadorLexico(ss);
    return 0;
}