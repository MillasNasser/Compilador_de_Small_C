#ifndef __TOKEN_H
#define __TOKEN_H
	#include "HeaderPadrao.h"
	
	typedef struct {
		const int nome;
		string lexema;
		unsigned long int linha;
	} Token;
#endif //__TOKEN_H