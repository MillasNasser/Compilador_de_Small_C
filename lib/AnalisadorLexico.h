#ifndef __ANALISADOR_LEXICO_H
#define __ANALISADOR_LEXICO_H
	#include "HeaderPadrao.h"
	#include "IO.h"
	#include "lista.h"

    typedef struct s_AnalsdrLex{
        IO *io;
		bool (*addWL)(string lexema, string token);
		bool (*remWL)(string lexema, string token);
		bool (*defaultWL)();
		void (*start)(struct s_AnalsdrLex *self);
    } AnalisadorLexico;

	Lista wordList;

#endif //__ANALISADOR_LEXICO_H