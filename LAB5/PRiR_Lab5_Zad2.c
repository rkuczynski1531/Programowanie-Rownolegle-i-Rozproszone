#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "err.h"
#include <math.h>
double Leibniz(int i)
{
    int n, zarodek;
    time_t tt;
    zarodek = time(&tt);
    srand(zarodek + i);
    n = rand()% (5000 + 1 - 100) + 100;
    printf("n = %d\n", n);
    double wynik;
    for(int j = 1; j <= n; j++){
        wynik += pow(-1, j - 1)/(2 * j - 1);
    }
    wynik *= 4;

	return wynik;
}

int main ()
{
 pid_t pid;
 int i, p;
 printf("Podaj ilosc procesow: ");
 scanf("%d", &p);

 printf("Moj PID = %d\n", getpid());

 for (i = 1; i <= p; i++){
    switch (pid = fork()) {
        case -1:
            perror("Error in fork\n");
        case 0:
            printf("Jestem procesem potomnym. Moj PID = %d\n", getpid());
            printf("Wynik przyblizenia to: %f\n", Leibniz(i));

            return 0;

        default:
        printf("Jestem procesem macierzystym. Moj PID = %d\n", getpid());


    }
 }
 for (i = 1; i <= p; i++)
    if (wait(0) == -1)
        perror("Error in wait\n");
 return 0;

}
