/*
#include <omp.h>
#include <stdio.h>

int main()
{
	int n;
#pragma omp parallel private(n)
	{
		n = omp_get_thread_num();
		printf("Before critical %i \n", n);
#pragma omp critical
		{
			n = omp_get_thread_num();
			printf("Thread %i is working \n", n);
		}
		printf("After critical %i \n", n);
	}
}
*/