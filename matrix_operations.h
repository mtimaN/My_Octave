#pragma once

void load_matrix(int ***a, int m, int n);

void free_matrix(int **a, int m);

void crop_matrix(int ***a, int *m, int *n);

int **mat_product(int **a, int **b, int ma, int na, int nb);

void read_matrix(int **a, int m, int n);

void print_matrix(int **a, int m, int n);

void transpose_matrix(int ***a, int *m, int *n);

void matrix_power(int ***a, int n, int pow);

int squares_sum(int **a, int m, int n);

void matrix_sort(int ***matrices, int *m, int *n, int size);

void m_sum(int **a, int **b, int **sum, int n);

void m_dif(int **a, int **b, int **dif, int n);

void m_dif(int **a, int **b, int **dif, int n);

void strassen_free(int ***a, int n, int size);

int **strassen(int **a, int **b, int n);
