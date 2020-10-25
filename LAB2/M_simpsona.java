import java.util.ArrayList;

public class M_simpsona extends Thread {
    double a, b;
    ArrayList<Double> x = new ArrayList<>();
    ArrayList<Double> t = new ArrayList<>();
    double wynik;
    double n = 20.0;
    public M_simpsona(double a, double b) {
        this.a = a;
        this.b = b;
    }

    public void run(){

        for(int i = 0; i <= n; i++) {
            x.add(a + (i/n) * (b - a));
        }

        for(int i = 0; i < n; i++) {
            t.add((x.get(i+1) + x.get(i)) / 2);
        }

        wynik = funkcjaPodcalkowa(a) + funkcjaPodcalkowa(b);

        double suma = 0;
        double suma2 = 0;

        for(int i = 0; i < n; i++) {
            suma += funkcjaPodcalkowa(t.get(i));
        }

        suma *= 4;

        for(int j = 1; j < n; j++) {
            suma2 += funkcjaPodcalkowa(x.get(j));
        }

        suma2 *= 2;

        wynik += suma + suma2;

        wynik *=  H(x)/3;
    }

    double H(ArrayList<Double> x) {
        return (x.get(x.size() - 1) - x.get(x.size() - 2))/2;
    }

    double funkcjaPodcalkowa(double x) {
        return Math.sin(0.4 * Math.pow(x, 2) - 2.1) / Math.sqrt(1.1 * x + 0.3);
    }
}
