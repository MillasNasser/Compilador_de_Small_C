#include "lista.h"

void lst_add(Lista* lista, void* dado, size_t size, int index){
	if((lista->qnt == 0) ^ (lista->lista == NULL)){
		perror("Incosistencia na lista, qnt difere do inicio da lista\n");
		return;
	}

	/* Se for o primeiro elemento da lista */
	if( lista->qnt == 0 && /// A lista estiver vazia
		lista->lista == NULL && /// O primeiro elemento for nulo
		(index == inicio || index == final) /// E o índice for no inicio ou final	
	){
		lista->lista = lista->ultimo = new_No(dado,size);
		lista->qnt++;
		return;
	}

	/* Adição normal de um vértice*/
	/* Quando inserir no final da lista*/
	if(index == final){
		No *novo = new_No(dado, size);
		lista->ultimo = lista->ultimo->prox = novo;
		lista->qnt++;
		return;
	}else
	/* Quando inserir no início da lista */
	if(index == inicio){
		No *novo = new_No(dado, size);
		novo->prox = lista->lista;
		lista->lista = novo;
		lista->qnt++;
		return;
	}else 
	/* Quando inserir no meio da lista */
	if(index > 0 && index < lista->qnt){
		int i;
		No *element = lista->lista;

		/* Itera sobre os elementos até no anterior do index */
		for(i=0; //Pega o primeiro elemento e define i=0
			i < index-1; //Enquanto i não for o elemento anterior 
			i++, element = lista->lista->prox //Pega o próximo elemento da lista
		);

		/* Aqui já chegou no elemento anterior desejado */
		No *novo = new_No(dado, size);
		novo->prox = element->prox;
		element->prox = novo;
		lista->qnt++;
		return;
	}
	/* Quando não for um valor de índice válido */
	perror("Valor invalido de indice, favor inserir um valor correto\n");
}

No* lst_pop(Lista* lista, int index){
	if(index < final || index >= lista->qnt){
		perror("Valor invalido de indice\n");
		return 0;
	}
	lista->qnt--;

	int i;
	No *element = lista->lista;
	No *prox;

	if(index == final) {
		index = lista->qnt;}
	else
	if(index == inicio){
		prox = lista->lista;
		lista->lista = lista->lista->prox;
		prox->prox = NULL;
		return prox;
	}
	/* Itera sobre os elementos até no anterior do index */
	for(i=0; //Pega o primeiro elemento e define i=0
		i < index-1; //Enquanto i não for o elemento anterior 
		i++, element = lista->lista->prox //Pega o próximo elemento da lista
	);
	prox = element->prox; //Pega o próximo elemento do que vai ser retirado

	element->prox = prox->prox;
	

	return prox;
}

int no_equals(No* elem1, No* elem2, int (*dataEquals)(void*,void*)){
	if( elem1->size == elem2->size){
		return dataEquals(elem1->valor,elem2->valor);
	}
	return false;
}

int lst_busca(Lista* lista, void *item, size_t size, int (*dataEquals)(void*,void*)){
	No *chave = new_No(item,size);
	int i;
	No *element = lista->lista;
	/* Itera sobre os elementos até no anterior do index */
	for(i = 0, element = lista->lista; //Pega o primeiro elemento da lista
		element != NULL; //Enquanto i não for o elemento anterior 
		i++, element = element->prox //Pega o próximo elemento da lista
	){
		if(no_equals(chave, element,dataEquals)){
			/* Liberando a chave criada para comparação */
			if(chave->valor != element->valor){
				free(chave->valor);
			}
			free(chave);
			return i;
		}
	}

	return -1;
}

No* lst_get(Lista* lista, int index){
	if(index < final || index >= lista->qnt){
		return NULL;
	}
	if(index == final){ index = lista->qnt-1; }
	No *element;
	/* Itera sobre os elementos até no anterior do index */
	for(element = lista->lista; //Pega o primeiro elemento da lista
		index > 0; //Enquanto i não for o elemento anterior 
		index--, element = element->prox //Pega o próximo elemento da lista
	);

	return element;
}

bool lst_existe(Lista* lista, void *item, size_t size, int (*dataEquals)(void*,void*)){
	if(lst_busca(lista,item,size,dataEquals) != -1){
		return true;
	}
	return false;
}

void lprintf(Lista *lista){
	int i;
	No* elemnt = lista->lista;
	for(i = 0; i < lista->qnt; i++, elemnt = elemnt->prox){
		printf("[%d]<[%lu] [%d]>\n",
			i, elemnt->size, *(int*)elemnt->valor);
	}
}

/*---------------------------------------*/
void del_Lista(Lista* lista, int dataDel(void *)){
	/* Se não houver ninguém na lista */
	if(lista->lista == NULL){
		free(lista);
		return;
	}

	int i = 0;
	No *elemnt = lista->lista;
	No *next;
	for(i = 0; i < lista->qnt; i++, elemnt = next){
		next = elemnt->prox;
		if(!dataDel(elemnt->valor)) exit(-1);
		elemnt->prox = NULL;
		free(elemnt);
	}
	if(next == NULL){
		free(lista);
		return;
	}
	perror("Erro: Vetor inconsistente");
}

/*Tamanho inicial da lista é sempre lista_size*/
Lista* new_Lista(){
	Lista* nova = malloc(sizeof(Lista));
	nova->qnt = 0;
	nova->lista = nova->ultimo = NULL;
	/*------ Metodos -------*/
	nova->type = "Lista";
	nova->add = lst_add;
	nova->pop = lst_pop;
	nova->busca = lst_busca;
	nova->get = lst_get;
	nova->existe = lst_existe;
	return nova;
}

No* new_No(void* data, size_t size){
	No *novo = (No*)malloc(sizeof(No));
	novo->size = size;
	novo->valor = data;
	novo->equals = no_equals;
	novo->prox = NULL;
	return novo;
}