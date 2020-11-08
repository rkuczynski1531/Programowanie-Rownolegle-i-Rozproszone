import java.util.Scanner;

public class PRiRLab3Zad2 {
    static int ilosc_taksowek = 10;
    static int ilosc_miejsc = 5;
    static PostojTaksowek postoj;
    public PRiRLab3Zad2(){}

    public static void main(String a[]){
        Scanner scan = new Scanner(System.in);
        System.out.println("Podaj ilosc miejsc parkingowych");
        int n = scan.nextInt();
        System.out.println("Podaj ilosc taksowek");
        int t = scan.nextInt();
        postoj = new PostojTaksowek(n, t);
        for(int i = 0; i < t; i++)
            new Taksowka(i, 2000, postoj).start();
    }
}
