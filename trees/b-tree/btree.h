#ifndef B_TREE_H
#define B_TREE_H

typedef struct no {
  struct no* pai;
  int* chaves;
  struct no** filhos;
  int qtdChaves;
} No;

typedef struct arvoreb {
  No* raiz;
  int ordem;
} ArvoreB;

ArvoreB* criarArvoreB(int ordem);
void inserirNaArvoreB(ArvoreB* arvore, int valor);
void destruirArvoreB(ArvoreB* arvore);

#endif