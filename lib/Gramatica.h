#ifndef __GRAMATICA_H
#define __GRAMATICA_H
    #include "HeaderPadrao.h"
    #include "Token.h"
    #include "lista.h"
    #include "ConjuntoFirst.h"
    #include "TabelaSimbolos.h"
    #include "ASTNodes.h"

    extern Lista* tknVec;
    int index_entrada;
    bool match(string );

    /* Funções da Gramática*/
    ASTNode* Programa ();
    void Decl_Comando ();
    void Declaracao ();
    void Decl2 ();
    string Tipo ();
    ASTNode* Comando ();
    ASTNode* Bloco ();
    ASTNode* Atribuicao ();
    ASTNode* ComandoSe ();
    ASTNode* ComandoSenao ();
    ASTNode* ComandoEnquanto ();
    ASTNode* ComandoRead ();
    ASTNode* ComandoPrint ();
    ASTNode* ComandoFor ();
    Attr* AtribuicaoFor ();
    Expr* Expressao ();
    Expr* ExpressaoOpc ();
    Expr* Conjuncao();
    Expr* ConjuncaoOpc ();
    Expr* Igualdade ();
    Expr* IgualdadeOpc();
    string OpIgual ();
    Expr* Relacao ();
    Expr* RelacaoOpc ();
    string OpRel ();
    Expr* Adicao ();
    Expr* AdicaoOpc ();
    string OpAdicao ();
    Expr* Termo ();
    Expr* TermoOpc ();
    string OpMult ();
    Expr* Fator ();

    void Gramatica_init();
#endif //__GRAMATICA_H