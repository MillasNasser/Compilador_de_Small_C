#ifndef __ANALISADOR_SINTATICO_H_
#define __ANALISADOR_SINTATICO_H_
    #include "HeaderPadrao.h"
    #include "AnalisadorLexico.h"
    #include "Gramatica.h"

    typedef struct s_AnalsdrSint{
        void (*start)(string path);
    } AnalisadorSintatico;

	AnalisadorSintatico* new_AnalisadorSintatico();

	void del_AnalisadorSintatico(AnalisadorSintatico*);
    
#endif //__ANALISADOR_SINTATICO_H_