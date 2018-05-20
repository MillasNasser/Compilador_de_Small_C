#ifndef __ANALISADOR_SINTATICO_H_
#define __ANALISADOR_SINTATICO_H_
    #include "HeaderPadrao.h"
    #include "AnalisadorLexico.h"
    #include "ConjuntoFirst.h"

    /* Variaveis globais */
    unsigned int index_entrada = 0;

    int match(Token* token);
    
#endif //__ANALISADOR_SINTATICO_H_