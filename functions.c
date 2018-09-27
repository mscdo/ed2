
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"


/*
* STRUCTS
*/

struct ponto{
    float x, y;
	struct ponto *prox;
};

struct vertice{
    int vertice1, vertice2, peso;
};

/**********************************/

void inicia(float x, float y, Ponto *pilha)
{
	pilha->prox = NULL;
	pilha->x = x;
	pilha->y = y;	
}

int vazia(Ponto *pilha)
{
	if(pilha->prox == NULL)
		return 1;
	else
		return 0;
}


Ponto *aloca(float x, float y, Ponto *pilha)
{
	Ponto *new = malloc(sizeof(Ponto));

	if(!new){
		return NULL;
	}else{
		new->x = x;
		new->y = y;
		return new;
	}
}

void liberaPilha(Ponto *pilha)
{
	if(!vazia(pilha)){
		Ponto *pontoProx;
		Ponto *atual = pilha->prox;

		while(atual != NULL){
			pontoProx = atual->prox;
			atual = pontoProx;
		}
	}
}

void push(Ponto *pilha, float x, float y)
{
	Ponto *new = aloca(x, y, pilha);
	new->prox = NULL;

	if(vazia(pilha)){
		pilha->prox = new;

	}else{
		Ponto *tmp = pilha->prox;

		while(tmp->prox != NULL)
		{
			tmp = tmp->prox;
		}
		tmp->prox = new;
	}
}


Ponto* pop(Ponto *pilha)
{
	if(pilha->prox == NULL){
		printf("Pilha já vazia \n\n");
		return NULL;
	}else{
		Ponto *fim = pilha->prox,
	          *fim2 = pilha;

		while(fim->prox != NULL){
			fim2 = fim;
			fim = fim->prox;
		}
		fim2->prox = NULL;
		return fim;
	}
}

void percorre(Ponto *pilha)
{
	Ponto *new = pilha->prox;

	while(new){
		printf("-- %f,%f \n", new->x, new->y);
		new = new->prox;
	}
}

