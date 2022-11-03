using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AlgoAdsz2017_LZW
{
    public partial class Form1 : Form
    {
        //ITT KEZDŐDIK a program releváns része

        //Teszt: "abrakadabra", "blablabla", "ababcbababaaaaaaa"

        string[] dictionary;
        int dictSize;
        int[] code;
        int codeSize;

        string lzwDecompress()
        {
            //AZ LZW. KITÖMÖRÍTÉS ALGORITMUSA
            //Az "str" tárolja az aktuálisan felépülő szót
            //A "preC" tárolja a korábbi (a szótárban megtalálható) indexet
            //Az "actC" tárolja az aktuális szó szótárbeli indexét
            //A "ch" az aktuális szó első karaktere
            //A "dictionary[i]" a szótár "i"-edik indexű szava
            //A "dictSize" jelzi, mekkora jelenleg a szótár mérete
            //A "ch" karakter hozzáfűzése a szótár "x" indexű szavához: dictionary[x] + ch

            dictionaryInit();

            string str = "";
            int preC = code[0], actC;
            char ch = ' ';
            string output = "";
            for (int i = 1; i < codeSize; i++)
            {
                actC = code[i];
                str = dictionary[actC];
                if (dictSize > code[i])
                {
                    ch = Convert.ToChar(str[0]);
                }
                dictionary[dictSize] = dictionary[preC] + ch;
                preC = actC;
                dictSize++;
            }
            
            for (int i = 0; i < codeSize; i++)
            {
                output += dictionary[code[i]];
            }
            
            return output;
        }

        //EDDIG TART a program releváns része

        public Form1()
        {
            InitializeComponent();
        }

        void lzwCompress( string input )
        {
            dictionaryInit();

            string str = "";
            int aCode;
            char ch;

            codeSize = 0;
            str = input[0].ToString();

            for( int i=1; i<input.Length; i++ )
            {
                ch = input[i];
                aCode = getCode( str+ch );

                if (aCode != -1) str = str + ch;
                else
                {
                    aCode = getCode(str);
                    code[codeSize] = aCode;
                    codeSize++;

                    dictionary[dictSize] = str + ch;
                    dictSize++;

                    str = ch.ToString();
                }
            }
            aCode = getCode(str);
            code[codeSize] = aCode;
            codeSize++;
        }
        int getCode( string str )
        {
            int res = -1;

            for (int i = 0; i < dictSize; i++)
                if (dictionary[i] == str) return i;

            return res;
        }
        void dictionaryInit()
        {
            dictionary = new string[4096];
            for (dictSize = 0; dictSize < 26; dictSize++) dictionary[dictSize] = ((char)('a' + dictSize)).ToString();
        }
        void updateDictionary( int x )
        {
            if( x==1 ) listView1.Items.Clear();
            else listView2.Items.Clear();

            for( int i=0; i<dictSize; i++ )
            {
                ListViewItem lvi = new ListViewItem( i.ToString() );
                lvi.SubItems.Add( dictionary[i] );

                if (x == 1) listView1.Items.Add(lvi);
                else listView2.Items.Add(lvi);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //Form's appearance
            Text = "LZW. kitömörítés";
            ClientSize = new Size(700, 300);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MinimizeBox = false;
            MaximizeBox = false;
            DoubleBuffered = true;

            //Initialize
            code = new int[100];
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string str = inpInput.Text;

            if (str.Length>2)
            {
                bool valid = true;

                for (int i = 0; i < str.Length; i++) if (str[i] < 'a' || str[i] > 'z') valid = false;

                if (valid)
                {
                    lzwCompress(str);
                    updateDictionary(1);

                    txtCode.Text = "";
                    for (int i = 0; i < codeSize; i++) txtCode.Text += code[i].ToString() + " ";

                    str = lzwDecompress();
                    txtOutput.Text = str;

                    updateDictionary(2);
                }
                else MessageBox.Show("A beírt szöveg csak az angol ABC kisbetűiből állhat!");
            }
            else MessageBox.Show("A szöveg túl rövid!");
        }
    }
}
