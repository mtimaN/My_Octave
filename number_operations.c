// Copyright Mantu Matei 312CA 2022-2023
#include <stdio.h>
#include <stdlib.h>
#define MOD 10007

int modulo(int x)
{
	return (x % MOD + MOD) % MOD;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

void my_swap(int *a, int *b)
{
	if (a == b)
		return;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}
