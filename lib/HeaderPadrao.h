#ifndef __HEADER_H
#define __HEADER_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>

    #define build(dest, src) \
            memcpy(dest, src, sizeof(*src))

    ///Tipo boolean definido
    typedef char bool;
    #define true 1
    #define false 0
    
    ///Tipo string definido
    typedef char* string;

    ///Inclusão da biblioteca de funções e estruturas úteis
    #include "utils.h"
#endif //__HEADER_H