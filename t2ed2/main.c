#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main(int argc, char *argv[]){

	int N, i, tamanho_arquivo, num_discos = 0;
	char string_arquivo[10];


	FILE *arquivo;
	arquivo = fopen (argv[1], "r");

	if(arquivo == NULL){
		printf("Não foi possível abrir o arquivo. \n");
		return 1;
	}

	fscanf(arquivo, "%d", &N);

	int vetor_dados[N + 1];

	for (i = 1;i <= N;i ++){
		fscanf (arquivo, "%s", string_arquivo);
		tamanho_arquivo = atoi (string_arquivo);
		vetor_dados[i] = tamanho_arquivo;
	}

	fclose(arquivo);

	num_discos = worst_fit(vetor_dados, 1, N);
	printf("WORST FIT : ");
	printf("%d discos necessários \n", num_discos);

	num_discos = best_fit(vetor_dados, N);
	printf("BEST FIT: ");
	printf("%d discos necessários \n", num_discos);

	quicksort(vetor_dados, 1, N);
	/*int k;
	for(k=1;k<=N;k++){
		printf("%d \n", vetor_dados[k]);
	}*/
	num_discos = worst_fit(vetor_dados, 1, N);
	printf("WORST FIT DECRESCENTE: ");
	printf("%d discos necessários \n", num_discos);

	num_discos = best_fit(vetor_dados, N);
	printf("BEST FIT DECRESCENTE: ");
	printf("%d discos necessários \n", num_discos);

	return 0;
}
