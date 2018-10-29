/*
 * lib.h
 *
 *  Created on: 22 de out de 2018
 *      Author: melina
 */

#ifndef LIB_H_
#define LIB_H_

#define TAMANHO_MAX_DISCO 1000000
#define key(A)	(A)
#define less(A, B)	(key(A) < key(B))
#define exch(A, B)	{ int t = A; A = B; B = t; }
#define soma(A, B)	(A+B)

int
partition(int *vetor, int lo, int hi);

void
quicksort(int *vetor, int lo, int hi);

int
worst_fit(int *vetor, int lo, int N); //considera os arquivos na ordem que eles são apresentados

int
best_fit(int *vetor, int N);

#endif /* LIB_H_ */
