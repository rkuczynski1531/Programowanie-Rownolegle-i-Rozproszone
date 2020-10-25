class M_trapezow extends Thread {
    double a;
    double b;

    double wynik;
    double n = 20.0;
    public M_trapezow(double a, double b){
        this.a = a;
        this.b = b;

    }

    double funkcjaPodcalkowa(double x) {
        return Math.sin(0.4 * Math.pow(x, 2) - 2.1) / Math.sqrt(1.1 * x + 0.3);
    }

    public void run(){

        double punkt = 0;
        for(int i = 1; i < n; i++) {
            punkt = a + (i/n) * (b - a);
            wynik += funkcjaPodcalkowa(punkt);
        }
        wynik += funkcjaPodcalkowa(a)/2 + funkcjaPodcalkowa(b)/2;
        wynik = wynik * (b-a)/n;
    }
}
