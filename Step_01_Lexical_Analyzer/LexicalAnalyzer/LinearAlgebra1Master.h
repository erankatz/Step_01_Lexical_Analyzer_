#ifndef __LINEARALGEBRA1MASTER_H__
#define __LINEARALGEBRA1MASTER_H__

#include <assert.h>

#define M 3
#define N 3
#define MATRIXFILE "Matrix.txt"
#define OPERATIONFILE "RowOperations.txt"


float random();

int** RandomizeMatrix(int m, int n);

int** CreateMatrix(int m, int n);

void SaveMatrixToFile(float** mat, int m, int n, const char* filename);


void FreeMatrix(float** mat, int m);
float** CreateElementaryMatrix(int m, int n);

float** MatrixMultiplication(float** mat1, float** mat2, int m, int n);
#endif