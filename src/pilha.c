#include "pilha.h"

void plh_add(Pilha *pilha, void *dado, size_t size){
    ((Lista*)pilha)->add(((Lista*)pilha),dado,size,final);
}

No plh_pop(Pilha *pilha){
    return ((Lista*)pilha)->pop(((Lista*)pilha),final);
}

Pilha* new_pilha(){
    Pilha *nova = malloc(sizeof(Pilha));
    build(nova, new_lista());
    nova->add = plh_add;
    nova->pop = plh_pop;
    ((Lista*)nova)->type = "Pilha";
    return nova;
}