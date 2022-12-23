#include <stdlib.h>
#include "btree.h"

// This find the index that the element should be inserted, given a sorted array
int findIndex(int* arr, int size, int key) {
  int index = 0;

  while (index < size) {
    if (key <= arr[index] || arr[index] == -1)
      break;
    index++;
  }

  return index;
}

// Insertion in an int array, given an index
void insertion(int* arr, int index, int size, int key) {
  if (index > size)
    return;

  for (int i = size - 2; i >= index; i--) {
    arr[i + 1] = arr[i];
  }
  arr[index] = key;
}

// This create a Btree (API)
Btree* createBtree(int order) {
  if (order <= 0)
    return NULL;

  Btree* btree = malloc(sizeof(Btree));
  btree->order = order;
  btree->root = NULL;
  return btree;
}

// This simply create a Btree node, with every element of it set to NULL.
NodeB* createBtreeNode(Btree* btree) {
  int max = btree->order * 2;

  NodeB* node = malloc(sizeof(NodeB));
  node->qtdKeys = 0;
  node->father = NULL;

  node->keys = malloc((max + 1) * sizeof(int));
  for (int i = 0; i < max + 1; i++) {
    node->keys[i] = -1;
  }

  node->children = malloc((max + 2) * sizeof(NodeB*));
  for (int i = 0; i < max + 2; i++) {
    node->children[i] = NULL;
  }

  return node;
}

// This will split the node into two, left and right.
void splitNodes(Btree *btree, NodeB **node, NodeB **left, NodeB **right) {
  NodeB *l = createBtreeNode(btree);
  NodeB *r = createBtreeNode(btree);

  NodeB* cur = *node;
  int order = btree->order;
  int max = order * 2;

  for (int i = 0; i < order; i++) {
    l->keys[i] = cur->keys[i];
    l->children[i] = cur->children[i];
  }
  l->children[order] = cur->children[order];
  r->children[0] = cur->children[order + 1];
  for (int i = order + 1; i <= max; i++) {
    r->keys[i - (order + 1)] = cur->keys[i];
    r->children[i - order] = cur->children[i + 1];
  }

  // If the node does not have a father, it is the root of the tree.
  // In this case, the tree needs a new root.
  if (cur->father == NULL) {
    cur->father = createBtreeNode(btree);
    btree->root = cur->father;
  }

  l->father = cur->father;
  r->father = cur->father;
  l->qtdKeys = order;
  r->qtdKeys = order;

  *left = l;
  *right = r;

  free(*node);
}

// Insertion into a Btree node. This insertion can be in a leaf (left 
// and right are both NULL) or from a promotion (recursive call)
void insertIntoBtreeNode(Btree *btree, NodeB *node, int key, NodeB **left, NodeB **right) {
  int order = btree->order;
  int max = order * 2;

  // Find index of keys array
  int index = findIndex(node->keys, max, key);
  insertion(node->keys, index, max + 1, key);
  node->qtdKeys++;

  // If left node or right node isn't null, the insertion came from a
  // previous promotion and the children needs to be shifted 
  if (left != NULL || right != NULL) {
    node->children[index] = *left;

    for (int i = max + 1; i >= index + 1; i--) {
      node->children[i + 1] = node->children[i];
    }
    node->children[index + 1] = *right;
  }

  // It needs a promotion, because the size of the keys array has passed
  // its maximum
  if (node->qtdKeys > max) {
    NodeB *newLeft, *newRight;
    int promotedKey = node->keys[order];
    splitNodes(btree, &node, &newLeft, &newRight);
    insertIntoBtreeNode(btree, newLeft->father, promotedKey, &newLeft, &newRight);
  }
}

// Insert a key into Btree function (API)
void insertBtree(Btree* btree, int key) {
  if (key <= 0) {
    return;
  }

  NodeB* node;

  // Case in which the tree is empty
  if (btree->root == NULL) {
    node = createBtreeNode(btree);
    node->keys[0] = key;
    node->qtdKeys++;
    btree->root = node;
    return;
  }

  node = btree->root;
  int max = btree->order * 2;

  // Here it will find the leaf and insert into it, passing NULL and NULL as
  // left and right, because it's not an insertion that came from a promotion
  while (1) {
    int index = findIndex(node->keys, max, key);
    if (node->children[index] == NULL) {
      insertIntoBtreeNode(btree, node, key, NULL, NULL);
      break;
    } else {
      node = node->children[index];
    }
  }
}
