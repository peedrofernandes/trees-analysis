#ifndef B_TREE_H
#define B_TREE_H

typedef struct noB {
    int total;
    int* chaves;
    struct noB** filhos;
    struct noB* pai; 
} NoB;

typedef struct arvoreb {
  NoB* raiz;
  int ordem;
} ArvoreB;

ArvoreB* criarArvoreB(int ordem, int* qtd);
void inserirNaArvoreB(ArvoreB* arvore, int valor, int* qtd);
void destruirArvoreB(ArvoreB* arvore);

#endif