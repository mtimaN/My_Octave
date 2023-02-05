// Copyright Mantu Matei 312CA 2022-2023
#include <stdio.h>
#include <stdlib.h>
#include "number_operations.h"
#define MOD 10007
#define ERR "Error allocating memory\n"

void load_matrix(int ***a, int m, int n)
{
	int i;
	int **b = (int **)malloc(m * sizeof(int *));
	if (!b) {
		printf(ERR);
		return;
	}
	for (i = 0; i < m; ++i) {
		b[i] = calloc(n, sizeof(int));
		if (!b[i]) {
			for (int j = 0; j < i; ++j)
				free(b[j]);
			printf(ERR);
			return;
		}
	}
	*a = b;
}

void free_matrix(int **a, int m)
{
	int i;
	for (i = 0; i < m; ++i)
		free(a[i]);
	free(a);
}

void crop_matrix(int ***a, int *m, int *n)
{
	int i, j, **mat, **b = *a;

	// making a copy
	load_matrix(&mat, *m, *n);
	for (i = 0; i < *m; ++i)
		for (j = 0; j < *n; ++j)
			mat[i][j] = b[i][j];

	// adding the lines
	int l, c, x;
	scanf("%d", &l);
	for (i = 0; i < l; ++i) {
		scanf("%d", &x);
		for (j = 0; j < *n; ++j)
			b[i][j] = mat[x][j];
	}
	for (i = 0; i < l; ++i)
		for (j = 0; j < *n; ++j)
			mat[i][j] = b[i][j];

	// adding the columns
	scanf("%d", &c);
	for (i = 0; i < c; ++i) {
		scanf("%d", &x);
		for (j = 0; j < l; ++j)
			b[j][i] = mat[j][x];
	}

	// resizing
	free_matrix(mat, *m);
	for (i = l; i < *m; ++i)
		free(b[i]);
	b = (int **)realloc(b, l * sizeof(int *));
	for (i = 0; i < l; ++i)
		b[i] = (int *)realloc(b[i], c * sizeof(int));
	*m = l;
	*n = c;
	*a = b;
}

int **mat_product(int **a, int **b, int ma, int na, int nb)
{
	int i, j, k, **product;
	load_matrix(&product, ma, nb);
	for (i = 0; i < ma; ++i)
		for (j = 0; j < na; ++j)
			for (k = 0; k < nb; ++k) {
				product[i][k] += modulo(a[i][j]) * modulo(b[j][k]);
				product[i][k] = modulo(product[i][k]);
			}
	return product;
}

void read_matrix(int **a, int m, int n)
{
	int i, j;
	for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
			scanf("%d", &a[i][j]);
}

void print_matrix(int **a, int m, int n)
{
	int i, j;
	for (i = 0; i < m; ++i) {
		for (j = 0; j < n; ++j)
			printf("%d ", a[i][j]);
		printf("\n");
	}
}

void transpose_matrix(int ***a, int *m, int *n)
{
	int i, j, **matrix = *a;

	// resizing the matrix in order to transpose the matrix
	if (*m < *n) {
		matrix = (int **)realloc(matrix, (*n) * sizeof(int *));
		for (i = *m; i < *n; ++i)
			matrix[i] = (int *)calloc((*n), sizeof(int));
	}
	if (*n < *m)
		for (i = 0; i < *m; ++i) {
			matrix[i] = (int *)realloc(matrix[i], (*m) * sizeof(int));
			for (j = *n; j < *m; ++j)
				matrix[i][j] = 0;
		}

	// transposing
	int mx = max(*m, *n);
	for (i = 0; i < mx; ++i)
		for (j = i + 1; j < mx; ++j)
			my_swap(&matrix[i][j], &matrix[j][i]);
	my_swap(m, n);

	// freeing excess memory
	if (*m < *n) {
		for (i = *m; i < *n; ++i)
			free(matrix[i]);
	} else if (*n < *m) {
		for (i = 0; i < *m; ++i)
			matrix[i] = (int *)realloc(matrix[i], (*n) * sizeof(int));
	}
	*a = matrix;
}

void matrix_power(int ***a, int n, int pow)
{
	// using the fast exponentiation algorithm
	int **aux, i, j, **new_a = *a;
	if (pow == 0) {
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j)
				if (i == j)
					new_a[i][j] = 1;
				else
					new_a[i][j] = 0;
	}
	load_matrix(&aux, n, n);
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			aux[i][j] = new_a[i][j];
	pow--;
	while (pow > 0) {
		int **old;
		if (pow & 1) {
			old = new_a;
			new_a = mat_product(new_a, aux, n, n, n);
			free_matrix(old, n);
		}
			old = aux;
			aux = mat_product(aux, aux, n, n, n);
			pow >>= 1;
			free_matrix(old, n);
	}
	free_matrix(aux, n);
	*a = new_a;
}

int squares_sum(int **a, int m, int n)
{
	int i, j, s = 0;
	for (i = 0; i < m; ++i) {
		for (j = 0; j < n; ++j) {
			s += a[i][j];
			s = modulo(s);
		}
	}
	return s;
}

