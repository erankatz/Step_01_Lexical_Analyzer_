
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#include "LinearAlgebra1Master.h"

float random()
{
	_sleep(557);
	srand(time(NULL));
	return  (float)5 - rand() % 11;
}

float** RandomizeMatrix(int m, int n)
{
	int i, j, k;
	float **x, *y;

	x = CreateMatrix(m, n);
	for (i = 0; i<m; i++)
	{
		for (j = 0; j<n; j++)
		{
			x[i][j] = random();
		}
	}

	return x;
}

float** CreateMatrix(int m, int n)
{
	int i;
	float **x, *y;

	x = (float **)malloc(m * sizeof(float));
	for (i = 0; i<m; i++)
		x[i] = (int *)malloc(n * sizeof(float));
	y = (float *)malloc(n * sizeof(float));
	return x;
}

void SaveMatrixToFile(float** mat, int m, int n, const char* filename)
{
	int i, j;
	FILE *file = fopen(filename, "w");
	fprintf(file, "[");

	for (i = 0; i<m; i++)
	{
		for (j = 0; j<n; j++)
		{
			fprintf(file, " %.2f",mat[i][j]);
		}
		if (i < m - 1)
		{
			fprintf(file, " ;");
		}
	}
	fprintf(file, "]");
	flushall();
	fclose(file);
}

void FreeMatrix(float** mat, int m)
{
	int i;

	for (i = 0; i<m; i++)
	{
		free(mat[i]);
	}
	free(mat);
}

float** CreateElementaryMatrix(int m, int n)
{
	int i;
	int j;
	float** mat = CreateMatrix(m, n);

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				mat[i][j] = 1;
			}
			else {
				mat[i][j] = 0;
			}
		}
	}

	return mat;
}

float** MatrixMultiplication(float** mat1, float** mat2, int m, int n)
{
	int i, j, k;
	float sum;
	float** mat3;

	mat3 = CreateMatrix(M, N);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			sum = 0;
			for (k = 0; k < m; k++) {
				sum = sum + mat1[i][k] * mat2[k][j];
			}
			mat3[i][j] = sum;
		}
	}
	return mat3;
}
