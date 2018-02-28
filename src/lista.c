#include "lista.h"

void lst_add(Lista* lista, void* dado, size_t size, int index){
	//Se a lista estiver cheia
	if(lista->qnt == lista->__tam_max){
		lista->begin = 0;
		lista->end = lista->__tam_max - 1;
		lista->lista = realloc( lista->lista, sizeof(Lista)*
								lista->__tam_max * 2 );		
		lista->__tam_max *= 2;
	}

	//Se for necessario inserir no final
	if(index == final || index == lista->qnt){
		lista->end = d_add(lista->end,lista->__tam_max);
		lista->lista[lista->end] = new_no(size, dado);
	}else 

	//Se for inserir no inicio
	if(index == inicio){
		lista->begin =d_rem(lista->begin, lista->__tam_max);
		lista->lista[lista->begin] = new_no(size, dado);
	}else 

	//Se for inserir em uma posição central
	/*Há a remoção do No na posição atual e é jogado para o
	  final da lista, e o novo é inserido em seu lugar*/
	if(index < lista->qnt && index > 0){
		lista->end = d_add(lista->end, lista->__tam_max);
		lista->lista[lista->end] = lista->lista[index];
		lista->lista[index] = new_no(size, dado);
	}
	lista->qnt++;
}

No lst_pop(Lista* lista, int index){
	if(lista->qnt == 0){
		return No_NULL;
	}
	lista->qnt--;
	//Se remover no final
	if(index == final || index == lista->qnt){
		No retorno = lista->lista[lista->end];
		lista->end = d_rem(lista->end, lista->__tam_max);
		return retorno;
	}else 
	
	//Se remover no inicio
	if(index == inicio){
		No retorno = lista->lista[lista->begin];
		lista->begin =d_add(lista->begin, lista->__tam_max);
		return retorno;
	}else 
	
	//Se remover no centro
	/*Há a remoção do No na posição atual e é jogado em seu
	  lugar o No do final da lista*/
	if(index < lista->qnt && index > 0){
		No retorno = lista->lista[d_at(index+lista->begin, lista->__tam_max)];
		lista->lista[d_at(index+lista->begin, lista->__tam_max)] = lista->lista[lista->end];
		lista->end = d_rem(lista->end, lista->__tam_max);
		return retorno;
	}
	lista->qnt++;
	return No_NULL;
}

bool lst_equals(No elem1, No elem2){
	if( elem1.size == elem2.size &&
		elem1.valor == elem2.valor){
		return true;
	}
	return false;
}

int lst_busca(Lista* lista, void *item, size_t size){
	int i;
	for(i = 0; i < lista->qnt; i++){
		if(lst_equals(*(lista->get(lista,i)), new_no(size,item))){
			return i;
		}
	}
	return -1;
}

No* lst_get(Lista* lista, int index){
	if(index >= lista->qnt)
		return NULL;

	return &lista->lista[
			d_at(lista->begin + index, lista->__tam_max)
		];
}

bool lst_existe(Lista* lista, void *item, size_t size){
	if(lst_busca(lista,item,size) >= 0)
		return true;
	return false;
}
/*---------------------------------------*/
void drop_lista(Lista* lista){
	free(lista->lista);
	free(lista);
}

/*Tamanho inicial da lista é sempre lista_size*/
Lista* new_lista(){
	Lista* nova = malloc(sizeof(Lista));
	nova->begin = nova->end = 0;
	nova->lista = calloc(lista_size,sizeof(No));
	nova->__tam_max = lista_size;
	/*------ Metodos -------*/
	nova->type = "Lista";
	nova->add = lst_add;
	nova->pop = lst_pop;
	nova->busca = lst_busca;
	nova->get = lst_get;
	nova->existe = lst_existe;
	return nova;
}

No new_no(size_t size, void* data){
	No novo = (No){size,data, lst_equals};
	return novo;
}