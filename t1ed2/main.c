#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "functions.h"


int main(){
//int argc, char *argv[]
	float x, y, **matrizTriangularSuperior;
	int tamanhoPilha, nVertices, nArestas;
	int *pai;
	char NAME[15], COMMENT[15], DIMENSION[15], lixo[30],linha1[50],linha2[50],linha3[50],linha4[50],linha5[50],linha6[50];
	char number[8], name[40], nome_arquivo[40];

	Ponto *pilha = malloc(sizeof(Ponto*));

	/*
	****************************
	* ABERTURA DE ARQUIVO TSP *
	****************************
	*/

	FILE *arquivo = fopen("../in/berlin52.tsp", "r");

	if(arquivo == NULL){
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	}else{
		fgets(linha1, 50, arquivo);
		fgets(linha2, 50, arquivo);
		fgets(linha3, 50, arquivo);
		fgets(linha4, 50, arquivo);
		fgets(linha5, 50, arquivo);
		fgets(linha6, 50, arquivo);
		while((fscanf(arquivo,"%s %f %f\n", number, &x, &y))!=EOF){
			if(number[0]=='E'){//armengue se vc pensar em alguma ideia melhor, por favor kkkk
				break;		
			}else{
				push(pilha,x,y);
				tamanhoPilha++;
			}
		}			
	}

	fclose(arquivo);

	matrizTriangularSuperior = alocaMatriz(tamanhoPilha);
	preencheMatriz(tamanhoPilha, pilha, matrizTriangularSuperior);
	

	pai = criaPai(tamanhoPilha);
	
	nVertices = tamanhoPilha; 
	nArestas = (nVertices*(nVertices - 1) ) /2;  

	

	Vertice* vetorArcos;
	vetorArcos = criaArcos(matrizTriangularSuperior, tamanhoPilha, nArestas);

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
	fprintf(arquivo_mst, "EOF");	
	
	mst(vetorArcos, nVertices, nArestas, arquivo_mst);

	fclose(arquivo_mst);

	//percorre(pilha);
	liberaMatriz(matrizTriangularSuperior, tamanhoPilha);
	liberaPilha(pilha); //tem que liberar matriz

	return 0;
}