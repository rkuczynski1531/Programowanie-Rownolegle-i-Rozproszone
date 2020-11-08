import java.util.Scanner;
import java.util.concurrent.Semaphore;

public class PRiRLab3Zad1 {
    public static void main(String a[]){
        Scanner s = new Scanner(System.in);
        System.out.println("Podaj ilosc filozofow: ");
        int n = s.nextInt();
        boolean exit = false;
        while(!exit){
            System.out.println("Wybierz wariant: \n1.Problem 5 filozofow\n2.Problem ucztujących filozofów z niesymetrycznym\n" + "sięganiem po widelce\n3.Rzut monety w rozwiązaniu problemu ucztujących Filozofów\n4.Wyjscie");
            int wariant = s.nextInt();
            switch(wariant){
                case 1:
                    for(int i = 0; i<n; i++){
                        Filozof1.widelec[i] = new Semaphore(1);
                    }
                    for(int i = 0; i < n; i++){
                        new Filozof1(i, n).start();
                    }
                    exit = true;
                    break;
                case 2:
                    for(int i = 0; i<n; i++){
                        Filozof2.widelec[i] = new Semaphore(1);
                    }
                    for(int i = 0; i < n; i++){
                        new Filozof2(i, n).start();
                    }
                    exit = true;
                    break;
                case 3:
                    for(int i = 0; i<n; i++){
                        Filozof3.widelec[i] = new Semaphore(1);
                    }
                    for(int i = 0; i < n; i++){
                        new Filozof3(i, n).start();
                    }
                    exit = true;
                    break;
                case 4:
                    exit = true;
                    break;
                default:
                    System.out.println("Nie ma takiej opcji. Wpisz numer od 1 do 4: ");
                    break;
            }
        }
    }
}
