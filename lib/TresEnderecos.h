#ifndef __GERADOR_3_ENDR_
#define __GERADOR_3_ENDR_

    #include "HeaderPadrao.h"
    #include "ASTNodes.h"

    typedef struct s_Gerador{
        void (*start)(FILE *arq, ASTNode *arvoreSintatica);
    }Gerador;

/* Funções do gerador 3 endereços */
    string Gen_ASTNode(FILE *arq, ASTNode *self);
    string Gen_ASTBloco(FILE *arq, ASTNode *self);
    string Gen_Expr(FILE *arq, ASTNode *self);
    string Gen_Idntf(FILE *arq, ASTNode *self);
    string Gen_Numero(FILE *arq, ASTNode *self);
    string Gen_LogicalOp(FILE *arq, ASTNode *self);
    string Gen_RelOp(FILE *arq, ASTNode *self);
    string Gen_ArithOp(FILE *arq, ASTNode *self);
    string Gen_Attr(FILE *arq, ASTNode *self);
    string Gen_If(FILE *arq, ASTNode *self);
    string Gen_While(FILE *arq, ASTNode *self);
    string Gen_For(FILE *arq, ASTNode *self);
    string Gen_Read(FILE *arq, ASTNode *self);
    string Gen_Print(FILE *arq, ASTNode *self);

/* Contrutores e destrutores */
    Gerador* new_Gerador3Enderecos();

    void del_Gerador3Enderecos(Gerador *self);

#endif // __GERADOR_3_ENDR_
