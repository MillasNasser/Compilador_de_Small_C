#include "AnalisadorLexico.h"

#define btwn(src,min,max) (src >= min && src <= max)

typedef struct s_Chave{
	string lexema;
	string token;
}Chave;

bool AnLex_addWL(AnalisadorLexico *this, string lexema, string token){
	Chave *newTkn = malloc(sizeof(Chave));
	newTkn->lexema = lexema;
	newTkn->token = token;

	this->wordList->add(this->wordList, newTkn, sizeof(newTkn), final);
	return true;
}

///Inutil por enquanto
//bool AnLex_remWL(AnalisadorLexico *this, string lexema, string token){}

bool AnLex_defaultWL(AnalisadorLexico *this){
	char lexema[500];
	char token[500];
	this->wordList = new_lista();
	FILE *def = fopen("./utils/WordList.txt","r");

	if(def == NULL) return false;
	while(!feof(def)){
		fscanf(def,"%s %s",lexema,token);
		//fscanf(def,"%s",token);
		AnLex_addWL(this,lexema,token);
	}
	return true;
}

void AnLex_start(struct s_AnalsdrLex *this){
	char aux = this->io->getNextChar(this->io);
	
	while(btwn(aux,'a','z') || btwn(aux,'A','Z')){
		printf("%c",aux);
		aux = this->io->getNextChar(this->io);
	}
	printf("\n");
}

/*-------------------------------------------------------*/
AnalisadorLexico* new_AnalisadorLexico(string path){
	AnalisadorLexico *new = malloc(sizeof(AnalisadorLexico));
	AnLex_defaultWL(new);
	new->tknVec = new_lista();
	new->io = new_IO(path);
	new->defaultWL = AnLex_defaultWL;
	//new->remWL = AnLex_remWL;
	new->start = AnLex_start;
	return new;
}

void del_AnalisadorLexico(AnalisadorLexico *this){
	del_IO(this->io);
	drop_lista(this->wordList);
	free(this);
}