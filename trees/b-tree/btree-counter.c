#include <stdlib.h>
#include "btree-counter.h"

void destroyBtreeNode(Btree* btree, NodeB *node) {
  if (node == NULL) {
    return;
  }

  for (int i = 0; i < btree->order * 2 + 2; i++) {
    destroyBtreeNode(btree, node->children[i]);
  }

  free(node->children);
  node->children = NULL;
  free(node->keys);
  node->keys = NULL;
  free(node);
  node = NULL;
}

void destroyBtree(Btree* btree) {
  destroyBtreeNode(btree, btree->root);
  free(btree);
}

// This find the index that the element should be inserted, given a sorted array
int findIndex(int* arr, int size, int key, int *qtd) {
  int index = 0;

  *qtd += 1;
  while (index < size) {
    if (key <= arr[index] || arr[index] == -1) {
      *qtd += 1;
      break;
    }
    index++;
    *qtd += 2;
  }

  *qtd += 2;
  return index;
}

// Insertion in an int array, given an index
void insertion(int* arr, int index, int size, int key, int *qtd) {
  *qtd += 1;
  if (index > size) {
    *qtd += 1;
    return;
  }

  *qtd += 2;
  for (int i = size - 2; i >= index; i--) {
    arr[i + 1] = arr[i];
    *qtd += 3;
  }
  arr[index] = key;

  *qtd += 1;
}

// This create a Btree (API)
Btree* createBtree(int order, int *qtd) {
  *qtd += 1;
  if (order <= 0) {
    *qtd += 1;
    return NULL;
  }

  Btree* btree = malloc(sizeof(Btree));
  btree->order = order;
  btree->root = NULL;

  *qtd += 4;
  return btree;
}

// This simply create a Btree node, with every element of it set to NULL.
NodeB* createBtreeNode(Btree* btree, int *qtd) {
  int max = btree->order * 2;

  NodeB* node = malloc(sizeof(NodeB));
  node->qtdKeys = 0;
  node->father = NULL;

  node->keys = malloc((max + 1) * sizeof(int));
  *qtd += 2;
  for (int i = 0; i < max + 1; i++) {
    node->keys[i] = -1;
    *qtd += 3;
  }

  node->children = malloc((max + 2) * sizeof(NodeB*));
  *qtd += 2;
  for (int i = 0; i < max + 2; i++) {
    node->children[i] = NULL;
    *qtd += 3;
  }

  *qtd += 7;
  return node;
}

// This will split the node into two, left and right.
void splitNodes(Btree *btree, NodeB **node, NodeB **left, NodeB **right, int *qtd) {
  NodeB *l = createBtreeNode(btree, qtd);
  NodeB *r = createBtreeNode(btree, qtd);

  int order = btree->order;
  int max = order * 2;

  *qtd += 2;
  for (int i = 0; i < order; i++) {
    l->keys[i] = (*node)->keys[i];
    if ((*node)->children[i] != NULL) {
      l->children[i] = (*node)->children[i];
      l->children[i]->father = l;
    }
    *qtd += 4;
  }
  if ((*node)->children[order] != NULL) {
    l->children[order] = (*node)->children[order];
    l->children[order]->father = l;
  }
  if ((*node)->children[order + 1] != NULL) {
    r->children[0] = (*node)->children[order + 1];
    r->children[0]->father = r;
  }
  *qtd += 2;
  for (int i = order + 1; i <= max; i++) {
    r->keys[i - (order + 1)] = (*node)->keys[i];
    if ((*node)->children[i + 1] != NULL) {
      r->children[i - order] = (*node)->children[i + 1];
      r->children[i - order]->father = r;
    }
    *qtd += 4;
  }

  // If the node does not have a father, it is the root of the tree.
  // In this case, the tree needs a new root.
  *qtd += 1;
  if ((*node)->father == NULL) {
    (*node)->father = createBtreeNode(btree, qtd);
    btree->root = (*node)->father;
    *qtd += 2;
  }

  l->father = (*node)->father;
  r->father = (*node)->father;
  l->qtdKeys = order;
  r->qtdKeys = order;

  *left = l;
  *right = r;

  free((*node));
  (*node) = NULL;
  free(*node);
  (*node) = NULL;

  *qtd += 14;
}

// Insertion into a Btree node. This insertion can be in a leaf (left 
// and right are both NULL) or from a promotion (recursive call)
void insertIntoBtreeNode(Btree *btree, NodeB *node, int key, NodeB **left, NodeB **right, int *qtd) {
  int order = btree->order;
  int max = order * 2;

  // Find index of keys array
  int index = findIndex(node->keys, max, key, qtd);
  insertion(node->keys, index, max + 1, key, qtd);
  node->qtdKeys++;

  // If left node or right node isn't null, the insertion came from a
  // previous promotion and the children needs to be shifted
  *qtd += 1;
  if (left != NULL || right != NULL) {
    node->children[index] = *left;

    *qtd += 2;
    for (int i = max + 1; i >= index + 1; i--) {
      node->children[i + 1] = node->children[i];
      *qtd += 3;
    }
    node->children[index + 1] = *right;
    *qtd += 2;
  }

  // It needs a promotion, because the size of the keys array has passed
  // its maximum
  *qtd += 1;
  if (node->qtdKeys > max) {
    NodeB *newLeft, *newRight;
    int promotedKey = node->keys[order];
    splitNodes(btree, &node, &newLeft, &newRight, qtd);
    insertIntoBtreeNode(btree, newLeft->father, promotedKey, &newLeft, &newRight, qtd);
    *qtd += 4;
  }

  *qtd += 5;
}

// Insert a key into Btree function (API)
void insertBtree(Btree* btree, int key, int *qtd) {
  *qtd += 1;
  if (key <= 0) {
    *qtd += 1;
    return;
  }

  NodeB* node;

  // Case in which the tree is empty
  *qtd += 1;
  if (btree->root == NULL) {
    node = createBtreeNode(btree, qtd);
    node->keys[0] = key;
    node->qtdKeys++;
    btree->root = node;
    *qtd += 5;
    return;
  }

  node = btree->root;
  int max = btree->order * 2;

  // Here it will find the leaf and insert into it, passing NULL and NULL as
  // left and right, because it's not an insertion that came from a promotion
  *qtd += 1;
  while (1) {
    int index = findIndex(node->keys, max, key, qtd);
    *qtd += 1;
    if (node->children[index] == NULL) {
      insertIntoBtreeNode(btree, node, key, NULL, NULL, qtd);
      *qtd += 1;
      break;
    } else {
      node = node->children[index];
      *qtd += 1;
    }
    *qtd += 2;
  }

  *qtd += 3;
}
