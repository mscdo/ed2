#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int
main (int argc, char *argv[]){

	int N, i, size_of_file, number_of_disks = 0;
	char file_string[10];


	FILE *file;
	file = fopen (argv[1], "r");

	if (file == NULL){
		printf ("Não foi possível abrir o file. \n");
		return 1;
	}

	fscanf(file, "%d", &N);

	int data_arrays[N + 1];

	for (i = 1;i <= N;i ++){
		fscanf (file, "%s", file_string);
		size_of_file = atoi (file_string);
		data_arrays[i] = size_of_file;
	}

	fclose(file);

	number_of_disks = worst_fit(data_arrays, 1, N);
	printf ("WORST FIT : ");
	printf ("%d discos necessários \n", number_of_disks);

	number_of_disks = best_fit(data_arrays, N);
	printf ("BEST FIT: ");
	printf ("%d discos necessários \n", number_of_disks);

	quicksort(data_arrays, 1, N);

	number_of_disks = worst_fit(data_arrays, 1, N);
	printf ("WORST FIT DECRESCENTE: ");
	printf ("%d discos necessários \n", number_of_disks);

	number_of_disks = best_fit(data_arrays, N);
	printf ("BEST FIT DECRESCENTE: ");
	printf ("%d discos necessários \n", number_of_disks);

	return 0;
}
