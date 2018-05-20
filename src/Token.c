#include "Token.h"

bool Token_equals(Token *elem1, Token *elem2){
    if(	strcmp(elem1->lexema, elem2->lexema) == 0 &&
        strcmp(elem1->nome, elem2->nome) == 0){
        return true;
    }
    return false;
}

Token* new_Token(const string nome, char *lexema, unsigned long int linha){
    Token *new = malloc(sizeof(Token));
    new->nome = nome;
    new->linha= linha;
    new->lexema = lexema;
    return new;
}