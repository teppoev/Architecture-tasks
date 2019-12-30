/*#include <omp.h>
#include <stdio.h>

int main()
{
	int n = 1000, m = 2000, l = 1500;
	double **matrix1, **matrix2, **matrixprod; //[n x m], [m x l], [n x l]
	double time;
	for (int k = 1; k < 100; ++k) {
		matrix1 = new double* [n];
		matrix2 = new double* [m];
		matrixprod = new double* [l];
		for (int i = 0; i < n; ++i) {
			matrix1[i] = new double[m];
			matrixprod[i] = new double[l];
			for (int j = 0; j < m; ++j) {
				matrix1[i][j] = 1;
			}
		}
		for (int i = 0; i < m; ++i) {
			matrix2[i] = new double[l];
			for (int j = 0; j < l; ++j) {
				matrix2[i][j] = 1;
			}
		}
		time = omp_get_wtime();
#pragma omp parallel for schedule(static) shared(matrixprod)
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < l; ++j)
			{
				double sum = 0.0;
				for (int k = 0; k < m; ++k) {
					sum += matrix1[i][k] * matrix2[k][j];
				}
				matrixprod[i][j] = sum;
			}
		}
		time = omp_get_wtime() - time;
		for (int i = 0; i < n; ++i) {
			delete matrix1[i];
			delete matrixprod[i];
		}
		for (int j = 0; j < m; ++j) {
			delete matrix2[j];
		}
		delete[] matrix1, matrix2, matrixprod;
		printf("time is %f seconds;\n", time);
	}
}
*/