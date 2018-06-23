#include "AnalisadorSintatico.h"

int main(int argc, char *argv[]){
    strcpy(simbolTable,"symboltable.txt");
    strcpy(arvAbstr ,"abstractTree.txt");
    logErro = fopen("logErro.txt","w");
    if(logErro == NULL){
        perror("Erro ao executar a acao");
        exit(-2);
    }
    if(argc > 2){
        strcpy(simbolTable, argv[2]);
    }
    if(argc > 3){
        strcpy(arvAbstr, argv[3]);
    }

    AnalisadorSintatico *novo = new_AnalisadorSintatico();
    ASTNode *arvoreSintatica = novo->start(argv[1]);
    arvoreSintatica->del(arvoreSintatica);
    return 0;
}