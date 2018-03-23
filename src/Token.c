#include "Token.h"

Token* new_Token(const string nome, char *lexema, unsigned long int linha){
    Token *new = malloc(sizeof(Token));
    new->nome = nome;
    new->linha= linha;
    new->lexema = lexema;
    return new;
}