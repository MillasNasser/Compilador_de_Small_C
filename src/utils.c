#include "utils.h"
#include "Token.h"

string new_string(string src){
	int i;
	string copia = calloc(strlen(src)+1,sizeof(char));
	for(i = 0; src[i] != '\0'; i++){
		copia[i] = src[i];
	}
	return copia;
}

int Chave_equals(void *elem1,void *elem2){
	Chave *src1 = (Chave*)elem1;
	Chave *src2 = (Chave*)elem2;
	if(strcmp(src1->regex,src2->regex) == 0){
		return true;
	}
	return false;
}

int Chave_equalsFull(void *elem1,void *elem2){
	Chave *src1 = (Chave*)elem1;
	Chave *src2 = (Chave*)elem2;
	if( strcmp(src1->regex,src2->regex) == 0 && 
		strcmp(src1->token,src2->token) == 0){
		return true;
	}
	return false;
}