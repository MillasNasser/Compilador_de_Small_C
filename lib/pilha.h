#ifndef __PILHA_h
#define __PILHA_h
#include "HeaderPadrao.h"
#include "lista.h"

typedef struct s_pilha{
    Lista *super;
    void (*add)(struct s_pilha*, void *dado, size_t size);
    No (*pop)(struct s_pilha*);
}Pilha;

Pilha* new_pilha();

#endif //__PILHA_h