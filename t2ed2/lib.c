#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

int
partition(int *vetor, int low, int hi) {
	int i = low, j = hi+1;
	int v = vetor[low];

	while (1) {
		while (less(vetor[++i], v))
			if (i == hi) break;
		while (less(v, vetor[--j]))
			if (j == low) break;
		if (i >= j) break;
		exch(vetor[i], vetor[j]);
	}
	exch(vetor[low], vetor[j]);

	return j;
}

void
quicksort(int *vetor, int low, int hi) {
	if (hi <= low) {
		return;
	}

	int j = partition(vetor, low, hi);

	quicksort(vetor, low, j-1);
	quicksort(vetor, j+1, hi);
}

int
worst_fit(int *vetor, int low, int N){

	int soma = 0, contagem = 0 ;

	if(low <= N){
		if(low == N){
			contagem++;
		}
		else
		{
			do{
				if(low==N){
					break;
				}
				soma += vetor[low];
				low++;
			}while(soma <= TAMANHO_MAX_DISCO);

			contagem ++;
			contagem += worst_fit(vetor, low, N);
		}
	}
	return contagem;

}

int
best_fit(int *vetor, int N){

	int i = 1, j, k = 0,
			melhor_dif_minima = TAMANHO_MAX_DISCO,
			melhor_indice = 1,
			contagem = 0,
			discos[N];

	while (k < N){
		discos[k] = TAMANHO_MAX_DISCO;
		k++;
	}

	for (i = 1; i <= N; i++){
		melhor_dif_minima = TAMANHO_MAX_DISCO;
		for(j = 0; j < contagem; j++){
			if((discos[j] >= vetor[i]) && (discos[j] - vetor[i]) < melhor_dif_minima){
				melhor_dif_minima = (discos[j] - vetor[i]);
				melhor_indice = j;
			}
		}

		if (melhor_dif_minima != TAMANHO_MAX_DISCO){
			discos[melhor_indice] -= vetor[i];
		}
		else
		{
			discos[contagem] -= vetor[i];
			contagem++;
		}
	}

	return contagem;
}
