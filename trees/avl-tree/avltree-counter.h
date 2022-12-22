#ifndef AVL_TREE_COUNTER_H
#define AVL_TREE_COUNTER_H

typedef struct noavl {
    int valor;
    struct noavl *esquerdo, *direito;
    short altura;
} NoAVL;

// -------------------- API --------------------

NoAVL *inserirNaAvl(NoAVL *raiz, int x, int* qtd);
void destruirAvl(NoAVL *raiz);

// -------------------- --- --------------------

#endif