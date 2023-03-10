#include <stdlib.h>

typedef struct nodeb {
  int qtdKeys;
  int* keys;
  struct nodeb** children;
  struct nodeb* father;
} NodeB;

typedef struct btree {
  NodeB* root;
  int order;
} Btree;

// Insert a key into Btree function (API)
void insertBtree(Btree* btree, int key, int *qtd);

// This create a Btree (API)
Btree* createBtree(int order, int *qtd);

// This destroys the tree (API)
void destroyBtree(Btree* btree);
