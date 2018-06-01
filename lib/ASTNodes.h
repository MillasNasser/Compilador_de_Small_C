#ifndef __ASTNodes_H_
#define __ASTNodes_H_
    #include "HeaderPadrao.h"
    #include "lista.h"

    //Definindo o comando new
    #define new(NOME) new_ ## NOME;

    typedef struct s_ASTNode{
        string nome;
        Lista *filhos;
        string tipo;
        int valor;
    }ASTNode;

    ASTNode new_ASTNode();

    /* Novos nós Comando*/
    /* Novo Bloco */
    ASTNode new_Bloco(ASTNode expressao, ASTNode c_true, ASTNode c_false);

    /* Nova Atribuição */
    ASTNode new_Attr(ASTNode expressao, ASTNode c_true, ASTNode c_false);

    /* Novo If */
    ASTNode new_If(ASTNode expressao, ASTNode c_true, ASTNode c_false);

    /* Novo While */
    ASTNode new_While(ASTNode expressao, ASTNode c_true, ASTNode c_false);

    /* Novo For */
    ASTNode new_For(ASTNode expressao, ASTNode c_true, ASTNode c_false);

    /* Novo Print */
    ASTNode new_Print(ASTNode expressao, ASTNode c_true, ASTNode c_false);

    /* Novo Read */
    ASTNode new_Read(ASTNode expressao, ASTNode c_true, ASTNode c_false);

    /* Novos nós Expressão */
    /* Nova Expressão */
    ASTNode new_Expr();
#endif //__ASTNodes_H_