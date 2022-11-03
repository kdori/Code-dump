using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AlgoAdsz2017_MergeSort
{
    public partial class Form1 : Form
    {
        //ITT KEZDŐDIK a program releváns része

        int N;
        int[] scores;
        string[] names;

        void mergeSort( int bottom, int top )
        {
            //AZ ÖSSZEFSÜLŐ RENDEZÉS ALGORITMUSA
            //A "scores" tömb tárolja a számsorozatot
            //A "names" tömb tárolja a számokhoz tartozó neveket
            //Az "N" változó tárolja, hogy jelenleg hány elem szerepel a tömbökben
            //A "scores[i]" kifejezés az "i"-edik indexű számra hivatkozik
            //A "names[i]" kifejezés az "i"-edik indexű névre hivatkozik
            //A "mergeSort(x,y)" kifejezés: a függvény hívása "x" és "y" paraméterekkel

            int[] iTmp = new int[N]; //ideiglenes tömb egészek számára
            string[] sTmp = new string[N]; //ideiglenes tömb szövegek számára
            int m = 0;


            if (top - bottom > 0)
            {
                Console.WriteLine(bottom + " " + top);
                m = (bottom + top) / 2;
                mergeSort(bottom, m);
                mergeSort(m + 1, top);
                int i = bottom; int j = m+1;
                for (int k = bottom; k < top; k++)
                {

                    if (scores[i] > scores[j] && i <= m)
                    {
                        iTmp[k] = scores[i];
                        sTmp[k] = names[i];
                        i++;
                    }
                    else if (scores[i] < scores[j] && j <= top)
                    {
                        iTmp[k] = scores[j];
                        sTmp[k] = names[j];
                        j++;
                    }
                }
               

            }
            for (int l = bottom; l < top; l++)
            {
                scores[l] = iTmp[l];
                names[l] = sTmp[l];
            }


        }

        //EDDIG TART a program releváns része

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //Form's appearance
            Text = "Összefésülő rendezés";
            ClientSize = new Size(640, 480);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MinimizeBox = false;
            MaximizeBox = false;
            DoubleBuffered = true;

            //Initialize
            Random rand = new Random();
            timer = new Timer();
            timer.Interval = 100;
            timer.Tick += timerTick;

            scores = new int[100];
            names = new string[100];
            N = 10;

            names[0] = "Gipsz Jakab";
            names[1] = "Jóska Pista";
            names[2] = "Minta Mónika";
            names[3] = "Példa Péter";
            names[4] = "Sablon Sándor";
            names[5] = "Kovács Katinka";
            names[6] = "Horváth Heléna";
            names[7] = "Tóth Tódor";
            names[8] = "Varga Viktória";
            names[9] = "Takács Tímea";

            for (int i = 0; i < N; i++)
            {
                scores[i] = rand.Next(1, 90);
            }

            sorting();
            refreshList();
        }

        private void sorting()
        {
            Console.WriteLine("Rendezés előtt:");
            for (int i = 0; i < N; i++) Console.WriteLine(names[i] + ": "+scores[i]);
            Console.WriteLine("------");

            mergeSort(0,N-1);

            Console.WriteLine("Rendezés után:");
            for (int i = 0; i < N; i++) Console.WriteLine(names[i] + ": " + scores[i]);
            Console.WriteLine("======");
        }
        private void addRowToList( string name, int score )
        {
            int x = listView.Items.Count + 1;

            ListViewItem lvi = new ListViewItem( x.ToString()+"." );
            lvi.SubItems.Add(name);
            lvi.SubItems.Add(score.ToString());
            listView.Items.Add( lvi );
        }
        private Timer timer;
        private int animX;
        private void refreshList()
        {
            listView.Items.Clear();
            animX = 0;
            timer.Start();
        }
        private void timerTick(object sender, EventArgs e)
        {
            addRowToList( names[animX], scores[animX] );
            animX++;
            if (animX >= N) timer.Stop();
        }

        private void button_Click(object sender, EventArgs e)
        {
            int score;
            string name = inpName.Text;
            bool valid = Int32.TryParse(inpScore.Text, out score);

            if ( valid )
            {
                if (name.Trim().Length > 2)
                {
                    if (score >= 0 && score <= 100)
                    {
                        scores[N] = score;
                        names[N] = name;
                        N++;

                        sorting();
                        refreshList();

                        inpName.Clear();
                        inpScore.Clear();
                    }
                    else MessageBox.Show("A beírt érték min. 0, max. 100 lehet!");
                }
                else MessageBox.Show("Valós nevet adjon meg!");
            }
            else MessageBox.Show("A pontszám csak szám lehet!");
        }
    }
}
