#ifndef __GRAMATICA_H
#define __GRAMATICA_H
    #include "HeaderPadrao.h"
    #include "Token.h"

    bool match(Token*);

    /* Funções da Gramática*/
    void Programa ();
    void Decl_Comando ();
    void Declaracao ();
    void DecI2 ();
    void Tipo ();
    void Comando ();
    void Bloco ();
    void Atribuicao ();
    void ComandoSe ();
    void ComandoSenao ();
    void ComandoEnquanto ();
    void ComandoRead ();
    void ComandoPrint ();
    void Expressao ();
    void ExpressaoOpc ();
    void Conjuncao();
    void ConjuncaoOpc ();
    void Igualdade ();
    void IgualdadeOpc();
    void Oplgual ();
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

#endif //__GRAMATICA_H