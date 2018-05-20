#include "AnalisadorSintatico.h"

int match(Token* token){
    Token *tokenEntrada = (Token*)tknVec->get(tknVec,index_entrada)->valor;
    if(Token_equals(tokenEntrada,token)){
        index_entrada++;
        return true;
    }
    return false;
}