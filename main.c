#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "functions.h"


int main(int argc, char *argv[]){

	float x, y, **matrizTriangularSuperior;
	int tamanhoPilha, aresta;
	int *pai;
	char NAME[15], COMMENT[15], DIMENSION[15], lixo[30];
	char number, name[40], nome_arquivo[40];

	Ponto *pilha = malloc(sizeof(Ponto*));

	/*
	****************************
	* ABERTURA DE ARQUIVO TSP *
	****************************
	*/

	FILE *arquivo = fopen(argv[1], "r");

	if(arquivo == NULL){
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	    exit(1);
	}
	
	fscanf(arquivo, "%s %s \n", NAME, name);	
	fgets(COMMENT, 50, arquivo);
	fgets(lixo, 50, arquivo);
	fgets(DIMENSION, 50, arquivo);
	fgets(lixo, 50, arquivo); // ignora a linha WEIGHT TYPE
	fgets(lixo, 50, arquivo); // ignora a linha NODE SECTION
	
	fscanf(arquivo,"%s %f %f \n", &number, &x, &y);

	do{
		push(pilha, x, y);
		tamanhoPilha++; 
	} while(number != EOF);

	fclose(arquivo);

	matrizTriangularSuperior = alocaMatriz(tamanhoPilha);
	preencheMatriz(tamanhoPilha, pilha, matrizTriangularSuperior);

	pai = criaPai(tamanhoPilha);
	aresta = tamanhoPilha - 1; //Nao entendi essa

	Vertice *vetor[tamanhoPilha];
	criaVetorAdjacencias(matrizTriangularSuperior, tamanhoPilha, vetor);
	
	FILE* arquivo_mst;

	strcpy(nome_arquivo, (strcat(name, ".mst")));
	arquivo_mst = fopen(nome_arquivo, "wt");

	if(arquivo_mst!=NULL){
		
		strcpy(nome_arquivo, strcat(name, "2"));
		strcpy(nome_arquivo, strcat(nome_arquivo, ".mst"));
		arquivo_mst = fopen(nome_arquivo, "wt");
	}

	fprintf(arquivo_mst, "%s \n", NAME);
	fprintf(arquivo_mst, "%s \n", COMMENT);
	fprintf(arquivo_mst, "%s \n", DIMENSION);
	fprintf(arquivo_mst, "MST_SECTION \n");
	//imprimeVetorAdjacencias(vetor, tamanhoPilha, arquivo_mst);	
	fprintf(arquivo_mst, "EOF");	

	fclose(arquivo_mst);
	
	//percorre(pilha);
	liberaMatriz(matrizTriangularSuperior, tamanhoPilha);
	liberaPilha(pilha); //tem que liberar matriz

	return 0;
}