float **alocaMatriz(int tamanhoPilha){
	int i, j; //Variáveis Auxiliares

	float **m = (float**)malloc(tamanhoPilha * sizeof(float*)); //Aloca um Vetor de Ponteiros

	for (i = 0; i < tamanhoPilha; i++){ //Percorre as linhas do Vetor de Ponteiros
	   m[i] = (float*) malloc(tamanhoPilha * sizeof(float)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
	   
	   for (j = 0; j < tamanhoPilha; j++){ //Percorre o Vetor de Inteiros atual.
	        m[i][j] = 0; //Inicializa com 0.
	   }
	}
	return m; //Retorna o Ponteiro para a Matriz Aloca
}

void preencheMatriz(int tamanhoPilha, Ponto *pilha, float **matrizTriangularSuperior){
	Ponto *aux1 = pilha->prox;
	Ponto *aux2 = pilha->prox;
	float distancia;

	for(int i = 0; i < tamanhoPilha; i++){
		aux2 = aux1;

		for(int j = i; j< tamanhoPilha; j++){
			distancia = calculaDistancia(aux1->x, aux1->y, aux2->x, aux2->y);
			matrizTriangularSuperior[i][j] = distancia;
			
			if(aux2->prox)
			{			
				aux2 = aux2->prox;
			}
		}

		if(aux1->prox)
		{			
			aux1 = aux1->prox;
		}	
	}			
}

float calculaDistancia(float x1, float y1, float x2, float y2){
	return (sqrt( pow (x2 - x1, 2) + pow (y2 - y1, 2)));	
}

void imprimeMatriz(int tamanhoPilha, float **matrizTriangularSuperior){

	for(int i=0;i<tamanhoPilha;i++){
		printf("\nlinha %i \n",i);

		for(int j = 0; j < tamanhoPilha; j++){
			printf("-%0.2f-", matrizTriangularSuperior[i][j]);	
		}	
	}			
}

int *criaPai(int tamanhoPilha){
	int i; //Variáveis Auxiliares
	int *p = (int*)malloc(tamanhoPilha * sizeof(int)); //Aloca um Vetor de Ponteiros

	for (i = 0; i < tamanhoPilha; i++){ //Percorre as linhas do Vetor de Ponteiros
    	p[i] = i;//inicializa todo o vetor com um valor de pai que é você mesmo
  	}
	return p; //Retorna o Ponteiro para a Matriz Aloca	
}

int findPai(int x, int *pai){
    if(pai[x] == x) return x;
    return pai[x] = findPai(pai[x],pai);
}

int MenorLinha(float **matrizTriangularSuperior, int i, int tamanhoPilha){
	int menor = matrizTriangularSuperior[i][i+1], indiceMenor = i + 1;

		for(int j=i+1;j<tamanhoPilha;j++){
			if(menor > matrizTriangularSuperior[i][j]){
				indiceMenor = j;
				menor = matrizTriangularSuperior[i][j];			
			}		
		}
	return indiceMenor;
}

void unePai(int a, int b, int *pai){
    pai[a] = b;
}

void liberaMatriz(float **matrizTriangularSuperior, int tamanhoPilha){

	int i;  /* variavel auxiliar */
	if (matrizTriangularSuperior != NULL){

		for (i = 0; i < tamanhoPilha; i++){
			free (matrizTriangularSuperior[i]);
		} 
		free (matrizTriangularSuperior);      
	}
}

Vertice* criaArcos(float **matrizTriangularSuperior, int tamanhoPilha, int nArestas){
	Vertice *arcos = malloc(nArestas*sizeof(Vertice));
	int i, j;

	for(i = 0; i < tamanhoPilha; i++){
 		for(j = i+1; j < tamanhoPilha; j++){
 			arcos[j].peso = matrizTriangularSuperior[i][j];
 			arcos[j].vertice1 = i;
 			arcos[j].vertice2 = j;
 		}
	}

	return 	arcos;

}

int get_root(int i, int* parent, int nVertices){
	
	while(i != parent[i]) {
	  i = parent[i]; 
		printf("%d \n", parent[i]);
	}
	return i;
}

void quick_sort(Vertice* grafo, int left, int right) {
    int i, j, peso_pivo;
	struct vertice aux;

    i = left;
    j = right;
    peso_pivo = grafo[(left + right) / 2].peso;
     
    while(i <= j) {
        while(grafo[i].peso < peso_pivo && i < right)
            i++;
		
        while(grafo[j].peso > peso_pivo && j > left)
            j--;
		
        if(i <= j) {
            aux = grafo[i];
            grafo[i] = grafo[j];
            grafo[j] = aux;
            i++;
            j--;
        }
    }
     
    if(j > left)
        quick_sort(grafo, left, j);
    
    if(i < right)
        quick_sort(grafo, i, right);
}

void mst(Vertice* grafo, int nVertices, int nArestas, FILE* arquivo) {

	int i = 0, v1, v2, valor;
	int *parent, *rank;
	
	quick_sort(grafo, 0, nArestas-1);
	
	double peso_arvore = 0, tamanho_arvore = 0;
	
	parent = malloc(nVertices*sizeof(int));
	rank   = calloc(nVertices,sizeof(int));
	
	for(i=0; i < nVertices; i++){
		parent[i] = i; 
	}

	for(i=0; tamanho_arvore < (nVertices-1); i++) {
		
		v1 = get_root(grafo[i].vertice1, parent, nVertices);
		v2 = get_root(grafo[i].vertice2, parent, nVertices);
		
		if (v1!=v2) {
			if (rank[v1] > rank[v2])
				parent[v2] = v1;
			else
				parent[v1] = v2;
			
			if (rank[v1] == rank[v2])
				rank[v2]++;
			
			peso_arvore += grafo[i].peso;
			tamanho_arvore++;
		}
	}

	//print
	free(grafo);

}