
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/*
* STRUCTS
*/

typedef struct ponto Ponto;
typedef struct grafo Grafo;
typedef struct vertice Vertice;

/* 
* PILHA
*/

void inicia(float x, float y, Ponto *pilha);
int vazia(Ponto *pilha);
Ponto *aloca(float x, float y, Ponto *pilha);

void liberaPilha(Ponto *pilha);
void push(Ponto *pilha, float x, float y);
Ponto* pop(Ponto *pilha);
void percorre(Ponto *pilha);


/*
* MATRIZ
*/

float **alocaMatriz(int tamanhoPilha);
void preencheMatriz(int tamanhoPilha, Ponto *pilha, float **matrizTriangularSuperior);
float calculaDistancia(float x1, float y1, float x2, float y2);
int *criaPai(int tamanhoPilha);
int findPai(int x, int *pai);
int MenorLinha(float **matrizTriangularSuperior, int i, int tamanhoPilha);
void unePai(int a, int b, int *pai);

/*
* GRAFO E KRUSKAL
*/

void criaVetorAdjacencias(float **matrizTriangularSuperior, int tamanhoPilha, Vertice* vetor[]);
void insereOrdenado(Vertice *a, int i);
void mst_kruskal(Vertice* vetor[], int tamanhoPilha);
void liberaMatriz(float **matrizTriangularSuperior, int tamanhoPilha);



#endif