#ifndef REDBLACKTREE_COUNTER_H
#define REDBLACKTREE_COUNTER_H

enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct norn {
    struct norn* pai;
    struct norn* esquerda;
    struct norn* direita;
    Cor cor;
    int valor;
} NoRN;

typedef struct arvorern {
    NoRN* raiz;
    NoRN* nulo; 
} ArvoreRN;

ArvoreRN* criarArvoreRubroNegra(int* qtd);
void inserirNaArvoreRubroNegra(ArvoreRN* arvore, int valor, int* qtd);
void destruirArvoreRubroNegra(ArvoreRN* arvore);

#endif