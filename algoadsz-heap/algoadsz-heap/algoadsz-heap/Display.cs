using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace algoadsz_heap
{
    class Display : Panel
    {
        private Graphics gx;
        private int[] model;
        private int count;

        public Display(Control parent)
        {
            parent.Controls.Add(this);

            BackColor = Color.White;
            Width = parent.ClientSize.Width;
            Height = parent.ClientSize.Height;
            Left = 0;
            Top = 0;

            SetStyle(
                ControlStyles.AllPaintingInWmPaint |
                ControlStyles.UserPaint |
                ControlStyles.DoubleBuffer,
                true);
            UpdateStyles();

            gx = CreateGraphics();
            Paint += draw;

            model = null;
            count = 0;
        }

        public void setModel(int[] model,int count)
        {
            this.model = model;
            this.count = count;
            Refresh();
        }
        private void draw(object sender, PaintEventArgs e)
        {
            if (model != null)
            {
                //int count = model.Length;

                if (count > 0)
                {
                    int[] vx = new int[count];
                    int[] vy = new int[count];

                    int top = 45;
                    int center = Width / 2;

                    vx[0] = center;
                    vy[0] = top;

                    int lx, ws;

                    lx = Width / 4;
                    ws = Width / 2;
                    for( int i=1; i<=2 && i<count; i++)
                    {
                        vy[i] = top + 100;
                        vx[i] = lx;
                        lx += ws;
                    }

                    lx = Width / 8;
                    ws = Width / 4;
                    for (int i = 3; i <= 6 && i < count; i++)
                    {
                        vy[i] = top + 100 * 2;
                        vx[i] = lx;
                        lx += ws;
                    }

                    lx = Width / 16;
                    ws = Width / 8;
                    for (int i = 7; i <= 14 && i < count; i++)
                    {
                        vy[i] = top + 100 * 3;
                        vx[i] = lx;
                        lx += ws;
                    }
                    for (int i = 15; i < count; i++) vx[i] = vy[i] = -100;

                        for (int i = 0; i < count; i++)
                    {
                        int c; 
                        c = (i * 2)+1;
                        if (c < count) drawEdge( e.Graphics, vx[i], vy[i], vx[c], vy[c] );
                        c++;
                        if (c < count) drawEdge(e.Graphics, vx[i], vy[i], vx[c], vy[c]);

                        drawVertex(e.Graphics, vx[i], vy[i], model[i], i==0 ? true : false );
                    }
                }
            }
        }
        private void drawVertex( Graphics graphics, int x, int y, int value, bool root=false)
        {
            x -= 25;
            y -= 25;

            Brush border = Brushes.Gray;
            Brush brush = Brushes.LightGray;
            Pen pen = new Pen(border, 3);
            SolidBrush txt = new SolidBrush(Color.Gray);

            if (root)
            {
                brush = Brushes.Gray;
                txt = new SolidBrush(Color.White);
            }

            graphics.FillEllipse(brush, x, y, 50, 50);
            graphics.DrawEllipse(pen, x, y, 50, 50);

            StringFormat stringFormat = new StringFormat();
            stringFormat.Alignment = StringAlignment.Center;
            stringFormat.LineAlignment = StringAlignment.Center;

            graphics.DrawString( value.ToString(), new Font("Arial", 16, FontStyle.Bold), txt, new Rectangle(x, y + 3, 50, 50), stringFormat);
        }
        private void drawEdge(Graphics graphics, int fx, int fy, int tx, int ty )
        {
            Brush border = Brushes.Gray;
            Pen pen = new Pen(border, 3);

            graphics.DrawLine( pen, new Point(fx, fy), new Point(tx, ty));
        }
    }
}
