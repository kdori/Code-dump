using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AlgoAdsz2017_Hash
{
    public partial class Form1 : Form
    {
        //ITT KEZDŐDIK a program releváns része

        int N;
        int[] ht;

        //A HASH-TÁBLA METÓDUSAI
        //A "ht" tömb tárolja a Hash-táblát
        //Az "N" változó tárolja a tábla méretét
        //A "ht[x]" kifejezés azt a "k" kulcsot jelenti, amelyet az "x" indexnek feleltet meg a Hash
        int hash( int k ) //Hash-függvény
        {
            int x = k % N;
            return x;
        }
        bool htInsert( int k ) //Beszúrás
        {
            int x = hash(k);
            int c = 0;
            int i = 0;
            while( c < N && ht[x + i] != 0)
            {
                i++;
                if (x + c == N - 1 )
                {
                    x = 0;
                    i = 0;
                }
                c++;
            }
            if (c < N)
            {
                ht[x + c] = k;
                return true;
            }
            else
            {
                return false;
            }
        }
        int htSearch( int k ) //Keresés
        {
            int x = 0;
            for (int i = 0; i < N; i++)
            {
                if (ht[i]==k)
                {
                    x = i;
                    break;
                }
            }
            if (ht[x] == k && x < N)
            {
                return x;
            }
            else
            {
                return -1;
            }
            
        }
        void htDel( int k ) //Törlés
        {
            int x = htSearch(k);
            if (x != -1)
            {
                ht[x] = -1;
            }
        }
        
        //EDDIG TART a program releváns része

        public Form1()
        {
            InitializeComponent();
        }

        private void refreshView()
        {
            tblHash.Items.Clear();
            tblCustomers.Items.Clear();

            ListViewItem lvi;

            for (int i = 0; i < N; i++)
            {
                String key = ht[i].ToString();
                if (ht[i] == 0) key = "-";
                else if (ht[i] == -1) key = "X";

                lvi = new ListViewItem( key );
                lvi.SubItems.Add( i.ToString() );
                tblHash.Items.Add( lvi );

                if (ht[i] > 0)
                {
                    lvi = new ListViewItem(key);
                    lvi.SubItems.Add(names[i]);
                    tblCustomers.Items.Add(lvi);
                }
            }
        }
        private void htLog()
        {
            for (int i = 0; i < N; i++) Console.WriteLine("[" + i + "]=" + ht[i]);
            Console.WriteLine("======");
        }

        string[] names;

        private void Form1_Load(object sender, EventArgs e)
        {
            //Form's appearance
            Text = "Hash-tábla";
            ClientSize = new Size(700, 300);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MinimizeBox = false;
            MaximizeBox = false;
            DoubleBuffered = true;

            //Initialize
            N = 7;
            names = new string[N];
            ht = new int[N];
            for (int i = 0; i < N; i++) ht[i] = 0;

            addNew( "Aladár", 123 );
            addNew( "Béla", 256 );
            addNew( "Csongor", 1024 );
            refreshView();
        }

        private void addNew( string name, int key )
        {
            bool ok = htInsert(key);

            if( ok )
            {
                int x = htSearch(key);

                if (x != -1)
                {
                    names[x] = name;
                }
            }
            else MessageBox.Show("A tábla megtelt!");
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            string name = inpName.Text.Trim();
            int key;
            bool valid = Int32.TryParse( inpKey.Text, out key );
            string error = null;

            if (name.Length < 3) error = "Valós nevet adjon meg!";
            else if (!valid) error = "Az azonosító-kulcs csak szám lehet!";
            else if (key < 1) error = "A kulcs legyen pozitív szám!";
            else if (key>10000000) error = "Azért ennél legyen kisebb szám a kulcs!";

            if( error==null )
            {
                int x = htSearch(key);
                if (x != -1) error = "Ez az azonosító-kulcs már létezik!";
                else
                {
                    addNew( name, key );
                    refreshView();
                    inpName.Clear();
                    inpKey.Clear();
                }
            }

            if (error != null)  MessageBox.Show(error);
        }

        private void btnDel_Click(object sender, EventArgs e)
        {
            int key;
            bool valid = Int32.TryParse(inpKey.Text, out key);
            string error = null;
            
            if (!valid) error = "Az azonosító-kulcs csak szám lehet!";
            else if (key < 1) error = "A kulcs legyen pozitív szám!";
            else if (key > 10000000) error = "Azért ennél legyen kisebb szám a kulcs!";

            if (error == null)
            {
                int x = htSearch(key);
                if (x == -1) error = "Ez az azonosító-kulcs nem létezik!";
                else
                {
                    htDel(key);
                    refreshView();
                }
            }

            if (error != null) MessageBox.Show(error);
        }
    }
}
