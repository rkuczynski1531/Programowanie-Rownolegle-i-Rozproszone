#include <stdio.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int nr_procesu, l_procesow, tag = 20;
    MPI_Status status;           
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &nr_procesu);
    MPI_Comm_size(MPI_COMM_WORLD, &l_procesow);
    double wynik = 0;
    int n = 1;
    
    if(nr_procesu == 0){
		wynik += 4 * pow(-1, n - 1) / (2 * n - 1);
		printf("Proces nr. %d, aktualna wartosc przyblizenia: %f \n", nr_procesu, wynik);
		n += 1;
	    MPI_Send(&wynik, 1, MPI_DOUBLE, nr_procesu+1, tag, MPI_COMM_WORLD);
		MPI_Send(&n, 1, MPI_INT, nr_procesu+1, tag, MPI_COMM_WORLD);
    }

    if(nr_procesu > 0 && nr_procesu <= l_procesow-1){
		MPI_Recv(&wynik, 1, MPI_DOUBLE, nr_procesu-1, tag, MPI_COMM_WORLD, &status);
		MPI_Recv(&n, 1, MPI_INT, nr_procesu-1, tag, MPI_COMM_WORLD, &status);
		wynik += 4 * pow(-1, n - 1) / (2 * n - 1);
		printf("Proces nr. %d, aktualna wartosc przyblizenia: %f \n", nr_procesu, wynik);
		n += 1;
		
		if(nr_procesu != l_procesow-1){
			MPI_Send(&wynik, 1, MPI_DOUBLE, nr_procesu+1, tag, MPI_COMM_WORLD);
			MPI_Send(&n, 1, MPI_INT, nr_procesu+1, tag, MPI_COMM_WORLD);
		}
    }
    
    MPI_Finalize();
    return 0;
}
