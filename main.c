#include "AnalisadorSintatico.h"

int main(int argc, char *argv[]){
    strcpy(simbolTable,"symboltable.txt");
    strcpy(arvAbstr ,"abstractTree.txt");

    logErro = fopen("logErro.txt","w");
    if(logErro == NULL){
        perror("Erro ao executar a acao:");
        exit(-2);
    }

    cod3Addr = fopen("cod3Addr.txt","w");
    if(cod3Addr == NULL){
        perror("Erro ao executar a acao:");
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
    
    Gerador *gen3Addr = new_Gerador3Enderecos();
    gen3Addr->start(cod3Addr, arvoreSintatica);

    Interpretador *interpretador = new_Interpretador();
    interpretador->start(stdout, arvoreSintatica);
    
    arvoreSintatica->del(arvoreSintatica);

    fclose(logErro);
    fclose(cod3Addr);
    return 0;
}