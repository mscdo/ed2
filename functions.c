
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
    int vertice_id;
    int peso;
    struct vertice *prox;
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

		for(int j = i; j<tamanhoPilha; j++){
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
			printf("-%f-", matrizTriangularSuperior[i][j]);	
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

void criaVetorAdjacencias(float **matrizTriangularSuperior, int tamanhoPilha, Vertice* vetor[]) {
	int m, i, j;

 	// Aloca vetor
 	for(m = 0; m < tamanhoPilha; m++){
 		vetor[m] = malloc(sizeof(Vertice*));
 		vetor[m]->prox = NULL;
 	}

 	for(i = 0; i < tamanhoPilha; i++){
 		for(j = i; j < tamanhoPilha; j++){

 			if (matrizTriangularSuperior[i][j] != 0){
 				if (vetor[i] == NULL){ //ainda não está no vetor
 					
 					vetor[i]->vertice_id = i;
 					vetor[i]->peso = 0;

 				}else{
 					//já possui conexoes ou já foi inicializado

 					if(vetor[i]->prox == NULL){
 						//Não possui nenhuma conexão
 						vetor[i]->prox = malloc(sizeof(Vertice));
 						vetor[i]->vertice_id = i;
 						vetor[i]->peso = matrizTriangularSuperior[i][j];
 						vetor[i]->prox->prox=NULL;
 					}else{
 						//insere ordenado
 						insereOrdenado(vetor[i]->prox, i);
 					}
 				}
 			}
 		}
 	}
}

void insereOrdenado(Vertice *a, int i){

	Vertice* tmp;

	if (a[i].peso <= a[i].prox->peso){
		
		tmp = a[i].prox;
		Vertice *aux = malloc(sizeof(Vertice));
		a[i].prox = aux;
		aux->prox = tmp;

		free(tmp);
		
	}else{
		insereOrdenado(a->prox, i);
	}
}

Vertice* procuraMenorArco(Vertice* vetor, int tamanhoPilha){
	int aux=0;
	Vertice* tmp = malloc(sizeof(Vertice));
	tmp->peso = 0;
	tmp->prox = NULL;

	while(aux <= tamanhoPilha){
		if(vetor[aux].prox->peso < tmp->peso){
			tmp->peso = vetor[aux].peso;
			tmp->vertice_id = vetor[aux].vertice_id;
		}		
		aux++;
	}
	return tmp;
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

void imprimeVetorAdjacencias(Vertice* vetor, int tamanhoPilha, FILE* arquivo){
	int tmp = 0;
	Vertice* aux = malloc(sizeof(Vertice));

	while (tmp <= tamanhoPilha){
		*aux = vetor[tmp];
		while(vetor[tmp].prox != NULL){
			fprintf(arquivo, "%d %d \n", vetor[tmp].vertice_id, vetor[tmp].prox->vertice_id);
			imprimeVetorAdjacencias(vetor[tmp].prox, tamanhoPilha, arquivo);
		}
		tmp++;
	}
}