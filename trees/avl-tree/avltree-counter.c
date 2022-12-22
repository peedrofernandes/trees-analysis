#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "avltree-counter.h"

NoAVL* novoNo(int x, int* qtd){
    int q = 0;

    NoAVL *novo = malloc(sizeof(NoAVL));

    q++;
    if (novo) {
      novo->valor = x;
      novo->esquerdo = NULL;
      novo->direito = NULL;
      novo->altura = 0;
      q += 4;
    } else {
      printf("\nERRO ao alocar nó em novo No!\n");
      q++;
    }

    q++;
    *qtd += q;

    return novo;
}

short maior(short a, short b, int* qtd){
    int q = 0;

    q++;
    *qtd += q;

    return (a > b) ? a : b;
}

short alturaDoNo(NoAVL *no, int* qtd){
    int q = 0;

    q++;
    if (no == NULL) {
        q++;
        *qtd += q;
        return -1;
    } else {
        q++;
        *qtd += q;
        return no->altura;
    }

    q++;
    *qtd += q;
}

short fatorDeBalanceamento(NoAVL *no, int* qtd){
    int q = 0;

    q++;
    if (no) {
        q++;
        *qtd += q;
        return (alturaDoNo(no->esquerdo, qtd) - alturaDoNo(no->direito, qtd));
    } else {
        q++;
        *qtd += q;
        return 0;
    }

    *qtd += q;
}

NoAVL* rotacaoEsquerda(NoAVL *r, int* qtd){
    int q = 0;

    NoAVL *y, *f;

    y = r->direito;
    f = y->esquerdo;

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(alturaDoNo(r->esquerdo, qtd), alturaDoNo(r->direito, qtd), qtd) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo, qtd), alturaDoNo(y->direito, qtd), qtd) + 1;

    q += 8;
    *qtd += q;

    return y;
}

NoAVL* rotacaoDireita(NoAVL *r, int* qtd){
    int q = 0;

    NoAVL *y, *f;

    y = r->esquerdo;
    f = y->direito;

    y->direito = r;
    r->esquerdo = f;

    r->altura = maior(alturaDoNo(r->esquerdo, qtd), alturaDoNo(r->direito, qtd), qtd) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo, qtd), alturaDoNo(y->direito, qtd), qtd) + 1;

    q += 8;
    *qtd += q;

    return y;
}

NoAVL* rotacaoEsquerdaDireita(NoAVL *r, int* qtd){
    int q = 0;

    r->esquerdo = rotacaoEsquerda(r->esquerdo, qtd);

    q += 2;
    *qtd += q;

    return rotacaoDireita(r, qtd);
}

NoAVL* rotacaoDireitaEsquerda(NoAVL *r, int* qtd){
    int q = 0;

    r->direito = rotacaoDireita(r->direito, qtd);

    q += 2;
    *qtd += q;

    return rotacaoEsquerda(r, qtd);
}

NoAVL* balancear(NoAVL *raiz, int* qtd){
    int q = 0;

    short fb = fatorDeBalanceamento(raiz, qtd);

    // Rotação à esquerda
    q += 4;
    if (fb < -1 && fatorDeBalanceamento(raiz->direito, qtd) <= 0) {
        raiz = rotacaoEsquerda(raiz, qtd);
        q++;
    } else if (fb > 1 && fatorDeBalanceamento(raiz->esquerdo, qtd) >= 0) {
        raiz = rotacaoDireita(raiz, qtd);
        q++;
    } else if (fb > 1 && fatorDeBalanceamento(raiz->esquerdo, qtd) < 0) {
        raiz = rotacaoEsquerdaDireita(raiz, qtd);
        q++;
    } else if (fb < -1 && fatorDeBalanceamento(raiz->direito, qtd) > 0) {
        raiz = rotacaoDireitaEsquerda(raiz, qtd);
        q++;
    }

    q++;
    *qtd += q;

    return raiz;
}

// -------------------- API --------------------

NoAVL* inserirNaAvl(NoAVL *raiz, int x, int* qtd){
    int q = 0;

    q++;
    if (raiz == NULL) {
        return novoNo(x, qtd);
        q++;
    } else {
        q++;
        if (x < raiz->valor) {
          raiz->esquerdo = inserirNaAvl(raiz->esquerdo, x, qtd);
          q++;
        } 
        else

        q++;
        if (x > raiz->valor) {
          raiz->direito = inserirNaAvl(raiz->direito, x, qtd);
          q++;
        }
    }

    raiz->altura = maior(alturaDoNo(raiz->esquerdo, qtd), alturaDoNo(raiz->direito, qtd), qtd) + 1;
    raiz = balancear(raiz, qtd);

    q += 3;
    *qtd += q;

    return raiz;
}

void destruirAvl(NoAVL *raiz) {
    if (raiz != NULL) {
        destruirAvl(raiz->esquerdo);
        destruirAvl(raiz->direito);
        raiz = NULL;
        free(raiz);
    }
}

// -------------------- --- --------------------



    