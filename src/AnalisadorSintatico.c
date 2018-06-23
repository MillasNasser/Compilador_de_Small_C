#include "AnalisadorSintatico.h"

ASTNode* AnSint_start(string path){
    AnalisadorLexico *ss = new_AnalisadorLexico(path);
    ss->start(ss);

    Gramatica_init();
    ASTNode *arvoreSintatica = Programa();
    print_Tabela();

    del_AnalisadorLexico(ss);
    return arvoreSintatica;
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
