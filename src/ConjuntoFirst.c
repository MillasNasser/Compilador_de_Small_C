#include "ConjuntoFirst.h"

bool inFirst(string lex, char first[][str_size], unsigned int size){
    unsigned int i;
    for(i = 0; i < size; i++){
        if(strcmp(lex, first[i]) == 0){
            return true;
        }
    }
    return false;
}