public class M_prostokatow extends Thread {
    double a;
    double b;

    double wynik;
    int n = 100;
    public M_prostokatow(double a, double b){
        this.a = a;
        this.b = b;
    }

    double funkcjaPodcalkowa(double x) {
        return Math.sin(0.4 * Math.pow(x, 2) - 2.1) / Math.sqrt(1.1 * x + 0.3);
    }

    public void run(){
        wynik = 0;
        double dx = (b - a) / n;
        for(int i = 1; i <= n; i++)
            wynik += funkcjaPodcalkowa(a + i * dx);
        wynik *= dx;
    }
}
