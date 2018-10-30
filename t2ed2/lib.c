#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

int
partition(int *array, int low, int hi) {
	int i = low, j = hi+1;
	int v = array[low];

	while (1) {
		while (less(array[++i], v))
			if (i == hi) break;
		while (less(v, array[--j]))
			if (j == low) break;
		if (i >= j) break;
		exch(array[i], array[j]);
	}
	exch(array[low], array[j]);

	return j;
}

void
quicksort(int *array, int low, int hi) {
	if (hi <= low) {
		return;
	}

	int j = partition(array, low, hi);

	quicksort(array, low, j-1);
	quicksort(array, j+1, hi);
}

int
worst_fit(int *array, int low, int N){

	int sum = 0, count = 0 ;

	if (low <= N){
		if (low == N){
			count++;
		}
		else
		{
			do {
				if (low==N){
					break;
				}
				sum += array[low];
				low++;
			} while (sum <= MAX_SIZE_DISK);

			count ++;
			count += worst_fit(array, low, N);
		}
	}
	return count;

}

int
best_fit(int *array, int N){

	int i = 1, j, k = 0,
			best_min_diff = MAX_SIZE_DISK,
			best_index = 1,
			count = 0,
			disks[N];

	while (k < N){
		disks[k] = MAX_SIZE_DISK;
		k++;
	}

	for (i = 1; i <= N; i++){

		best_min_diff = MAX_SIZE_DISK;

		for (j = 0; j < count; j++){
			if ((disks[j] >= array[i]) && (disks[j] - array[i]) < best_min_diff){
				best_min_diff = (disks[j] - array[i]);
				best_index = j;
			}
		}

		if (best_min_diff != MAX_SIZE_DISK){
			disks[best_index] -= array[i];
		}
		else
		{
			disks[count] -= array[i];
			count++;
		}
	}

	return count;
}
