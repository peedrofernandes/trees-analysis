#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "redblacktree-counter.h"

int vazia(ArvoreRN* arvore, int *qtd) {
  int q = 0;

  q += 2;
  *qtd += q;

  return arvore->raiz == NULL;
}

void destruirNo(NoRN* no) {
    if (no != NULL) {
      destruirNo(no->esquerda);
      destruirNo(no->direita);
      no = NULL;
      free(no);
    }
}

NoRN* criarNo(ArvoreRN* arvore, NoRN* pai, int valor, int *qtd) {
    int q = 0;

    NoRN* no = malloc(sizeof(NoRN));
    no->pai = pai;    
    no->valor = valor;
    no->direita = arvore->nulo;
    no->esquerda = arvore->nulo;

    q += 5;
    *qtd += q;

    return no;
}

NoRN* adicionarNo(ArvoreRN* arvore, NoRN* no, int valor, int *qtd) {
    int q = 0;

    q += 2;
    if (valor > no->valor) {
        q++;
        if (no->direita == arvore->nulo) {
            no->direita = criarNo(arvore, no, valor, qtd);
            no->direita->cor = Vermelho;

            q += 3;
            *qtd += q;

            return no->direita;
        } else {
            q++;
            *qtd += q;

            return adicionarNo(arvore, no->direita, valor, qtd);
        }
    } else if (valor < no->valor) {
        q++;    
        if (no->esquerda == arvore->nulo) {
            no->esquerda = criarNo(arvore, no, valor, qtd);
            no->esquerda->cor = Vermelho;

            q += 3;
            *qtd += q;

            return no->esquerda;
        } else {
            q++;
            *qtd += q;

            return adicionarNo(arvore, no->esquerda, valor, qtd);
        }
    }

    q++;
    *qtd += q;

    return NULL;
}

void rotacionarEsquerda(ArvoreRN* arvore, NoRN* no, int* qtd) {
    int q = 0;

    NoRN* direita = no->direita;
    no->direita = direita->esquerda;

    q++;
    if (direita->esquerda != arvore->nulo) {
        direita->esquerda->pai = no;
        q++;
    }

    direita->pai = no->pai;

    q += 2;
    if (no->pai == arvore->nulo) {
        arvore->raiz = direita;
        q++;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = direita;
        q++;
    } else {
        no->pai->direita = direita;
        q++;
    }

    direita->esquerda = no;
    no->pai = direita;

    q += 5;
    *qtd += q;
}

void rotacionarDireita(ArvoreRN* arvore, NoRN* no, int* qtd) {
    int q = 0;

    NoRN* esquerda = no->esquerda;
    no->esquerda = esquerda->direita;

    q++;
    if (esquerda->direita != arvore->nulo) {
        esquerda->direita->pai = no;
        q++;
    }

    esquerda->pai = no->pai;
    
    q += 2;
    if (no->pai == arvore->nulo) {
        arvore->raiz = esquerda;
        q++;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = esquerda;
        q++;
    } else {
        no->pai->direita = esquerda;
        q++;
    }
    
    esquerda->direita = no;
    no->pai = esquerda;

    q += 5;
    *qtd += q;
}

void balancearRn(ArvoreRN* arvore, NoRN* no, int* qtd) {
    int q = 0;

    q++;
    while (no->pai->cor == Vermelho) {
        q++;
        if (no->pai == no->pai->pai->esquerda) {
            NoRN *tio = no->pai->pai->direita;
            
            q++;
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
                q += 4;
            } else {
                q++;
                if (no == no->pai->direita) {
                    no = no->pai; //Caso 2
                    rotacionarEsquerda(arvore, no, qtd); //Caso 2
                    q += 2;
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarDireita(arvore, no->pai->pai, qtd); //Caso 3
                    q += 3;
                }
            }

            q++;
        } else {
            NoRN *tio = no->pai->pai->esquerda;
            
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                if (no == no->pai->esquerda) {
                    no = no->pai; //Caso 2
                    rotacionarDireita(arvore, no, qtd); //Caso 2
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarEsquerda(arvore, no->pai->pai, qtd); //Caso 3
                }
            }
        }
    }
    arvore->raiz->cor = Preto; //Conserta possível quebra regra 2

    q++;
    *qtd += q;
}

// -------------------- API --------------------

ArvoreRN* criarArvoreRubroNegra(int* qtd) {
    ArvoreRN *arvore = malloc(sizeof(ArvoreRN));
    arvore->nulo = NULL;
    arvore->raiz = NULL;
    arvore->nulo = criarNo(arvore, NULL, 0, qtd);
    arvore->nulo->cor = Preto;

    return arvore;
}

void inserirNaArvoreRubroNegra(ArvoreRN* arvore, int valor, int* qtd) {
    int q = 0;

    q++;
    if (vazia(arvore, qtd)) {
        arvore->raiz = criarNo(arvore, arvore->nulo, valor, qtd);
        arvore->raiz->cor = Preto;
        q += 2;
    } else {
        NoRN* no = adicionarNo(arvore, arvore->raiz, valor, qtd);

        q++;
        if (no != NULL) {
            balancearRn(arvore, no, qtd);
            q++;
        }
    }

    q++;
    *qtd += q;
}

void destruirArvoreRubroNegra(ArvoreRN* arvore) {
    destruirNo(arvore->raiz);
    free(arvore);
}

// -------------------- --- --------------------