void matrix_sort(int ***matrices, int *m, int *n, int size)
{
	int *sums = (int *)calloc(size, sizeof(int));
	int i, ok = 0;
	for (i = 0; i < size; ++i)
		sums[i] = squares_sum(matrices[i], m[i], n[i]);

	//bubble sort
	while (!ok) {
		ok = 1;
		for (i = 0; i < size - 1; ++i)
			if (sums[i] > sums[i + 1]) {
				my_swap(&sums[i], &sums[i + 1]);
				my_swap(&m[i], &m[i + 1]);
				my_swap(&n[i], &n[i + 1]);
				int **aux;
				aux = matrices[i];
				matrices[i] = matrices[i + 1];
				matrices[i + 1] = aux;
				ok = 0;
			}
	}
	free(sums);
}

void m_sum(int **a, int **b, int **sum, int n)
{
	int i, j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			sum[i][j] = modulo(a[i][j] + b[i][j]);
}

void m_dif(int **a, int **b, int **dif, int n)
{
	int i, j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			dif[i][j] = modulo(a[i][j] - b[i][j]);
}

void strassen_init(int ****block, int size)
{
	*block = (int ***)malloc((size * sizeof(int **)));
	if (!*block) {
		printf(ERR);
		return;
	}
}

void strassen_free(int ***a, int n, int size)
{
	int i, j;
	for (i = 0; i < size; ++i)
		for (j = 0; j < n; ++j)
			free(a[i][j]);
	for (i = 0; i < size; ++i)
		free(a[i]);
	free(a);
}

int **strassen(int **a, int **b, int n)
{
	int **c_final;
	load_matrix(&c_final, n, n);
	if (n == 1) {
		c_final[0][0] = modulo(modulo(a[0][0]) * modulo(b[0][0]));
		return c_final;
	}
	n /= 2;
	int ***a_b, ***b_b, ***c, ***m, i, j;
	strassen_init(&a_b, 4);
	strassen_init(&b_b, 4);
	strassen_init(&c, 4);
	strassen_init(&m, 7);
	for (i = 0; i < 4; ++i) {
		load_matrix(&a_b[i], n, n);
		load_matrix(&b_b[i], n, n);
		load_matrix(&c[i], n, n);
	}

	// splitting the matrix into 4
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j) {
			a_b[0][i][j] = a[i][j];
			a_b[1][i][j] = a[i][j + n];
			a_b[2][i][j] = a[i + n][j];
			a_b[3][i][j] = a[i + n][j + n];
			b_b[0][i][j] = b[i][j];
			b_b[1][i][j] = b[i][j + n];
			b_b[2][i][j] = b[i + n][j];
			b_b[3][i][j] = b[i + n][j + n];
		}
	//computing the 7 matrices
	int **tmp1, **tmp2;
	load_matrix(&tmp1, n, n);
	load_matrix(&tmp2, n, n);
	m_sum(a_b[0], a_b[3], tmp1, n);
	m_sum(b_b[0], b_b[3], tmp2, n);
	m[0] = strassen(tmp1, tmp2, n);
	m_sum(a_b[2], a_b[3], tmp1, n);
	m[1] = strassen(tmp1, b_b[0], n);
	m_dif(b_b[1], b_b[3], tmp1, n);
	m[2] = strassen(a_b[0], tmp1, n);
	m_dif(b_b[2], b_b[0], tmp1, n);
	m[3] = strassen(a_b[3], tmp1, n);
	m_sum(a_b[0], a_b[1], tmp1, n);
	m[4] = strassen(tmp1, b_b[3], n);
	m_dif(a_b[2], a_b[0], tmp1, n);
	m_sum(b_b[0], b_b[1], tmp2, n);
	m[5] = strassen(tmp1, tmp2, n);
	m_dif(a_b[1], a_b[3], tmp1, n);
	m_sum(b_b[2], b_b[3], tmp2, n);
	m[6] = strassen(tmp1, tmp2, n);

	//computing the 4 result matrices
	m_sum(m[0], m[3], tmp1, n);
	m_dif(m[6], m[4], tmp2, n);
	m_sum(tmp1, tmp2, c[0], n);
	m_sum(m[2], m[4], c[1], n);
	m_sum(m[1], m[3], c[2], n);
	m_dif(m[0], m[1], tmp1, n);
	m_sum(m[2], m[5], tmp2, n);
	m_sum(tmp1, tmp2, c[3], n);

	//combining the 4 matrices into one
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j) {
			c_final[i][j] = c[0][i][j];
			c_final[i][j + n] = c[1][i][j];
			c_final[i + n][j] = c[2][i][j];
			c_final[i + n][j + n] = c[3][i][j];
		}
	//freeing up all memory used
	free_matrix(tmp1, n);
	free_matrix(tmp2, n);
	strassen_free(a_b, n, 4);
	strassen_free(b_b, n, 4);
	strassen_free(c, n, 4);
	strassen_free(m, n, 7);
	return c_final;
}
