#ifndef __ANALISADOR_LEXICO_H
#define __ANALISADOR_LEXICO_H
	#include "HeaderPadrao.h"
	#include "IO.h"
	#include "lista.h"
	#include "Token.h"

	Lista *wordList;
	Lista *tknVec;

    typedef struct s_AnalsdrLex{
        IO *io;
		bool (*addWL)(string lexema, string token);
		bool (*defaultWL)();
		void (*start)(struct s_AnalsdrLex *self);
    } AnalisadorLexico;

	AnalisadorLexico* new_AnalisadorLexico(string path);

	void del_AnalisadorLexico(AnalisadorLexico*);
#endif //__ANALISADOR_LEXICO_H