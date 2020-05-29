// mpicc piReduceMPI.c -o piReduceMPI 
// mpirun -np 4 piReduceMPI

#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <math.h>

#define ITERATIONS 2e09

int calcPI(double *pi, int ID, int numprocs){
    int init, end, i;
    printf("actual process is %i \n", ID);
    init = (ITERATIONS/numprocs) * ID;
    end = (ITERATIONS/numprocs) + 1;

	for(i = init; i < end; i++){
		*pi = *pi + (double)(4.0/ ((i*2)+1));
		i++;
		*pi = *pi - (double)(4.0 / ((i*2)+1));
	} 
}

int main(int argc, char *argv[])
{
    int done = 0, n, processId, numprocs, I, rc, i;
    double local_pi, global_pi, h;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &processId);
    if (processId == 0) printf("Lauching with %i process\n", numprocs);
    local_pi = 0.0;
    global_pi = 0.0;

    calcPI(&local_pi, processId, numprocs);

    MPI_Reduce(&local_pi, &global_pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(processId == 0) printf("pi is approximately %.16f \n", global_pi);
    MPI_Finalize();
    return 0;
}