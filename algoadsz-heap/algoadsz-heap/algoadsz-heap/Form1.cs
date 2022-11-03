using System;
using System.Drawing;
using System.Windows.Forms;

namespace algoadsz_heap
{
    public partial class Form1 : Form
    {
        //ITT KEZDŐDIK a program releváns része

        int N;
        int[] heap;

        //a "heap" tömb tárolja a kupac elemeit (a megfelelő sorrendben)
        //az "N" a kupac elemeinek számát tárolja
        //a "heapRestore(x)" a kupac "x" indexű eleméből kiinduló javítást végzi
        //a "heapDel(x)" a kupac "x" indexű elemét távolítja el
        //a "heapInsert(v)" beszúr egy új "v" számot a kupacba

        void heapRestore(int x)
        {
            //KUPAC HELYREÁLLÍTÁSA
            int Ni = 0;
            if (x >= 0 && x < N)
            {
                if (x - 1 % 2 == 0)
                {
                    if (heap[x] > heap[x--])
                    {
                        Ni = x;
                    }
                    else
                    {
                        Ni = x--;
                    }
                }
                else
                {
                    Ni = x;
                }
                if (heap[(x-1)/2]<=heap[Ni])
                {
                    int csere = heap[(x - 1) / 2];
                    heap[(x - 1) / 2] = heap[Ni];
                    heap[Ni] = csere;
                }
                if ((x - 1) / 2 >= 0)
                {
                    x = (x - 1) / 2;
                    heapRestore(x);
                }
               
            }
            



        }
        void heapDel(int x)
        {
            //ELEM TÖRLÉSE A KUPACBÓL
            int csere = heap[N-1];
            heap[N - 1] = heap[x];
            heap[x] = csere;
            
            N--;
            heapRestore(x);
        }
        void heapInsert(int v)
        {
            //ÚJ ELEM BESZÚRÁSA A KUPACBA
            N++;
            heap[N - 1] = v;
            heapRestore(N-1);
        }

        //EDDIG TART a program releváns része

        public Form1()
        {
            InitializeComponent();
        }

        Display display;
        private int[] numbers;
        private int nC;

        private void printHeap()
        {
            if (N > 0)
            {
                Console.WriteLine("A kupac elemei:");

                int sep = 0;
                int block = 1;

                for (int i = 0; i < N; i++)
                {
                    Console.Write(heap[i] + " ");
                    if (i == sep)
                    {
                        block *= 2;
                        sep += block;
                        Console.Write("| ");
                    }
                    else
                    if (i % 2 == 0) Console.Write(", ");
                }
                Console.WriteLine("");
                Console.WriteLine("---");
            }
            else Console.WriteLine("A kupac üres");
        }
        private void printNumbers()
        {
            Console.WriteLine("A generált számok:");

            for (int i = 0; i < nC; i++) Console.Write(numbers[i] + " ");
            Console.WriteLine("");
            Console.WriteLine("---");
        }
        private void fillHeap()
        {
            N = 0;
            for (int i = 0; i < nC; i++) heapInsert(numbers[i]);

            if (N < 1)
            {
                for (int i = 0; i < nC; i++) heap[i] = numbers[i];
                N = nC;
            }
            display.setModel(heap, nC);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //Form's appearance
            Text = "Kupacrendezés";
            ClientSize = new Size(620, 480);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MinimizeBox = false;
            MaximizeBox = false;
            DoubleBuffered = true;

            display = new Display(this);
            display.Width = 600;
            display.Height = 400;
            display.Left = 10;
            display.Top = 10;

            //Initialize
            Random rand = new Random();

            numbers = new int[256];
            nC = 0;
            for (int i = 0; i < 9; i++) numbers[nC++] = rand.Next(1, 90);
            printNumbers();

            heap = new int[256];
            fillHeap();
            printHeap();
        }

        private void addBtn_Click(object sender, EventArgs e)
        {
            if (N < 15)
            {
                int number;
                bool valid = Int32.TryParse(inpNew.Text, out number);

                if (valid)
                {
                    if (number >= 1 && number <= 99)
                    {
                        Console.WriteLine("Insert: " + number);
                        heapInsert(number);
                        printHeap();
                        display.setModel(heap, N);
                    }
                    else MessageBox.Show("A beírt érték min. 1, max. 99 lehet!");
                }
                else MessageBox.Show("Az beírt érték csak szám lehet!");

                inpNew.Clear();
            }
            else MessageBox.Show("Több elem nem adható a kupachoz");
        }

        private void delBtn_Click(object sender, EventArgs e)
        {
            if (N > 0)
            {
                Console.WriteLine("Remove: heap[0]=" + heap[0]);
                heapDel(0);
                printHeap();
                display.setModel(heap, N);
            }
            else MessageBox.Show("Nincs több elem a kupacban");
        }
    }
}
