package ablak;
import java.awt.GridLayout;
import static java.lang.System.out;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.io.File;
import java.io.PrintStream;
import java.io.IOException;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class Ablak {
    public static void main(String[] args) {
    Beolvas be = new Beolvas();
    Kiír ki = new Kiír();
    ki.Ki();
    }
}

class Beolvas{
    public Beolvas(){
    Scanner billentyu = new Scanner (System.in, "ISO8859_2");
    String nev;
    Integer jegy;
        try{
            try (PrintStream file = new PrintStream("Fájl.txt")) {
            out.print("Kérek egy nevet: ");
            nev = billentyu.nextLine();
                while(nev.length()!=0){
                out.print("Kérek egy programozás érdemjegyet: ");
                jegy = billentyu.nextInt();  
                file.printf("%s-%d\n", nev, jegy);
                out.print("Kérek egy nevet: ");
                nev = billentyu.next();
                }
            }
        }
        catch (IOException error) {
        System.err.println("Hiba: " + error.getMessage());
        }
    }
}

class Kiír extends JFrame {
    public void Ki() {
        String sor;
        int sorok=0;
        StringTokenizer token;
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        try (Scanner file = new Scanner(new File("Fájl.txt"))) {
            while(file.hasNext()) {
                sor = file.nextLine();
                sorok++;
                token = new StringTokenizer(sor, "-");
                add(new JLabel(" " + (String) token.nextElement()));
                add(new JLabel((String) token.nextElement()));
            }
        file.close();
        }
        catch (IOException error) {
            System.err.println("Hiba: " + error.getMessage());
        }
        finally{
                setTitle("Jegyek");
                setLayout(new GridLayout(sorok, 3, 200, 30));
                pack();
                setVisible(true);
            }
        }
}
