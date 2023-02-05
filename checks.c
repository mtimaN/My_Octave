// Copyright Mantu Matei 312CA 2022-2023
#include <stdio.h>

int check_R(int ind, int pow, int *m, int *n, int size)
{
	if (ind > size - 1 || ind < 0)
		printf("No matrix with the given index\n");
	else if (m[ind] != n[ind])
		printf("Cannot perform matrix multiplication\n");
	else if (pow < 0)
		printf("Power should be positive\n");
	else
		return 1;
	return 0;
}

int check_M(int i, int j, int size, int *n, int *m)
{
	if (i > size || j > size || i < 0 || j < 0) {
		printf("No matrix with the given index\n");
			return 0;
	} else if (n[i] != m[j]) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}
	return 1;
}

int matrix_exists(int ind, int size)
{
	if (ind > size - 1 || ind < 0)
		printf("No matrix with the given index\n");
	else
		return 1;
	return 0;
}
