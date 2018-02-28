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
IO* new_IO(){
    IO *new = calloc(1,sizeof(IO));
    new->openFile = io_openFile;
    new->closeFile = io_closeFile;
    new->getNextChar = io_getNextChar;
    new->rewind = io_rewind;
    return new;
}

void del_IO(IO *io){
    free(io);
}