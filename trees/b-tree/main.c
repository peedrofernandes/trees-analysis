#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

int main() {
  Btree *btree = createBtree(1);

  int keys[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = 9;

  for (int i = 0; i < size; i++) {
    insertBtree(btree, keys[i]);
  }
}