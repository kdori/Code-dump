package binfajl;

import java.io.IOException;
import java.io.RandomAccessFile;
import static java.lang.System.err;
import java.util.Scanner;


public class Binfajl {

    public static void main(String[] args) {
       float szam;
        try{
            RandomAccessFile file = new RandomAccessFile("Teszt.txt", "rw");
            System.out.println("Kérék egy lebegőpontos számot!");
            Scanner scan = new Scanner(System.in);
            szam = scan.nextFloat();
            while(szam!=0){
                file.writeFloat(szam);
                System.out.println("Kérék egy lebegőpontos számot!");
                szam = scan.nextFloat();
            }
            file.seek(0);
            long poz = 1;
            while (poz < file.length()){
                System.out.println(file.readFloat());
                file.readFloat();
                poz++;
            }
        }
        catch (IOException error){
            err.println("Fájl hiba - " + error.getMessage());
        }
    }
    
}
