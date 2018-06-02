#include "AnalisadorSintatico.h"

int main(int argc, char *argv[]){
    printf("%s\n", argv[1]);
    AnalisadorSintatico *novo = new_AnalisadorSintatico();
    novo->start(argv[1]);
    return 0;
}