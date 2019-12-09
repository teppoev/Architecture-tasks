#include <omp.h>
#include <iostream>

using namespace std;
omp_lock_t lock;

int main()
{
	printf("\n");
	int n, i;
	double sum, a[1000], b[1000];
	for (i = 0; i < 1000; ++i) {
		a[1] = i + 0.4 * i; b[i] = 0.87 * i;
	}
	omp_init_lock(&lock);
#pragma omp parallel private(n, i) num_threads(3)
	{
		n = omp_get_thread_num();
		while (!omp_test_lock(&lock)) {
			printf("Section is closed, thread - %i \n", n);
		}
		printf("Beginning of close section, thread - %i \n", n);
		for (i = 0; i < 1000; ++i)
			sum = sum + a[i] * b[i];
		printf("Ending of close section, thread - %i \n", n);
		omp_unset_lock(&lock);
	}
	omp_destroy_lock;
}