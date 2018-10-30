#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
	int v1;
	int v2;
	int w;
} Edge;

int *parent, *rank;

void quick_sort(Edge** grafo, int left, int right) {
    int i, j, w_pivo;
	Edge* aux;
     
    i = left;
    j = right;
    w_pivo = grafo[(left + right) / 2]->w;
     
    while(i <= j) {
        while(grafo[i]->w < w_pivo && i < right)
            i++;
		
        while(grafo[j]->w > w_pivo && j > left)
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

int get_root(int i){
	while(i != parent[i]) {
	  i = parent[i];
	}
	return i;
}

int main(int argc, char* argv[]) {

	FILE* entrada = fopen (argv[1], "rb");
	if(!entrada) {
		printf("Erro ao abrir arquivo!\n");
		return 0;
	}
	char buffer[100];
	int nVertices, nArestas, i = 0;
    Edge** grafo;

	int v1, v2, valor;
	while(!feof(entrada)) {
		fgets(buffer, 100, entrada);
		if(buffer[0] == 'p') {
			sscanf(buffer, "p sp %d %d", &nVertices, &nArestas);
			grafo = (Edge**)malloc(nArestas*sizeof(Edge*));
        }
		else if (buffer[0] == 'a') {
			sscanf(buffer, "a %d %d %d", &v1, &v2, &valor);
			grafo[i] = (Edge*)malloc(sizeof(Edge));
			grafo[i]->v1 = v1-1;
			grafo[i]->v2 = v2-1;
			grafo[i++]->w = valor;
		}
	}
	
	quick_sort(grafo,0,nArestas-1);
	
	double peso_arvore = 0, tamanho_arvore = 0;
	
	parent = (int*)malloc(nVertices*sizeof(int));
	rank   = (int*)calloc(nVertices,sizeof(int));
	for(i=0; i<nVertices; i++) parent[i] = i;
	
	for(i=0; tamanho_arvore<nVertices-1; i++) {
		v1 = get_root(grafo[i]->v1);
		v2 = get_root(grafo[i]->v2);
		
		if (v1!=v2) {
			if (rank[v1] > rank[v2])
				parent[v2] = v1;
			else
				parent[v1] = v2;
			
			if (rank[v1] == rank[v2])
				rank[v2]++;
			
			peso_arvore += grafo[i]->w;
			tamanho_arvore++;
		}
	}
	
	
	printf("\n%s\n", argv[1]);
	printf("Vertices = %d\tArestas = %d\n", nVertices, nArestas);
}
