#include "hashMap.h"
#include <regex.h>

int true_cmp(void* elem1, void* elem2){return true;}

bool strEquals(char *elem1, char *elem2){
	bool nilElem1= elem1 == NULL;
	bool nilElem2= elem2 == NULL;
	if(nilElem1 && nilElem2){
		return true;
	}else if((elem1!=NULL && nilElem2) || (elem2!=NULL && nilElem1)){
		return false;
	}
	return strcmp(elem1,elem2) == 0;
}

bool mapno_equals(MapNo this, MapNo elem, int (*dataEquals)(void*,void*)){
	if( this.size == elem.size && strEquals(this.chave,elem.chave)){
		if(dataEquals(this.valor,elem.valor)){
			return true;
		}else{
			return false;
		}
	}
	return false;
}

int map_hashFunc(int x){
	return (x*x*x+2*x+3);
}

int map_hashCalc(Map *this, char *string){
	int i,value;
	if(this->lenght == 0) return -1;
	for(i = 0, value=0;string[i]!='\0';i++){
		value += this->hashFunc(string[i]);
	}
	return value%this->lenght;
}

bool map_add(Map *this, char *chave, void* dado, size_t size){
	int i,position = map_hashCalc(this,chave);
	MapNo novo = new_MapNo(chave, dado, size);
	MapNo atual = this->__map[position][0];

	if(strEquals(atual.chave,novo.chave)){
		this->__map[position][0].valor = dado;
	}else{
		int adicionou = 0;
		for(i = 0; i < this->depth; i++){
			atual = this->__map[position][i];
			if(mapno_equals(atual,novo,true_cmp)){
				this->__map[position][i].valor = dado;
				adicionou = 1; break;
			}else if(mapno_equals(atual,MapNo_NULL,true_cmp)){
				this->__map[position][i] = novo;
				adicionou = 1; break;
			}
		}
		if(!adicionou) return 0;
	}
	return 1;
}

void* map_get(Map *this, char* chave){
	int i, posicao = map_hashCalc(this,chave);
	MapNo *vecMap = this->__map[posicao];
	for(i = 0; i < this->depth; i++){
		if(strEquals(chave,vecMap[i].chave)){
			return this->__map[posicao][i].valor;
		}
	}
	return NULL;
}

MapNo* map_pop(struct s_Map* this, char *string){
	return NULL;
}

/*--------------------------------------*/
Map* new_Map(int size, int depth){
	Map *new = malloc(sizeof(Map));
	new->add = map_add;
	new->pop = map_pop;
	new->get = map_get;
	new->hashCalc = map_hashCalc;
	new->hashFunc = map_hashFunc;
	new->lenght = size;
	new->depth = depth;
	int i;
	new->__map = malloc(sizeof(MapNo*)*size);
	for(i = 0; i < size; i++){
		new->__map[i] = (MapNo*)calloc(depth,sizeof(MapNo));
	}
	return new;
}

MapNo new_MapNo(char *chave, void *valor, size_t size){
	MapNo new = (MapNo){size, chave, valor, mapno_equals};
	new.equals = mapno_equals;
	return new;
}

void del_Map(Map *this){
	int i;
	for(i = 0; i < this->lenght; i++){
		free(this->__map[i]);
	}
	free(this->__map);
	free(this);
}