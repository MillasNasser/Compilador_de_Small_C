#ifndef __HEADER_H
#define __HEADER_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>
    #include <math.h>

    #define build(dest, src) memcpy(dest,src,sizeof(*src))
    ///Tipo boolean definido
    typedef char bool;
    #define true 1
    #define false 0
    
    ///Tipo string definido
    typedef char* string;
    #define str_size 30 //Tamanho padrão

    ///Nome padrao dos arquivos
    char simbolTable[200]; // = "symboltable.txt";
	char arvAbstr[200]; // = "abstractTree.txt";

    //Arquivos padrões
    FILE *logErro;
    FILE *cod3Addr;

    ///Inclusão da biblioteca de funções e estruturas úteis
    #include "utils.h"
#endif //__HEADER_H