import java.util.Random;

public class Taksowka extends Thread {
    static int POSTOJ_TAKSOWEK = 1;
    static int WYJAZD = 2;
    static int MIASTO = 3;
    static int KONIEC_JEZDZENIA = 4;
    static int STACJA_BENZYNOWA = 5;
    static int WYPADEK = 6;
    static int TANKUJ = 1000;
    static int REZERWA = 500;

    int numer, paliwo = 1000, energia = 1000, stan;
    PostojTaksowek p;
    Random rand;
    boolean wyjscie = false;
    public Taksowka(int numer, int paliwo, PostojTaksowek p){
        this.numer = numer;
        this.paliwo= paliwo;
        this.stan = MIASTO;
        this.p = p;
        rand = new Random();
    }

    public void run(){
        while(wyjscie == false){
            if(stan == POSTOJ_TAKSOWEK){
                energia = 1000;
                if(rand.nextInt(2) == 1){
                    stan = WYJAZD;
                    System.out.println("Na postoju, taksowka nr. " + numer + " wyjezdza");
                    stan = p.wyjazd(numer);
                }
                else{
                    System.out.println("Taksowka nr " + numer + " Postoje jesszcze troche");
                }
            }
            else if(stan == WYJAZD){
                System.out.println("wyjechalem, taksowka nr. "+ numer);
                stan = MIASTO;
            }
            else if(stan == MIASTO){
                paliwo -= rand.nextInt(500);
                energia -= rand.nextInt(500);
                System.out.println("Taksowka "+ numer + " na miescie");
                if(energia <= 500){
                    stan = KONIEC_JEZDZENIA;
                }
                else if(paliwo <= REZERWA){
                    stan = STACJA_BENZYNOWA ;
                }
                else try {
                    sleep(rand.nextInt(1000));
                }
                catch (Exception e){
                }
            }
            else if(stan == KONIEC_JEZDZENIA){
                System.out.println("Taksowka nr. " + numer + " chcialaby zaparkowac, energia: " + energia);
                stan = p.zaparkuj();
                if(stan == KONIEC_JEZDZENIA){
                    energia -= rand.nextInt(500);
                    if(energia <= 0) stan = WYPADEK;
                    else if(paliwo <= 0){
                        paliwo -= rand.nextInt(500);
                        System.out.println("REZERWA " + paliwo);
                        if (paliwo <= 0) stan = STACJA_BENZYNOWA;
                    }
                }
            }
            else if(stan == STACJA_BENZYNOWA){
                System.out.println("Taksowka nr. " + numer + " tankuje samochod");
                paliwo = TANKUJ;
                try {
                    sleep(rand.nextInt(1000));
                } catch (InterruptedException e) {
                }
                stan = MIASTO;
            }
            else if (stan == WYPADEK){
                System.out.println("WYPADEK taksowki nr. " + numer);
                p.zmniejsz();
                wyjscie = true;
            }
        }
    }
}
