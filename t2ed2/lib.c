#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

void
fix_up(int *vetor, int k) {

	while (k > 1 && less(vetor[k/2], vetor[k])) {
		exch(vetor[k], vetor[k/2]);
		k = k/2;
	}
}

void
fix_down(int *vetor, int sz, int k){

	while (2 * k <= sz) {
		int j = 2 * k;

		if (j < sz && less(vetor[j], vetor[j+1])){
			j++;
		}

		if (!less(vetor[k], vetor[j])) {
			break;
		}

		exch(vetor[k], vetor[j]);
		k = j;
	}
}


void
deleta_maximo(int *vetor, int N) {
	int max = vetor[1];

	exch(vetor[1], vetor[N]);
	N--;
	fix_down(vetor, N, 1);
}



int
partition(int *vetor, int lo, int hi) {
	int i = lo, j = hi+1;
	int v = vetor[lo];

	while (1) {
		while (less(vetor[++i], v))
			if (i == hi) break;
		while (less(v, vetor[--j]))
			if (j == lo) break;
		if (i >= j) break;
		exch(vetor[i], vetor[j]);
	}
	exch(vetor[lo], vetor[j]);

	return j;
}

void
quicksort(int *vetor, int lo, int hi) {
	if (hi <= lo) {
		return;
	}

	int j = partition(vetor, lo, hi);

	quicksort(vetor, lo, j-1);
	quicksort(vetor, j+1, hi);
}

int
worst_fit(int *vetor, int lo, int N){

	int soma = 0, count = 0 ;

	if(lo <= N){
		if(lo == N){
			count++;
		}
		else
		{
			do{
				if(lo==N){
					break;
				}
				soma += vetor[lo];
				lo++;
			}while(soma <= MAX_SIZE_OF_PACKAGE);

			count ++;
			count += worst_fit(vetor, lo, N);
		}
	}

	return count;

}

void
best_fit(int *vetor, int N){



}

