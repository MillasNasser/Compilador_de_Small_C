#ifndef __LISTA_h
#define __LISTA_h
    #include "HeaderPadrao.h"
//----------------------------------------------------------

/*Em relação a posição da lista*/
#define inicio 0
#define final -1

/*No que define uma estrutura genérica*/
typedef struct s_No{
    size_t size; //Tamanho em bytes do dado
    void *valor; //Dado armazenado
    struct s_No *prox; //Ponteiro para o próximo elemento

    /*Verifica se o valor de dois No's são iguais*/
    /*Necessita de uma função que verifica se os dados são 
      iguais*/
    int (*equals)( struct s_No* self, struct s_No* element, 
                    int (*dataEquals)(void*,void*));
}No;

/* Descritor da LISTA*/
typedef struct s_Lista{
    const char* type;
    int qnt; //Armazena a quantidade atual da lista
    No *lista; //Aponta para o primeiro elemento da lista
    No *ultimo;
    
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
    No* (*pop)(struct s_Lista* self, int index);

    /*Busca um item na lista, o primeiro valor encontrado 
    é retornado o seu index
    Necessário passar uma função que compara os dados
    */
    int (*busca)(struct s_Lista* self, void *item, 
                 size_t size, int (*dtEqls)(void*,void*));

    /*Retorna o item no determinado index*/
    No* (*get)(struct s_Lista* self, int index);

    /*Verifica se há tal item na lista */
    bool (*existe)(struct s_Lista* self, void *item, 
                    size_t size,int (*dtEqls)(void*,void*));
}Lista;

/*Faz a inicialização da lista*/
Lista* new_Lista();

void lprintf(Lista *lista);

/*Faz a inicialização do No*/
No* new_No(void* data, size_t size);

/*Deleta todos os elementos e destroi a lista*/
void del_Lista(Lista* lista, int dataDel(void *));
#endif //__LISTA_h