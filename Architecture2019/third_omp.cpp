/*#include <omp.h>
#include <stdio.h>
#include <fstream>

void byRows(double** A, double* V, int n, int m, double* result) {
#pragma omp parallel for schedule(static) shared(result)
	for (int i = 0; i < n; ++i) {
		double localRes = 0.0;

		for (int j = 0; j < m; ++j) {
			localRes += A[i][j] * V[j];
		}
		result[i] = localRes;
	}
}

void byCols(const mat A, const vec H, int h, int w, vec result) {
	for (int i = 0; i < h; ++i)
		result[i] = 0.0;

#pragma omp parallel for schedule(static) shared(result)
	for (int j = 0; j < w; ++j) {
		double Hj = H[j];
		for (int i = 0; i < h; ++i) {
#pragma omp atomic
			result[i] += A[i][j] * Hj;
		}
	}
}

void byBlocks(const mat A, const vec H, int h, int w, vec result) {
	for (int i = 0; i < h; ++i) {
		result[i] = 0.0;
	}

	int s, q = 1, tn, k, l;
#pragma omp parallel shared(s, q, tn, k, l)
	{
#pragma omp single
		tn = omp_get_num_threads();

#pragma omp barrier

#pragma omp for reduction(max: q)
		for (int i = 2; i <= (int)sqrt(tn); ++i) {
			if (tn % i == 0)
				q = i;
		}

#pragma omp single
		{
			if (w < h)
				s = tn / q;
			else {
				s = q;
				q = tn / s;
			}
			k = (h + h % s) / s;
			l = (w + w % q) / q;
		}
#pragma omp barrier

		int num = omp_get_thread_num();
		int bi = num / q;
		int bj = num % q;

		int bh = k;
		if (bi == s - 1)
			bh = h - bi * k;

		int bw = l;
		if (bj == q - 1)
			bw = w - bj * l;

		for (int i = bi * k; i < bi * k + bh; ++i) {
			double localRes = 0.0;

			for (int j = bj * l; j < bj * l + bw; ++j) {
				localRes += A[i][j] * H[j];
			}

#pragma omp atomic
			result[i] += localRes;
		}
	}
}
*/