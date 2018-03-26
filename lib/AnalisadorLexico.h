#ifndef __ANALISADOR_LEXICO_H
#define __ANALISADOR_LEXICO_H
	#include "HeaderPadrao.h"
	#include "IO.h"
	#include "lista.h"
	#include "Token.h"

    typedef struct s_AnalsdrLex{
        IO *io;
		Lista *wordList;
		Lista *tknVec;
		bool (*addWL)(struct s_AnalsdrLex *self, string lexema, 
												 string token);
		bool (*defaultWL)(struct s_AnalsdrLex *self);
		void (*start)(struct s_AnalsdrLex *self);
    } AnalisadorLexico;

	AnalisadorLexico* new_AnalisadorLexico(string path);

	void del_AnalisadorLexico(AnalisadorLexico*);
#endif //__ANALISADOR_LEXICO_H