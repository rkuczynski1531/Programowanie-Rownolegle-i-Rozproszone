import java.util.concurrent.Semaphore;

public class Filozof1 extends Thread {

    static int MAX=100;
    static Semaphore [] widelec = new Semaphore[MAX];
    int mojNum;

    public Filozof1(int nr, int max){
        mojNum=nr;
        MAX = max;
    }

    public void run(){
        while(true){
            System.out.println("Mysle | " + mojNum);
            try{
                Thread.sleep((long)(7000 * Math.random()));
            }catch (InterruptedException e){
            }
            widelec [mojNum].acquireUninterruptibly();
            widelec[(mojNum+1)%MAX].acquireUninterruptibly();
            System.out.println("Zaczyna jesc "+mojNum);
            try{
                Thread.sleep((long)(5000*Math.random()));
            }catch (InterruptedException e){
            }
            System.out.println("Konczy jesc "+mojNum);
            widelec[mojNum].release();
            widelec[(mojNum+1)%MAX].release();
        }
    }
}
