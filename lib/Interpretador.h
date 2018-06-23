#ifndef __INTERPRETADOR_
#define __INTERPRETADOR_

    #include "HeaderPadrao.h"
    #include "ASTNodes.h"

    typedef struct s_Interpretador{
        void (*start)(FILE *arq, ASTNode *arvoreSintatica);
    }Interpretador;

/* Funções do interpretador */
    float Intpr_ASTNode(FILE *arq, ASTNode *self);
    float Intpr_ASTBloco(FILE *arq, ASTNode *self);
    float Intpr_Expr(FILE *arq, ASTNode *self);
    float Intpr_Idntf(FILE *arq, ASTNode *self);
    float Intpr_Numero(FILE *arq, ASTNode *self);
    float Intpr_LogicalOp(FILE *arq, ASTNode *self);
    float Intpr_RelOp(FILE *arq, ASTNode *self);
    float Intpr_ArithOp(FILE *arq, ASTNode *self);
    float Intpr_Attr(FILE *arq, ASTNode *self);
    float Intpr_If(FILE *arq, ASTNode *self);
    float Intpr_While(FILE *arq, ASTNode *self);
    float Intpr_For(FILE *arq, ASTNode *self);
    float Intpr_Read(FILE *arq, ASTNode *self);
    float Intpr_Print(FILE *arq, ASTNode *self);

/* Contrutores e destrutores */
    Interpretador* new_Interpretador();

    void del_Interpretador(Interpretador *self);

#endif // __INTERPRETADOR_
