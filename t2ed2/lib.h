/*
 * lib.h
 *
 *  Created on: 22 de out de 2018
 *      Author: melina
 */

#ifndef LIB_H_
#define LIB_H_

#define MAX_SIZE_OF_PACKAGE 1000000
#define key(A)	(A)
#define less(A, B)	(key(A) < key(B))
#define exch(A, B)	{ int t = A; A = B; B = t; }
#define soma(A, B)	(A+B)

typedef struct p P;
typedef struct d D;

void
fix_up(int *a, int k);

void
fix_down(int *a, int sz, int k);

void
deleta_maximo(int *vetor_dados, int N);

int
encontra_maximo(int *vetor, int N);

void
insere_no_vetor(int *vetor, int dado);

int
worst_fit(int *vetor, int lo, int N); //considera os arquivos na ordem que eles são apresentados

void
quicksort(int *vetor, int lo, int hi);


#endif /* LIB_H_ */
