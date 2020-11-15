#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "err.h"
double f(double x)
{

	return 4*x-6*x+5;
}

double Pole(int i)
{
    int a, b, n, tmp, zarodek;
    time_t tt;
    do{
        zarodek = time(&tt);
        srand(zarodek + i);
        i++;
        a = rand();
        b = rand();
        }while(a == b);
    n = rand()%50;
    if(a > b){
        tmp = b;
        b = a;
        a = tmp;
    }
    printf("a = %d, b = %d, n = %d\n", a, b, n);
	double h = (b-a)/(double)n; 
	double S = 0.0; 
	double podstawa_a = f(a), podstawa_b;

	for(int i=1;i<=n;i++)
	{
		podstawa_b = f(a+h*i);
		S += (podstawa_a+podstawa_b);
		podstawa_a = podstawa_b;
	}
	return S*0.5*h;
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
            printf("Wynik calki to: %f\n", Pole(i));
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
