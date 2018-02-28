#ifndef __LISTA_h
#define __LISTA_h
#include "HeaderPadrao.h"

#define lista_size 1 //Numero inicial de elementos na lista

//Acessa o elemento atual
#define d_at(a, val) ((a) % val)

//Acessa o proximo elemento
#define d_add(a, val) ((a + 1) % val)

//Acessa o elemento anterior
#define d_rem(a, val) ((a - 1 < 0)? val-1: a-1)

/*Em relação a posição da lista*/
#define inicio 0
#define final -1

/*No que define uma estrutura genérica*/
typedef struct s_No{
    size_t size; //Tamanho em bytes do dado
    void *valor; //Dado armazenado

    /*Verifica se o valor de dois No's são iguais*/
    bool (*equals)(struct s_No self, struct s_No element);
}No;
#define No_NULL (No){0,NULL,NULL}//Definição de NULL para No

/* Descritor da LISTA*/
typedef struct s_Lista{
    const char* type;
    int __tam_max; //Armazena o tamanho maximo da lista
    int qnt; //Armazena a quantidade atual da lista
    int begin; //Aponta para o inicio da lista
    int end; //Aponta para o final da lista
    No *lista;
    
    /*Adiciona no seguinte index,
        0: inicio;
        -1: final;
        [0 .. tamanho]: valores entre 0 e o limite da lista
    
    ___ Valores que são adicionados em index diferentes 
        de 0, -1 ou tam alteram o inicio ou final da lista
        0: inicio; -1: final*/
    void (*add)(struct s_Lista* self, void* dado, 
                size_t size, int index);

    /*Remove no indice em relação ao inicio e final da 
    lista que é variavel
        0: inicio;
        -1: final; 
        [0 .. tamanho]: valores entre 0 e o limite da lista

    ___ Valores que são removidos em index diferentes 
        de 0, -1 ou tam alteram
        o inicio ou final da lista*/
    No (*pop)(struct s_Lista* self, int index);

    /*Busca um item na lista, o primeiro valor encontrado 
    é retornado o seu index*/
    int (*busca)(struct s_Lista* self, void *item, 
                 size_t size);

    /*Retorna o item no determinado index*/
    No* (*get)(struct s_Lista* self, int index);

    /*Verifica se há tal item na lista */
    bool (*existe)(struct s_Lista* self, void *item, 
                    size_t size);
}Lista;

/*Faz a inicialização da lista*/
Lista* new_lista();

/*Faz a inicialização do No*/
No new_no(size_t size, void* data);

/*Deleta todos os elementos e destroi a lista*/
void drop_lista(Lista* lista);
#endif //__LISTA_h