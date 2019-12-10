#include <omp.h>
#include <stdio.h>

int main()
{
	int _max, _min;
	int n = 10000, m = 20000;
	int** matrix;
	double time;
	for (int k = 1; k < 100; ++k) {
		time = omp_get_wtime();
		_max = 0;
		matrix = new int* [n]; \
			for (int i = 0; i < n; ++i) {
				matrix[i] = new int[m];
				for (int j = 0; j < m; ++j) {
					matrix[i][j] = n + 1;
					if (j == m / 2) matrix[i][j] = (i + 2) % n;
				}
			}
#pragma omp parallel for private(_min)
		for (int i = 0; i < n; ++i)
		{
			_min = _CRT_INT_MAX;
			for (int j = 0; j < m; ++j)
			{
				_min = matrix[i][j] < _min ? matrix[i][j] : _min;
			}
#pragma omp critical
			_max = _min > _max ? _min : _max;
		}
		for (int i = 0; i < n; ++i) delete matrix[i];
		delete[] matrix;

		time = omp_get_wtime() - time;
		printf("maxmin is %i, time is %f ticks;\n", _max, time);
	}
}
