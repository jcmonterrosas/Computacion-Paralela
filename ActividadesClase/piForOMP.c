//%cflags:-fopenmp -lm -D_DEFAULT_SOURCE
//gcc pi_omp.c -o pi_omp -fopenmp
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>


#define ITERATIONS 2e09
#define THREADS 16

int main()
{
    int i, threads = THREADS;
    
    struct timeval tval_before, tval_after, tval_result;

    gettimeofday(&tval_before, NULL);
    
    double pi = 0.0;
    
    #pragma omp parallel num_threads(threads)
    {
	#pragma omp parallel for reduction (+:pi) 
	for(i = 0; i < ITERATIONS; i++){
		pi = pi + (double)(4.0/ ((i*2)+1));
		i++;
		pi = pi - (double)(4.0 / ((i*2)+1));
	} 
    }
    gettimeofday(&tval_after, NULL);

    timersub(&tval_after, &tval_before, &tval_result);

    printf("Time elapsed: %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    
    printf("\npi: %2.10f   \n", pi);
}
