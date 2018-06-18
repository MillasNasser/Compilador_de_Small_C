#include "AnalisadorLexico.h"

#define btwn(src,min,max) (min <= src && src <= max)
#define REG_MATCH 0

/* ------------------------- Métodos Privados ------------------------- */

int tknMenor(void *elem1, void *elem2){
	Token *tk1 = (Token*)elem1;
	Token *tk2 = (Token*)elem2;
	if(tk1->linha > tk2->linha){
		return 1;
	}
	return 0;
}

void define_linhas_dos_tokens(buffer leitura){
	int i;
	int numeroLinha = 1;
	int ocorreuErro = 0;
	for(i = 0; i < strlen(leitura);i++){
		if(leitura[i] == '\n'){
			numeroLinha++;
		}else if(leitura[i] != ' ' && leitura[i] != '\t' && leitura[i] != '\n'){
			printf("Erro lexico na linha %d: " 
					"caractere %c invalido!\n", numeroLinha, leitura[i]);
			ocorreuErro = 1;
		}
		leitura[i] = numeroLinha;
	}

	if(ocorreuErro){exit(-3);}

	for(i = 0; i < tknVec->qnt;i++){
		No* tknNo = tknVec->get(tknVec,i);
		Token *tokenAtual = (Token*)tknNo->valor;
		tokenAtual->linha = leitura[tokenAtual->linha];
	}
}

/* ------------------------- Métodos Públicos ------------------------- */
int AnLex_delWL(void *self){
	return 1;
}

bool AnLex_addWL(const string regex, const string token){
	if(regex[0] == EOF && strlen(regex) == 1);
	Chave *new = malloc(sizeof(Chave));
	new->regex = new_string(regex);
	new->token = new_string(token);
	wordList->add(wordList,new,sizeof(Chave),final);
	return true;
}

bool AnLex_defaultWL(){
	char reg_ex[500];
	char token[500];
	wordList = new_Lista();
	FILE *def = fopen("./utils/regexList.txt","r");

	if(def == NULL) return false;
	while(!feof(def)){
		fscanf(def,"%s %s",reg_ex,token);
		AnLex_addWL(reg_ex,token);
	}
	return true;
}

void AnLex_start(struct s_AnalsdrLex *this){
	int i, j;
	regex_t regex;
	regmatch_t match[1];
	buffer leitura = "";
	IO *io = this->io;
	fill_buffer(io, &leitura);
	
	for(i = 0; i < wordList->qnt; i++){
		string descrtr = leitura;
		Chave *analisarBkp= (Chave*)wordList->get(wordList,i)->valor;
		
		regcomp(&regex,analisarBkp->regex,REG_EXTENDED);
		while(regexec(&regex, descrtr,1,match,0) == REG_MATCH){
			int matchSize = match[0].rm_eo - match[0].rm_so;
			string word = calloc(matchSize, sizeof(char));
			memcpy(word,descrtr+match[0].rm_so,matchSize);
			Chave *analisar;
			
			int index;
			index = wordList->busca(wordList,&(Chave){word,NULL},sizeof(Chave),
																 Chave_equals);
			if(index != -1){
				analisar = (Chave*)wordList->get(wordList,index)->valor;
			}else{
				analisar = analisarBkp;
			}

			for(j = 0; j < matchSize; j++){
				descrtr[match[0].rm_so+j] = ' ';
			}
			Token *new = new_Token(word,analisar->token,
					  (descrtr+match[0].rm_so)-leitura);
			descrtr += match[0].rm_eo;
			tknVec->add_sort(tknVec,new,sizeof(Token),tknMenor);
		}
		regfree(&regex);
	}
	
	define_linhas_dos_tokens(leitura);
	free(leitura);
}

/* ####### Construtores e Destrutores #######*/
AnalisadorLexico* new_AnalisadorLexico(string path){
	AnalisadorLexico *new= malloc(sizeof(AnalisadorLexico));
	AnLex_defaultWL(new);
	tknVec = new_Lista();
	new->io = new_IO(path);
	new->defaultWL = AnLex_defaultWL;
	new->start = AnLex_start;
	return new;
}

void del_AnalisadorLexico(AnalisadorLexico *this){
	del_IO(this->io);
	del_Lista(wordList, AnLex_delWL);
	del_Lista(tknVec, del_Token);
	free(this);
}