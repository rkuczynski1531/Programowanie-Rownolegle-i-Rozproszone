#include <stdio.h>
#include <math.h>
#include "mpi.h"

double funkcjaPodcalkowa(double x)
{
	return pow(x, 2);
}

double licz(double ai, double bi){
	double punkt = 0;
	double n = 30.0;
	double wynik = 0;
    for(int i = 1; i < n; i++) {
        punkt = ai + (i/n) * (bi - ai);
        wynik += funkcjaPodcalkowa(punkt);
    }
    wynik += funkcjaPodcalkowa(ai)/2 + funkcjaPodcalkowa(bi)/2;
    wynik = wynik * (bi-ai)/n;
    return wynik;
}

int main(int argc, char **argv)
{
    int nr_procesu, l_procesow, tag = 20;
    MPI_Status status;           
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &nr_procesu);
    MPI_Comm_size(MPI_COMM_WORLD, &l_procesow);
    double wynik = 0;
    double a = 1.0, b = 10.0;
    double ai, bi;
    double roznica = b - a;
    
    if(nr_procesu == 0){
	    ai = a + roznica / l_procesow * nr_procesu;
	    bi = a + roznica / l_procesow * (nr_procesu + 1);
		wynik += licz(ai, bi);  
		MPI_Send(&wynik, 1, MPI_DOUBLE, nr_procesu+1, tag, MPI_COMM_WORLD);
		printf("Proces nr. %d, aktualna wartosc przyblizenia: %f \n", nr_procesu, wynik);	
    }

    if(nr_procesu > 0 && nr_procesu < l_procesow-1){
	    ai = a + roznica / l_procesow * nr_procesu;
	    bi = a + roznica / l_procesow * (nr_procesu + 1);
		MPI_Recv(&wynik, 1, MPI_DOUBLE, nr_procesu-1, tag, MPI_COMM_WORLD, &status);
		wynik += licz(ai, bi); 
		printf("Proces nr. %d, aktualna wartosc przyblizenia: %f \n", nr_procesu, wynik);
		MPI_Send(&wynik, 1, MPI_DOUBLE, nr_procesu+1, tag, MPI_COMM_WORLD);
    }

    if(nr_procesu == l_procesow-1){
	    ai = a + roznica / l_procesow * nr_procesu;
	    bi = a + roznica / l_procesow * (nr_procesu + 1);
		MPI_Recv(&wynik, 1, MPI_DOUBLE, nr_procesu-1, tag, MPI_COMM_WORLD, &status);
		wynik += licz(ai, bi); 
		printf("Proces nr. %d, aktualna wartosc przyblizenia: %f \n", nr_procesu, wynik);		
    }

    MPI_Finalize();
    return 0;
}
