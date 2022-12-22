#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    Cor cor;
    int valor;
} No;

typedef struct arvore {
    struct no* raiz;
    struct no* nulo; 
} Arvore;

Arvore* criarArvoreRubroNegra();
void inserirNaArvoreRubroNegra(Arvore* arvore, int valor);
void destruirArvoreRubroNegra(Arvore* arvore);

#endif