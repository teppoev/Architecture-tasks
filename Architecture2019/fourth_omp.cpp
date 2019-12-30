/*#include <omp.h>
#include <stdio.h>
#include <cmath>

void prod(double** A, double** B, int n, int m, int l, double** result) {
#pragma omp parallel for schedule(static) shared(result)
	for (int p = 0; p < n * m; ++p) {
		int i = p / m;
		int j = p % m;
		double sum = 0.0;
		for (int k = 0; k < l; ++k) {
			sum += A[i][k] * B[k][j];
		}
		result[i][j] = sum;
	}
}

void prodBlock(double** A, double** B, int n, int m, int l, double** result) {
	int s, q = 1, tn, k, p;
#pragma omp parallel shared(s, q, tn, k, p)
	{
#pragma omp single
		tn = omp_get_num_threads();

#pragma omp barrier

#pragma omp for //reduction(max: q) //It doesn't work on my version of OpenMP:( You need OpenMP 3.0 or higher to use it.
		for (int i = 2; i <= (int)sqrt(tn); ++i) {
			if (tn % i == 0)
				//q = i //You should use this if reduction works. Otherwise use next two rows.
#pragma omp critical
				q = q < i ? i : q;
		}

#pragma omp single
		{
			if (m < n)
				s = tn / q;
			else {
				s = q;
				q = tn / s;
			}
			k = (n + n % s) / s;
			p = (m + m % q) / q;
		}
#pragma omp barrier

		int num = omp_get_thread_num();
		int bi = num / q;
		int bj = num % q;

		int bh = k;
		if (bi == s - 1)
			bh = n - bi * k;

		int bw = p;
		if (bj == q - 1)
			bw = m - bj * p;

		for (int i = bi * k; i < bi * k + bh; ++i) {
			for (int j = bj * p; j < bj * p + bw; ++j) {
				double sum = 0.0;
				for (int k = 0; k < l; ++k) {
					sum += A[i][k] * B[k][j];
				}
				result[i][j] = sum;
			}
		}
	}
}

int main()
{
	int n = 1000, m = 2000, l = 1500;
	double** matrix1, ** matrix2, ** matrixprod; //[n x l], [l x m], [n x m]
	double time;
	for (int k = 1; k < 10; ++k) {
		matrix1 = new double* [n];
		matrix2 = new double* [l];
		matrixprod = new double* [n];
		for (int i = 0; i < n; ++i) {
			matrix1[i] = new double[l];
			matrixprod[i] = new double[m];
			for (int j = 0; j < l; ++j) {
				matrix1[i][j] = 1;
			}
		}
		for (int i = 0; i < l; ++i) {
			matrix2[i] = new double[m];
			for (int j = 0; j < m; ++j) {
				matrix2[i][j] = 1;
			}
		}
		switch (k % 2) {
		case 0:
		{
			time = omp_get_wtime();
			prod(matrix1, matrix2, n, m, l, matrixprod);
			time = omp_get_wtime() - time;
		}
		case 1:
		{
			time = omp_get_wtime();
			prodBlock(matrix1, matrix2, n, m, l, matrixprod);
			time = omp_get_wtime() - time;
		}
		}
		for (int i = 0; i < n; ++i) {
			delete matrix1[i];
			delete matrixprod[i];
		}
		for (int j = 0; j < l; ++j) {
			delete matrix2[j];
		}
		delete[] matrix1, matrix2, matrixprod;
		if (k % 2 == 0) printf("tape; ");
		if (k % 2 == 1) printf("block; ");
		printf("time is %f seconds;\n", time);
	}
}
*/