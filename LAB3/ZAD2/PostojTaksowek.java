public class PostojTaksowek {
    static int POSTOJ_TAKSOWEK = 1;
    static int WYJAZD = 2;
    static int MIASTO = 3;
    static int KONIEC_JEZDZENIA = 4;
    static int STACJA_BENZYNOWA = 5;
    static int WYPADEK = 6;

    int ilosc_miejsc;
    int ilosc_zajetych;
    int ilosc_taksowek;

    PostojTaksowek(int ilosc_miejsc, int ilosc_taksowek){
        this.ilosc_miejsc = ilosc_miejsc;
        this.ilosc_taksowek = ilosc_taksowek;
        this.ilosc_zajetych = 0;
    }

    synchronized int wyjazd(int numer){
        ilosc_zajetych--;
        System.out.println("Taksowka nr. " + numer + " Wyjechala");
        return WYJAZD;
    }

    synchronized int zaparkuj(){
        try{
            Thread.currentThread().sleep(1000);
        }
        catch (Exception ie){
        }
        if (ilosc_zajetych < ilosc_miejsc){
            ilosc_zajetych++;
            System.out.println("Miejsce parkinkowe nr. " + ilosc_zajetych + " Jest zajete");
            return POSTOJ_TAKSOWEK;
        }
        else return KONIEC_JEZDZENIA;
    }

    synchronized void zmniejsz(){
        ilosc_taksowek--;
        System.out.println("WYPADEK");
        if(ilosc_taksowek == ilosc_miejsc) System.out.println("Ilosc taksowek taka sama jak ilosc miejsc");
    }
}
