#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "mpi.h"
#define REZERWA 500
#define POSTOJ_TAKSOWEK 1
#define WYJAZD 2
#define MIASTO 3
#define KONIEC_JEZDZENIA 4
#define STACJA_BENZYNOWA 5
#define WYPADEK 6
#define TANKUJ 1000
int paliwo = 1000, energia = 1000;
int PARKUJ=1, NIE_PARKUJ=0;
int liczba_procesow;
int nr_procesu;
int ilosc_samochodow;
int ilosc_miejsc=5;
int ilosc_zajetych_miejsc=0;
int tag=1;
int wyslij[2];
int odbierz[2];
MPI_Status mpi_status;

void Wyslij(int nr_samochodu, int stan)
{
	wyslij[0]=nr_samochodu;
	wyslij[1]=stan;
	MPI_Send(&wyslij, 2, MPI_INT, 0, tag, MPI_COMM_WORLD);
	sleep(1);
}

void Postoj(int liczba_procesow){
	int nr_samochodu,status;
	ilosc_samochodow = liczba_procesow - 1;
	printf("Jest %d miejsc parkingowych\n", ilosc_miejsc);
	sleep(2);
	while(ilosc_miejsc<=ilosc_samochodow){
		MPI_Recv(&odbierz,2,MPI_INT,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD, &mpi_status);
		nr_samochodu=odbierz[0];
		status=odbierz[1];
		if(status==1){
			printf("Samochod %d stoi na postoju\n", nr_samochodu);
		}
		if(status==2){
			printf("Samochod %d wyjezdza na miasto z miejsca nr %d\n", nr_samochodu, ilosc_zajetych_miejsc);
			ilosc_zajetych_miejsc--;
		}
		if(status==3){
			printf("Samochod %d jezdzi po miescie\n", nr_samochodu);
		}
		if(status==4){
			if(ilosc_zajetych_miejsc<ilosc_miejsc){
				ilosc_zajetych_miejsc++;
				MPI_Send(&PARKUJ, 1, MPI_INT, nr_samochodu, tag, MPI_COMM_WORLD);
			}
			else{
				MPI_Send(&NIE_PARKUJ, 1, MPI_INT, nr_samochodu, tag, MPI_COMM_WORLD);
			}
		}
		if(status == 5){
			printf("Samochod %d tankuje na stacji benzynowej\n", nr_samochodu);
		}
		if(status==6){
			ilosc_samochodow--;
			printf("Ilosc samochodow %d\n", ilosc_samochodow);
		}
	}
	printf("Program zakonczyl dzialanie:)\n");
}

void Samochod(){
	int stan,suma,i;
	stan=MIASTO;
	while(1){
		if(stan==1){
			if(rand()%2==1){
				stan=WYJAZD;
				energia=1000;
				printf("Jestem gotowy do jazdy, samochod %d\n",nr_procesu);
				Wyslij(nr_procesu,stan);
			}
			else{
				Wyslij(nr_procesu,stan);
			}
		}
		else if(stan==2){
			printf("Wyjechalem, samochod %d\n",nr_procesu);
			stan=MIASTO;
			Wyslij(nr_procesu,stan);
		}
		else if(stan==3){
			paliwo-=rand()%500; 
			energia-=rand()%500;
			if(energia <= 500){
                stan = KONIEC_JEZDZENIA;
                printf("samochod %d, jestem zmeczony\n",nr_procesu);
                Wyslij(nr_procesu, stan);
            }
			else if(paliwo<=REZERWA){
				stan=STACJA_BENZYNOWA;
				printf("samochod %d, powinienem zatankowac\n",nr_procesu);
				Wyslij(nr_procesu, stan);
			}
			else{
				for(i=0; rand()%10000;i++);
			}
		}
		else if(stan==4){
			int temp;
			MPI_Recv(&temp, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &mpi_status);
			if(temp==PARKUJ){
				stan=POSTOJ_TAKSOWEK;
				printf("zaparkowalem, samochod %d\n", nr_procesu);
			}
			else
				{
				energia-=rand()%500;
				paliwo-=rand()%500;
				if(energia <= 0){
					stan = WYPADEK;
					printf("Mialem wypadek, samochod %d\n", nr_procesu);
					Wyslij(nr_procesu,stan);
				}
				else if(paliwo>0){
					stan=STACJA_BENZYNOWA;
					Wyslij(nr_procesu,stan);
				}
				else{
					stan=WYPADEK;
					printf("Mialem wypadek\n");
					Wyslij(nr_procesu,stan);
					return;
				}
			}
		}
		else if(stan == 5){
			printf("Samochod %d, jestem na stacji\n", nr_procesu);
			paliwo = TANKUJ;
			stan = MIASTO;
			Wyslij(nr_procesu,stan);
		}
	}
}
int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&nr_procesu);
	MPI_Comm_size(MPI_COMM_WORLD,&liczba_procesow);
	srand(time(NULL));
	if(nr_procesu == 0)
		Postoj(liczba_procesow);
	else 
		Samochod();
	MPI_Finalize();
	return 0;
}
