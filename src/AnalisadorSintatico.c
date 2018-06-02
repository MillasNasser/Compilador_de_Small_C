#include "AnalisadorSintatico.h"

void AnSint_start(string path){
    AnalisadorLexico *ss = new_AnalisadorLexico(path);
    ss->start(ss);

    Gramatica_init();
    Programa();
    print_Tabela(path);

    del_AnalisadorLexico(ss);
}

/* ####### Construtores e Destrutores #######*/
AnalisadorSintatico* new_AnalisadorSintatico(){
    AnalisadorSintatico *new = malloc(sizeof(AnalisadorSintatico));
    new->start = AnSint_start;
    return new;
}

void del_AnalisadorSintatico(AnalisadorSintatico* this){
    free(this);
}
