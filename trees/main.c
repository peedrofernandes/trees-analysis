#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl-tree/avltree-counter.h"
#include "b-tree/btree-counter.h"
#include "red-black-tree/redblacktree-counter.h"

#define arquivoAvl "files/avl.txt"
#define arquivoB1 "files/b1.txt"
#define arquivoB5 "files/b5.txt"
#define arquivoB10 "files/b10.txt"
#define arquivoRubroNegra "files/rubroNegra.txt"

int main() {
  srand(time(NULL));

  FILE *avlFile = fopen(arquivoAvl, "wt");
  FILE *b1File = fopen(arquivoB1, "wt");
  FILE *b5File = fopen(arquivoB5, "wt");
  FILE *b10File = fopen(arquivoB10, "wt");
  FILE *rnFile = fopen(arquivoRubroNegra, "wt");

  if (avlFile == NULL || b1File == NULL || b5File == NULL || b10File == NULL || rnFile == NULL) {
    printf("Erro na abertura de algum dos arquivos!\n");
    return 1;
  }

  int qAvl = 0, qB1 = 0, qB5 = 0, qB10 = 0, qRn = 0;

  NoAVL* avl = NULL;
  Btree *b1 = createBtree(1, &qB1);
  Btree *b5 = createBtree(5, &qB1);
  Btree *b10 = createBtree(10, &qB5);
  ArvoreRN *rn = criarArvoreRubroNegra(&qRn);

  // PIOR CASO

  fprintf(avlFile, "PIOR CASO\n");
  fprintf(b1File, "PIOR CASO\n");
  fprintf(b5File, "PIOR CASO\n");
  fprintf(b10File, "PIOR CASO\n");
  fprintf(rnFile, "PIOR CASO\n");

  for (int i = 1; i <= 1000; i++) {
    qAvl = 0, qB1 = 0, qB5 = 0, qB10 = 0, qRn = 0;
    avl = inserirNaAvl(avl, i, &qAvl);
    insertBtree(b1, i, &qB1);
    insertBtree(b5, i, &qB5);
    insertBtree(b10, i, &qB10);
    inserirNaArvoreRubroNegra(rn, i, &qRn);

    fprintf(avlFile, "%d %d\n", i, qAvl);
    fprintf(b1File, "%d %d\n", i, qB1);
    fprintf(b5File, "%d %d\n", i, qB5);
    fprintf(b10File, "%d %d\n", i, qB10);
    fprintf(rnFile, "%d %d\n", i, qRn);
  }

  destruirAvl(avl);
  destroyBtree(b1);
  destroyBtree(b5);
  destroyBtree(b10);
  destruirArvoreRubroNegra(rn);

  fprintf(avlFile, "CASO MEDIO\n");
  fprintf(b1File, "CASO MEDIO\n");
  fprintf(b5File, "CASO MEDIO\n");
  fprintf(b10File, "CASO MEDIO\n");
  fprintf(rnFile, "CASO MEDIO\n");

  // NoAVL** avl = NULL;
  // ArvoreB** b1 = criarArvoreB(1, &qB1);
  // ArvoreB** b5 = criarArvoreB(5, &qB1);
  // ArvoreB** b10 = criarArvoreB(10, &qB5);
  // ArvoreRN** rn = criarArvoreRubroNegra(&qRn);

  NoAVL **avlArray = malloc(10 * sizeof(NoAVL*));
  Btree **b1Array = malloc(10 * sizeof(Btree*));
  Btree **b5Array = malloc(10 * sizeof(Btree*));
  Btree **b10Array = malloc(10 * sizeof(Btree*));
  ArvoreRN **rnArray = malloc(10 * sizeof(ArvoreRN*));


  for (int i = 0; i < 10; i++) {
    avlArray[i] = NULL;
    b1Array[i] = createBtree(1, &qB1);
    b5Array[i] = createBtree(5, &qB5);
    b10Array[i] = createBtree(10, &qB10);
    rnArray[i] = criarArvoreRubroNegra(&qRn);
  }

  for (int i = 1; i <= 1000; i++) {
    qAvl = 0, qB1 = 0, qB5 = 0, qB10 = 0, qRn = 0;

    for (int j = 0; j < 10; j++) {
      int val = abs(rand() % 1000);

      avlArray[j] = inserirNaAvl(avlArray[j], val, &qAvl);
      insertBtree(b1Array[j], val, &qB1);
      insertBtree(b5Array[j], val, &qB5);
      insertBtree(b10Array[j], val, &qB10);
      inserirNaArvoreRubroNegra(rnArray[j], val, &qRn);
    }

    fprintf(avlFile, "%d %.3lf\n", i, (double)((double)qAvl / 10));
    fprintf(b1File, "%d %.3lf\n", i, (double)((double)qB1 / 10));
    fprintf(b5File, "%d %.3lf\n", i, (double)((double)qB5 / 10));
    fprintf(b10File, "%d %.3lf\n", i, (double)((double)qB10 / 10));
    fprintf(rnFile, "%d %.3lf\n", i, (double)((double)qRn / 10));
  }

  for (int i = 0; i < 10; i++) {
    destruirAvl(avlArray[i]);
    destroyBtree(b1Array[i]);
    destroyBtree(b5Array[i]);
    destroyBtree(b10Array[i]);
    destruirArvoreRubroNegra(rnArray[i]);
  }

  free(avlArray);
  free(b1Array);
  free(b5Array);
  free(b10Array);
  free(rnArray);

  fclose(avlFile);
  fclose(b1File);
  fclose(b5File);
  fclose(b10File);
  fclose(rnFile);

}

  // compilar gcc main.c avl-tree/avltree-counter.c b-tree/btree-counter.c red-black-tree/redblacktree-counter.c -o main