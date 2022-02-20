#include <stdio.h>
#include <string.h>

typedef struct Matrix {
	int m;
	int n;
	int matrix[100][100];
} Matrix;

Matrix matrixMultiplication(Matrix m1, Matrix m2) {
	Matrix result = {m1.m, m2.n};

	if (m1.m != m2.n) {
		return result;
	}

	for (int i = 0; i < m1.m; i++) {
		for (int j = 0; j < m2.n; j++) {
			for (int k = 0; k < m1.m + 1; k++) {
				result.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
			}
		}
	}
	return result;
}

void matrixPrint(Matrix m) {
	for (int i = 0; i < m.m; i++) {
		for (int j = 0; j < m.n; j++) {
			printf("%d ", m.matrix[i][j]);
		}
		printf("\n");
	}
}

Matrix scanMatrix(char name[]) {
	Matrix m;
	FILE *fp;
	strcat(name, ".txt");
	fp = fopen(name, "r+");

	fscanf(fp, "%d\n", &m.m);
	fscanf(fp, "%d\n", &m.n);

	for (int i = 0; i < m.m; i++) {
		for (int j = 0; j < m.n; j++) {
			fscanf(fp, "%d\n", &m.matrix[i][j]);
			// printf("%d ",m.matrix[i][j]);
		}
	}
	fclose(fp);
	return m;
}

int main(void) {
	char name1[] = "a";
	char name2[] = "b";

	Matrix mat1 = scanMatrix(name1);
	Matrix mat2 = scanMatrix(name2);

	Matrix result = matrixMultiplication(mat1, mat2);
	matrixPrint(result);
	return 0;
}