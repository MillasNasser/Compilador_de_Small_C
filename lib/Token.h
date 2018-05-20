#ifndef __TOKEN_H
#define __TOKEN_H
	#include "HeaderPadrao.h"

	typedef struct {
		string nome;
		string lexema;
		unsigned long int linha;
	} Token;

	bool Token_equals(Token *elem1, Token *elem2);

	Token* new_Token(const string nome, char *lexema, unsigned long int linha);
#endif //__TOKEN_H