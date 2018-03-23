#ifndef __TOKEN_H
#define __TOKEN_H
	#include "HeaderPadrao.h"

	typedef struct {
		string nome;
		string lexema;
		unsigned long int linha;
	} Token;

	Token* new_Token(const string nome, char *lexema, unsigned long int linha);
#endif //__TOKEN_H