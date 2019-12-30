#include <omp.h>
#include <stdio.h>
#include <fstream>

void byRows(double** A, double* V, int n, int m, double* result) {
#pragma omp parallel for schedule(static) shared(result)
	for (int i = 0; i < n; ++i) {
		double sum = 0.0;

		for (int j = 0; j < m; ++j) {
			sum += A[i][j] * V[j];
		}
		result[i] = sum;
	}
}

void byCols(double** A, double* V, int n, int m, double* result) {
	for (int i = 0; i < n; ++i)
		result[i] = 0.0;

#pragma omp parallel for schedule(static) shared(result)
	for (int j = 0; j < m; ++j) {
		double Vj = V[j];
		for (int i = 0; i < n; ++i) {
#pragma omp atomic
			result[i] += A[i][j] * Vj;
		}
	}
}

void byBlocks(double** A, double* V, int n, int m, double* result) {
	for (int i = 0; i < n; ++i) {
		result[i] = 0.0;
	}

	int s, q = 1, tn, k, l;
#pragma omp parallel shared(s, q, tn, k, l)
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
			l = (m + m % q) / q;
		}
#pragma omp barrier

		int num = omp_get_thread_num();
		int bi = num / q;
		int bj = num % q;

		int bh = k;
		if (bi == s - 1)
			bh = n - bi * k;

		int bw = l;
		if (bj == q - 1)
			bw = m - bj * l;

		for (int i = bi * k; i < bi * k + bh; ++i) {
			double sum = 0.0;

			for (int j = bj * l; j < bj * l + bw; ++j) {
				sum += A[i][j] * V[j];
			}

#pragma omp atomic
			result[i] += sum;
		}
	}
}

int main()
{
	int n = 10000, m = 20000;
	double** matrix, * vector, * vectorprod;
	double time;
	for (int k = 1; k < 10; ++k) {
		matrix = new double* [n];
		vector = new double[m];
		vectorprod = new double[n];
		for (int i = 0; i < n; ++i) {
			matrix[i] = new double[m];
			for (int j = 0; j < m; ++j) {
				matrix[i][j] = 1;
			}
		}
		for (int i = 0; i < m; ++i) {
			vector[i] = 1;
		}
		switch (k % 3) {
		case 0:
		{
			time = omp_get_wtime();
			byRows(matrix, vector, n, m, vectorprod);
			time = omp_get_wtime() - time;
		}
		case 1:
		{
			time = omp_get_wtime();
			byCols(matrix, vector, n, m, vectorprod);
			time = omp_get_wtime() - time;
		}
		case 2:
		{
			time = omp_get_wtime();
			byBlocks(matrix, vector, n, m, vectorprod);
			time = omp_get_wtime() - time;
		}
		}
		for (int i = 0; i < n; ++i) {
			delete matrix[i];
		}
		delete[] matrix, vector, vectorprod;
		if (k % 3 == 0) printf("by rows; ");
		if (k % 3 == 1) printf("by collumns; ");
		if (k % 3 == 2) printf("by block; ");
		printf("time is %f seconds;\n", time);
	}
}
