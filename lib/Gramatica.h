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
    void Decl_Comando (int nivel);
    void Declaracao (int nivel);
    void Decl2 (int nivel);
    void Tipo (int nivel);
    void Comando (int nivel);
    void Bloco (int nivel);
    void Atribuicao (int nivel);
    void ComandoSe (int nivel);
    void ComandoSenao (int nivel);
    void ComandoEnquanto (int nivel);
    void ComandoRead (int nivel);
    void ComandoPrint (int nivel);
    void ComandoFor (int nivel);
    void AtribuicaoFor (int nivel);
    void Expressao (int nivel);
    void ExpressaoOpc (int nivel);
    void Conjuncao(int nivel);
    void ConjuncaoOpc (int nivel);
    void Igualdade (int nivel);
    void IgualdadeOpc(int nivel);
    void OpIgual (int nivel);
    void Relacao (int nivel);
    void RelacaoOpc (int nivel);
    void OpRel (int nivel);
    void Adicao (int nivel);
    void AdicaoOpc (int nivel);
    void OpAdicao (int nivel);
    void Termo (int nivel);
    void TermoOpc (int nivel);
    void OpMult (int nivel);
    void Fator (int nivel);

    void Gramatica_init();
#endif //__GRAMATICA_H