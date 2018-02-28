#include "IO.h"

int main(){
    char c = '\0';
    IO *io = new_IO();
    io->openFile(io, "./main.c");
    do{
        printf("%c",c);
        c = io->getNextChar(io);
    }while(c!=EOF);

    FILE* hash = fopen("./CalculoHash.txt","r");
    int soma = 0;
    while(!feof(hash)){
        char a = fgetc(hash);
        if(a == '\n' || a == EOF){ printf("%d\n",soma); soma=0-'\n';}
        soma += a;
    }
    return 0;
}