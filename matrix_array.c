// Copyright Mantu Matei 312CA 2022-2023
#include <stdio.h>
#include <stdlib.h>
#define cc const char
#define ERR "Error allocating memory\n"

void free_matrices(int ***matrices, int *m, int *n, int size)
{
	int i, j;
	for (i = 0; i < size; ++i)
		for (j = 0; j < m[i]; ++j)
			free(matrices[i][j]);
	for (i = 0; i < size; ++i)
		free(matrices[i]);
	free(matrices);
	free(m);
	free(n);
}

void init(int ****matrices, int **m, int **n)
{
	*m = (int *)malloc(sizeof(int));
	if (!*m) {
		printf(ERR);
		return;
	}
	*n = (int *)malloc(sizeof(int));
	if (!*n) {
		free(*m);
		printf(ERR);
		return;
	}
	*matrices = (int ***)malloc(sizeof(int **));
	if (!*matrices) {
		free(*m);
		free(*n);
		printf(ERR);
		return;
	}
}

void change_cap(int ****matrices, int **m, int **n, int *cap, cc mode)
{
	if (mode == 'I') {
		*cap *= 2;
	} else if (mode == 'D') {
		*cap /= 2;
		if (*cap == 0) {
			*cap += 1;
			return;
		}
	}
	*m = (int *)realloc(*m, *cap * sizeof(int));
	if (!*m) {
		printf(ERR);
		return;
	}
	*n = (int *)realloc(*n, *cap * sizeof(int));
	if (!*n) {
		printf(ERR);
		free(*m);
		return;
	}
	*matrices = (int ***)realloc(*matrices, *cap * sizeof(int **));
	if (!*matrices) {
		printf(ERR);
		free(*m);
		free(*n);
		return;
	}
}
