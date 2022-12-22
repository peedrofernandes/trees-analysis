#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct no {
    int valor;
    struct no *esquerdo, *direito;
    short altura;
} No;

// -------------------- API --------------------

No *inserirNaAvl(No *raiz, int x);
void destruirAvl(No *raiz);

// -------------------- --- --------------------

#endif