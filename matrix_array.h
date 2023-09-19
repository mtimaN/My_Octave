
#pragma once
#define cc const char

void free_matrices(int ***matrices, int *m, int *n, int size);

void init(int ****matrices, int **m, int **n);

void change_cap(int ****matrices, int **m, int **n, int *cap, cc mode);