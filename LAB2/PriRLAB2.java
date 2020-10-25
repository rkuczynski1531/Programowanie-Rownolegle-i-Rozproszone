import java.util.ArrayList;
import java.util.Scanner;

public class PriRLAB2 {

    public static void main(String[] args) throws InterruptedException {
        double a = 1.1;
        double b = 2.1;
        double wynik = 0;
        Scanner scan = new Scanner(System.in);
        double watki;

        double roznica = b - a;
        double ai, bi;
        boolean exit = false;

        while(!exit) {
            wynik = 0;
            System.out.println("Wybierz metode (wpisz numer): \n1. Trapezow \n" + "2. Simpsona \n" + "3. Prostokatow \n" + "4. Wyjscie");
            int nr = scan.nextInt();
            switch (nr) {
                case 1:
                    System.out.println("Podaj ilosc watkow: ");
                    watki = scan.nextInt();
                    for (int i = 0; i < watki; i++) {
                        if (i != 0)
                            ai = a + roznica / watki * i;
                        else
                            ai = a + roznica / watki * i;
                        bi = a + roznica / watki * (i + 1);
                        M_trapezow watek = new M_trapezow(ai, bi);
                        watek.start();
                        watek.join();
                        wynik += watek.wynik;
                    }
                    System.out.println(wynik);
                    break;
                case 2:
                    System.out.println("Podaj ilosc watkow: ");
                    watki = scan.nextInt();
                    for (int i = 0; i < watki; i++) {
                        if (i != 0)
                            ai = a + roznica / watki * i;
                        else
                            ai = a + roznica / watki * i;
                        bi = a + roznica / watki * (i + 1);
                        M_simpsona watek = new M_simpsona(ai, bi);
                        watek.start();
                        watek.join();
                        wynik += watek.wynik;
                    }
                    System.out.println(wynik);
                    break;
                case 3:
                    System.out.println("Podaj ilosc watkow: ");
                    watki = scan.nextInt();
                    for (int i = 0; i < watki; i++) {
                        if (i != 0)
                            ai = a + roznica / watki * i;
                        else
                            ai = a + roznica / watki * i;
                        bi = a + roznica / watki * (i + 1);
                        M_prostokatow watek = new M_prostokatow(ai, bi);
                        watek.start();
                        watek.join();
                        wynik += watek.wynik;
                    }
                    System.out.println(wynik);
                    break;
                case 4:
                    exit = true;
                    break;
                default:
                    System.out.println("Nie ma takiej opcji. Wpisz numer od 1 do 3: ");
                    break;
            }
        }
    }
}
