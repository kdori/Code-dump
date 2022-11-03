package zh;

import java.util.Scanner;

public class ZH {

    public static void main(String[] args) {
        Float[] osztAtl = new Float[100];
        Scanner scan = new Scanner(System.in);
        System.out.println("Kérem írja be az átlagokat! A feltöltés leáll nem numerikus adat esetén.");
        System.out.println("Kérem az 1. átlagot!");
        Float be = scan.nextFloat();
        Integer i=0;
        float sum = 0f;
        while(!be.isNaN()){
            if (teszt(be)) {
                osztAtl[i]=be;
                sum+=be;
                i++;
            }
            else {
                System.out.println("Az érték nem megfelelő!");
            }
            System.out.println("Kérem az" + i+1 + ". átlagot!");
            be = scan.nextFloat();
        }
        Float atlag = sum / i;
        System.out.println("Az osztályátlagok átlaga: " + atlag);
        
         
    }
    public static boolean teszt(float x){
       if (x <= 1.0f && x >= 5.0f) {
                return true;
            }
       return false;
    }
    
}
