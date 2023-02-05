// Copyright Mantu Matei 312CA 2022-2023
#include <stdio.h>
#include <stdlib.h>
#include "matrix_operations.h"
#include "matrix_array.h"
#include "checks.h"

int main(void)
{
	char c;
	int ind, i, j, *m, *n, ***mats, size = 0, cap = 1, garbage, pow;
	init(&mats, &m, &n);
	scanf("%c ", &c);
	while ('A' <= c && c <= 'Z') {
		if (c == 'L') {
			if (size == cap)
				change_cap(&mats, &m, &n, &cap, 'I');
			scanf("%d%d", &m[size], &n[size]);
			load_matrix(&mats[size], m[size], n[size]);
			read_matrix(mats[size], m[size], n[size]);

			size++;
		} else if (c == 'D') {
			scanf("%d", &ind);
			if (matrix_exists(ind, size))
				printf("%d %d\n", m[ind], n[ind]);
		} else if (c == 'P') {
			scanf("%d", &ind);
			if (matrix_exists(ind, size))
				print_matrix(mats[ind], m[ind], n[ind]);
		} else if (c == 'C') {
			scanf("%d", &ind);
			if (matrix_exists(ind, size))
				crop_matrix(&mats[ind], &m[ind], &n[ind]);
		} else if (c == 'M') {
			scanf("%d%d", &i, &j);
			if (check_M(i, j, size, n, m)) {
				if (size == cap)
					change_cap(&mats, &m, &n, &cap, 'I');
				m[size] = m[i];
				n[size] = n[j];
				mats[size++] = mat_product(mats[i], mats[j], m[i], n[i], n[j]);
			}
		} else if (c == 'O') {
			matrix_sort(mats, m, n, size);
		} else if (c == 'T') {
			scanf("%d", &ind);
			if (matrix_exists(ind, size))
				transpose_matrix(&mats[ind], &m[ind], &n[ind]);
		} else if (c == 'R') {
			scanf("%d%d", &ind, &pow);
			if (check_R(ind, pow, m, n, size))
				matrix_power(&mats[ind], n[ind], pow);
		} else if (c == 'F') {
			scanf("%d", &ind);
			if (matrix_exists(ind, size)) {
				free_matrix(mats[ind], m[ind]);
				m[ind] = 0;
				n[ind] = 0;
				size--;
				for (i = ind; i < size; ++i) {
					mats[i] = mats[i + 1];
					m[i] = m[i + 1];
					n[i] = n[i + 1];
				}
				if (size * 2 < cap)
					change_cap(&mats, &m, &n, &cap, 'D');
			}
		} else if (c == 'Q') {
			free_matrices(mats, m, n, size);
			return 0;
		} else if (c == 'S') {
			scanf("%d%d", &i, &j);
			if (check_M(i, j, size, n, m)) {
				if (size == cap)
					change_cap(&mats, &m, &n, &cap, 'I');
				m[size] = m[i];
				n[size] = n[j];
				mats[size++] = strassen(mats[i], mats[j], m[i]);
			}
		} else {
			printf("Unrecognized command\n");
		}
		while (scanf("%d", &garbage))
			;
		scanf(" %c", &c);
	}
	return 0;
}
