#ifndef __UTILS_H
#define __UTILS_H
    #include "HeaderPadrao.h"

    typedef struct s_chave{
        string regex;
        string token;
    }Chave;

    int Chave_equals(void *elem1,void *elem2);
    
    int Chave_equalsFull(void *elem1,void *elem2);

    string new_string(string src);

#endif //__UTILS_H