/*
 * lib.h
 *
 *  Created on: 22 de out de 2018
 *      Author: melina
 */

#ifndef LIB_H_
#define LIB_H_

#define MAX_SIZE_DISK 1000000
#define key(A)	(A)
#define less(B, A)	(key(A) < key(B))
#define exch(A, B)	{ int t = A; A = B; B = t; }
#define soma(A, B)	(A+B)

int
partition(int *array, int low, int hi);

void
quicksort(int *array, int low, int hi);

int
worst_fit(int *array, int low, int N);

int
best_fit(int *array, int N);

#endif /* LIB_H_ */
