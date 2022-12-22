#include <stdlib.h>
#include "btree.h"


int encontrarIndice(int* arr, int size, int valor) {
  int i = 0;
  while (arr[i] != -1 && valor > arr[i] && i < size)
    i++;
  return i;
}

No* criarNo(ArvoreB* arvore) {
  No* no = malloc(sizeof(No));

  int max = arvore->ordem * 2;
  no->chaves = malloc((max + 1) * sizeof(int));
  no->filhos = malloc((max + 2) * sizeof(No*));
  no->qtdChaves = 0;

  for (int i = 0; i < max + 1; i++) {
    no->chaves[i] = -1;
  }

  for (int i = 0; i < max + 2; i++) {
    no->filhos[i] = NULL;
  }

  return no;
}

void destruirNo(ArvoreB* arvore, No* no) {
  if (no != NULL) {
    int max = arvore->ordem * 2;
    for (int i = 0; i < max + 2; i++) {
      destruirNo(arvore, no->filhos[i]);
    }
    free(no);
  }
}

void inserirNoVetor(ArvoreB* arvore, No* no, int valor, No* esq, No* dir) {
  int max = 2 * arvore->ordem;

  // Inserir no vetor
  int i = encontrarIndice(no->chaves, max + 1, valor);
  for (int j = max - 1; j >= i; j--) {
    no->chaves[j + 1] = no->chaves[j];
  }
  no->chaves[i] = valor;
  no->qtdChaves++;

  // Atualizar o vetor de filhos
  if (esq != NULL || dir != NULL) {
    no->filhos[i] = esq;
    for (int j = max + 1; j >= i + 1; j--) {
      no->filhos[j + 1] = no->filhos[j];
    }
    no->filhos[i + 1] = dir;
  }

  // Quebrar o vetor, se ultrapassar a quantidade máxima
  if (no->qtdChaves > max) {
    int mid = max / 2;
    No* esquerda = criarNo(arvore);
    No* direita = criarNo(arvore);
    for (int c = 0; c < max + 1; c++) {
      if (c < mid) {
        esquerda->chaves[c] = no->chaves[c];
        esquerda->filhos[c] = no->filhos[c];
      } else if (c == mid) {
        esquerda->filhos[c] = no->filhos[c];
        direita->filhos[c - mid] = no->filhos[c + 1];
      } else {
        direita->chaves[c - mid - 1] = no->chaves[c];
        direita->filhos[c - mid] = no->filhos[c + 1];
      }
    }
    esquerda->qtdChaves = mid;
    direita->qtdChaves = mid;

    No* pai = no->pai;
    if (pai == NULL) {
      pai = criarNo(arvore);
      arvore->raiz = pai;
    }
    esquerda->pai = pai;
    direita->pai = pai;
    int midElem = no->chaves[mid];
    free(no);
    inserirNoVetor(arvore, pai, midElem, esquerda, direita);
  }
}

// -------------------- API --------------------

ArvoreB* criarArvoreB(int ordem) {
  ArvoreB* arvore = malloc(sizeof(ArvoreB));
  
  arvore->ordem = ordem;
  arvore->raiz = NULL;

  return arvore;
}

void inserirNaArvoreB(ArvoreB* arvore, int valor) {
  if (arvore->raiz == NULL) {
    No* raiz = criarNo(arvore);
    raiz->chaves[0] = valor;
    raiz->qtdChaves++;
    arvore->raiz = raiz;
  } else {
    No* no = arvore->raiz;
    int max = 2 * arvore->ordem;
    while (1) {
      if (no->filhos[0] != NULL) {
        int i = encontrarIndice(no->chaves, max, valor);
        no = no->filhos[i];
      } else {
        inserirNoVetor(arvore, no, valor, NULL, NULL);
        break;
      }
    }
  }
}

void destruirArvoreB(ArvoreB* arvore) {
  destruirNo(arvore, arvore->raiz);
  free(arvore);
}

// -------------------- --- --------------------