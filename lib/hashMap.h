#ifndef __HASHMAP_H
#define __HASHMAP_H
    #include "HeaderPadrao.h"
    /*-----------------------------------------*/
    #include <string.h>

    #define hashDepth 5

    typedef struct s_MapNo{
        size_t size;
        char* chave;
        void* valor;
        /*Verifica se o valor de dois No's são iguais*/
        /*Necessita de uma função que verifica se os dados são 
        iguais*/
        bool (*equals)( struct s_MapNo self, struct s_MapNo element, 
                        int (*dataEquals)(void*,void*));
    }MapNo;
    #define MapNo_NULL (MapNo){0,NULL,NULL,NULL}

    typedef struct s_Map{
        int lenght;
        int depth;
        MapNo **__map;
        int (*hashFunc)(int value);
        int (*hashCalc)(struct s_Map *self, char *chave);
        void* (*get)(struct s_Map *self, char* chave);
        MapNo* (*pop)(struct s_Map* self, char *chave);
        bool (*add)(struct s_Map* self, char *chave, void* dado, size_t size);
    }Map;

    Map* new_Map(int size, int depth);

    MapNo new_MapNo(char *chave, void* valor, size_t size);

    void del_Map(Map *);

#endif //__HASHMAP_H