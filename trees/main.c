#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl-tree/avltree-counter.h"
#include "b-tree/btree-counter.h"
#include "red-black-tree/redblacktree-counter.h"

// int main() {
//     FILE *f = fopen("rubroNegra.txt", "w");
//     if(f == NULL){
//         printf("Erro na abertura de arquivo");
//         return 1;
//     }
//     Arvore* a = criar();    
//     for (int i = 1; i <= 1000; i++) {
//         count = 0;
//         adicionar(a, rand() % 1000);
//         fprintf(f, "%d - %d\n",i, count);
//     }
//     free(a);
//     float v[1000] = {0};
//     for(int i = 1; i <= 10;i++){
//         Arvore* a = criar(); 
//         for (int j = 0; j < 1000; j++) {
//             count = 0;
//             adicionar(a, rand() % 1000);
//             v[j] += count;
//         }
//         free(a);
//     }
    
//     for(int i = 0; i < 1000; i++){
//         fprintf(f, "%d - %.0f\n",i+1, ceil(v[i]/10));
//     }
// }

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
  ArvoreB *b1 = criarArvoreB(1, &qB1);
  ArvoreB *b5 = criarArvoreB(5, &qB1);
  ArvoreB *b10 = criarArvoreB(10, &qB5);
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
    inserirNaArvoreB(b1, i, &qB1);
    inserirNaArvoreB(b5, i, &qB5);
    inserirNaArvoreB(b10, i, &qB10);
    inserirNaArvoreRubroNegra(rn, i, &qRn);

    fprintf(avlFile, "%d %d\n", i, qAvl);
    fprintf(b1File, "%d %d\n", i, qB1);
    fprintf(b5File, "%d %d\n", i, qB5);
    fprintf(b10File, "%d %d\n", i, qB10);
    fprintf(rnFile, "%d %d\n", i, qRn);
  }

  destruirAvl(avl);
  destruirArvoreB(b1);
  destruirArvoreB(b5);
  destruirArvoreB(b10);
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
  ArvoreB **b1Array = malloc(10 * sizeof(ArvoreB*));
  ArvoreB **b5Array = malloc(10 * sizeof(ArvoreB *));
  ArvoreB **b10Array = malloc(10 * sizeof(ArvoreB *));
  ArvoreRN **rnArray = malloc(10 * sizeof(ArvoreRN *));


  for (int i = 0; i < 10; i++) {
    avlArray[i] = NULL;
    b1Array[i] = criarArvoreB(1, &qB1);
    b5Array[i] = criarArvoreB(5, &qB5);
    b10Array[i] = criarArvoreB(10, &qB10);
    rnArray[i] = criarArvoreRubroNegra(&qRn);
  }

  for (int i = 1; i <= 1000; i++) {
    qAvl = 0, qB1 = 0, qB5 = 0, qB10 = 0, qRn = 0;

    for (int j = 0; j < 10; j++) {
      int val = abs(rand() % 1000);

      avlArray[j] = inserirNaAvl(avlArray[j], val, &qAvl);
      inserirNaArvoreB(b1Array[j], val, &qB1);
      inserirNaArvoreB(b5Array[j], val, &qB5);
      inserirNaArvoreB(b10Array[j], val, &qB10);
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
    destruirArvoreB(b1Array[i]);
    destruirArvoreB(b5Array[i]);
    destruirArvoreB(b10Array[i]);
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