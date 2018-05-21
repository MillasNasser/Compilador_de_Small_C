#ifndef __GRAMATICA_H
#define __GRAMATICA_H
    #include "HeaderPadrao.h"
    #include "Token.h"
    #include "lista.h"
    #include "ConjuntoFirst.h"

    extern Lista* tknVec;
    int index_entrada;
    bool match(string );

    /* Funções da Gramática*/
    bool Programa ();
    void Decl_Comando ();
    void Declaracao ();
    void Decl2 ();
    void Tipo ();
    void Comando ();
    void Bloco ();
    void Atribuicao ();
    void ComandoSe ();
    void ComandoSenao ();
    void ComandoEnquanto ();
    void ComandoRead ();
    void ComandoPrint ();
    void ComandoFor ();
    void AtribuicaoFor ();
    void Expressao ();
    void ExpressaoOpc ();
    void Conjuncao();
    void ConjuncaoOpc ();
    void Igualdade ();
    void IgualdadeOpc();
    void OpIgual ();
    void Relacao ();
    void RelacaoOpc ();
    void OpRel ();
    void Adicao ();
    void AdicaoOpc ();
    void OpAdicao ();
    void Termo ();
    void TermoOpc ();
    void OpMult ();
    void Fator ();

    void Gramatica_init();
#endif //__GRAMATICA_H