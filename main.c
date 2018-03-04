#include "AnalisadorLexico.h"

int main(){
    AnalisadorLexico *anlx = new_AnalisadorLexico("./utils/cod.c");
    anlx->start(anlx);
    return 0;
}