#include "omp.h"
#include <stdio.h>
#include <stdlib.h>

static long num_steps = 100000;
double step;
void main (int argc, char const *argv[])
{
	// int num_threads =  omp_get_max_threads();
	int num_threads = atoi(argv[1]);

	int i, nthreads; double pi, sum[num_threads];
	step = 1.0/(double) num_steps;
	omp_set_num_threads(num_threads);
	#pragma omp parallel
	{
		int i, id,nthrds;
		double x;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		if (id == 0) nthreads = nthrds;
		for (i=id, sum[id]=0.0;i< num_steps; i=i+nthrds) {
			x = (i+0.5)*step;
			sum[id] += 4.0/(1.0+x*x);
		}
		printf("ID = %i \n", id);

	}
	for(i=0, pi=0.0;i<nthreads;i++)pi += sum[i] * step;
	printf("Valor de Pi = %f \n", pi);
	printf("cantidad de hilos %i \n",num_threads);
}
