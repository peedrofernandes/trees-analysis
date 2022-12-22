#include <stdio.h>
#include <stdlib.h>
#include "btree-counter.h"

NoB* criaNo(ArvoreB* arvore, int* qtd) {
  int q = 0;

  int max = arvore->ordem * 2;
  NoB* no = malloc(sizeof(NoB));

  no->pai = NULL;

  no->chaves = malloc(sizeof(int) * (max + 1));
  no->filhos = malloc(sizeof(NoB) * (max + 2));
  no->total = 0;

  q += 2;
  for (int i = 0; i < max + 2; i++) {
    no->filhos[i] = NULL;
    q += 3;
  }

  q += 6;
  *qtd += q;

  return no;
}

ArvoreB* criarArvoreB(int ordem, int* qtd) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = criaNo(a, qtd);

    return a;
}

int pesquisaBinaria(NoB* no, int chave, int* qtd) {
    int q = 0;

    int inicio = 0, fim = no->total - 1, meio;

    q++;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        q++;
        if (no->chaves[meio] == chave) {
          return meio;  // encontrou
          q++;
        } else if (no->chaves[meio] > chave) {
          fim = meio - 1;
          q += 2;
        } else {
          inicio = meio + 1;
          q++;
        }
        q++;
    }

    q += 2;
    *qtd += q;

    return inicio; //não encontrou	
}

int localizaChave(ArvoreB* arvore, int chave, int* qtd) {	
    NoB *no = arvore->raiz;
    
    while (no != NULL) {
        int i = pesquisaBinaria(no, chave, qtd);

        if (i < no->total && no->chaves[i] == chave) {
            return 1; //encontrou
        } else {
            no = no->filhos[i];
        }
    }

    return 0; //não encontrou	
}

NoB* localizaNo(ArvoreB* arvore, int chave, int* qtd) {
    int q = 0;

    NoB *no = arvore->raiz;

    q++;
    while (no != NULL) {
        int i = pesquisaBinaria(no, chave, qtd);

        q++;
        if (no->filhos[i] == NULL) {
            q++;
            return no;  // encontrou nó
        } else {
            no = no->filhos[i];
            q++;
        }
        q++;
    }

    q += 2;
    *qtd += q;

    return NULL; //não encontrou nenhum nó
}

void adicionaChaveNo(NoB* no, NoB* novo, int chave, int* qtd) {
    int q = 0;

    int i = pesquisaBinaria(no, chave, qtd);

    q += 2;
    for (int j = no->total - 1; j >= i; j--) {
        no->chaves[j + 1] = no->chaves[j];
        no->filhos[j + 2] = no->filhos[j + 1];
        q += 4;
    }

    no->chaves[i] = chave;
    no->filhos[i + 1] = novo;

    no->total++;

    q += 4;
    *qtd += q;
}

int transbordo(ArvoreB* arvore, NoB* no, int* qtd) {
    int q = 0;

    q += 2;
    *qtd += q;

    return no->total > arvore->ordem * 2;
}

NoB* divideNo(ArvoreB* arvore, NoB* no, int* qtd) {
    int q = 0;

    int meio = no->total / 2;
    NoB* novo = criaNo(arvore, qtd);
    novo->pai = no->pai;

    q += 2;
    for (int i = meio + 1; i < no->total; i++) {
        novo->filhos[novo->total] = no->filhos[i];
        novo->chaves[novo->total] = no->chaves[i];

        q++;
        if (novo->filhos[novo->total] != NULL) {
            novo->filhos[novo->total]->pai = novo;
            q++;
        }

        novo->total++;
        q += 5;
    }

    novo->filhos[novo->total] = no->filhos[no->total];

    q++;
    if (novo->filhos[novo->total] != NULL) {
        novo->filhos[novo->total]->pai = novo;
        q++;
    }
    no->total = meio;

    q += 5;
    *qtd += q;

    return novo;
}

void adicionaChaveRecursivo(ArvoreB* arvore, NoB* no, NoB* novo, int chave, int* qtd) {
    int q = 0;
    adicionaChaveNo(no, novo, chave, qtd);
    q++;
    if (transbordo(arvore, no, qtd)) {
        int promovido = no->chaves[arvore->ordem]; 
        NoB* novo = divideNo(arvore, no, qtd);

        q++;
        if (no->pai == NULL) {
            NoB* pai = criaNo(arvore, qtd);            
            pai->filhos[0] = no;
            adicionaChaveNo(pai, novo, promovido, qtd);
            
            no->pai = pai;
            novo->pai = pai;
            arvore->raiz = pai;
            q += 6;
        } else {
            adicionaChaveRecursivo(arvore, no->pai, novo, promovido, qtd);
            q++;
        }
        q += 2;
    }

    q++;
    *qtd += q;
}

void inserirNaArvoreB(ArvoreB* arvore, int chave, int* qtd) {
    int q = 0;

    NoB* no = localizaNo(arvore, chave, qtd);

    adicionaChaveRecursivo(arvore, no, NULL, chave, qtd);

    q += 2;
    *qtd += q;
}

void destruirNoB(ArvoreB* arvore, NoB* no) {
    if (no != NULL) {
        for (int i = 0; i < arvore->ordem * 2 + 1; i++) {
            destruirNoB(arvore, no->filhos[i]);
        }
        no = NULL;
        free(no);
    }
}

void destruirArvoreB(ArvoreB* arvore) {
    destruirNoB(arvore, arvore->raiz);
    arvore = NULL;
    free(arvore);
}

// int main() {
//     ArvoreB* arvore = criaArvore(1);

//     inserirNaArvoreB(arvore, 12);
//     inserirNaArvoreB(arvore, 3);
//     inserirNaArvoreB(arvore, 5);
//     inserirNaArvoreB(arvore, 7);
//     inserirNaArvoreB(arvore, 15);
//     inserirNaArvoreB(arvore, 99);
//     inserirNaArvoreB(arvore, 1);

// }