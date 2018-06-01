#include "ASTNodes.h"

ASTNode new_ASTNode(){
    ASTNode new;
    new.nome = NULL;
    new.filhos = NULL;
    new.tipo = NULL;
    new.valor = 0;
    return new;
}