#ifndef __HEADER_H
#define __HEADER_H
    #include <stdio.h>
    #include <stdlib.h>

    #define build(dest, src) \
            memcpy(dest, src, sizeof(src))

    ///Tipo boolean definido
    typedef char bool;
    #define true 1
    #define false 0
    
    ///Tipo string definido
    typedef char* string;
#endif //__HEADER_H