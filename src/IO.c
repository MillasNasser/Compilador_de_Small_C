#include "IO.h"

void io_openFile(IO *this, string path){
    FILE *source = fopen(path,"r");
    if(source == NULL){ 
        perror("Nao foi possivel abrir o \
        codigo-fonte no caminho especificado\n");
        exit(-1);
    }
    this->sourceCode = source;
}

bool io_closeFile(IO *this){
    if(fclose(this->sourceCode)){
        return true;
    }
    return false;
}

char io_getNextChar(IO *this){
    char a = fgetc(this->sourceCode);
    return a;
}

bool io_rewind(IO *this){
    if(this->sourceCode != NULL){
        rewind(this->sourceCode);
        return true;
    }
    perror("Arquivo de código fonte nulo!");
    exit(-1);
}

/** ------------- Construtores e Destrutores -----------**/
IO* new_IO(string path){
    IO *new = calloc(1,sizeof(IO));
    new->openFile = io_openFile;
    new->closeFile = io_closeFile;
    new->getNextChar = io_getNextChar;
    new->rewind = io_rewind;
    new->openFile(new,path);
    return new;
}

void del_IO(IO *io){
    fclose(io->sourceCode);
    free(io);
}

void fill_buffer(IO *io, buffer *buff){
    string bufferRetorno = NULL;
	if(io == NULL){
        perror("Entrada nao definida"); exit(-1);
    }else if(buff == NULL || *buff == NULL){
		perror("Buffer nao definido"); exit(-3);
	}
 
    fseek(io->sourceCode,0,SEEK_END);
    int sizeVec = ftell(io->sourceCode);
    rewind(io->sourceCode);
    
    bufferRetorno = (string)calloc(sizeVec, sizeof(char)+1);
    fread(bufferRetorno, sizeof(char), sizeVec, io->sourceCode);

    int i;
    for(i = strlen(bufferRetorno)-1; 
    bufferRetorno!=NULL && bufferRetorno[i] =='\n'; 
    i--);
    
    bufferRetorno[i+1] = '\0';
    *buff = bufferRetorno;
}