using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.ExceptionServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI
{
    unsafe public partial class MainForm : Form
    {
        private Pen pen;
        private Graphics g;
        private LinkedList<int> StraightLines;
        private LinkedList<int> RayLines;
        private LinkedList<int> LineSegments;
        private LinkedList<int> Circle;

        [DllImport("core.dll")]
        private static extern int add_Figure(StringBuilder buf);
        [DllImport("core.dll")]
        private static extern void initial_PlaneContainer();
        [DllImport("core.dll")]
        private static extern void dispose_PlaneContainer();
        [DllImport("core.dll")]
        private static extern double* get_IntersectionPoints();
        [DllImport("core.dll")]
        private static extern int get_NumOfIntersectionPoints();
        public MainForm()
        {
            InitializeComponent();
            dispose_PlaneContainer();
            initial_PlaneContainer();
            this.DoubleBuffered = true;
            this.pen = new Pen(Color.Red, width: 2);
            this.g = panel1.CreateGraphics();
            this.RayLines = new LinkedList<int>();
            this.StraightLines = new LinkedList<int>();
            this.LineSegments = new LinkedList<int>();
            this.Circle = new LinkedList<int>();
        }
        private void inputButton_Click(object sender, EventArgs e)
        {
            if (this.openFileDialog1.ShowDialog() == DialogResult.OK
                && !string.IsNullOrEmpty(this.openFileDialog1.FileName))
            {
                MessageBox.Show("输入文件打开成功!\n" + this.openFileDialog1.FileName);
                this.pathInput.Text = this.openFileDialog1.FileName;
                if (this.pathInput.Text != "no file")
                {
                    StreamReader sr = null;
                    try
                    {
                        sr = new StreamReader(this.pathInput.Text);
                        sr.ReadLine();
                    }
                    catch (Exception ee)
                    {
                        MessageBox.Show(this.openFileDialog1.FileName + "打开失败!");
                        this.openFileDialog1.FileName = "no file";
                    }

                    String line = sr.ReadLine();
                    StringBuilder sb = new StringBuilder(line);

                    while (line != null)
                    {
                        sb = new StringBuilder(line);
                        int retCode = add_Figure(sb);
                        processRetVal(retCode, line);
                        line = sr.ReadLine();
                    }
                    num.Text = "交点数目: " + get_NumOfIntersectionPoints();
                    MessageBox.Show(pathInput.Text + "录入完毕");
                }
            }
            else
            {
                MessageBox.Show("打开失败!\n");
                this.pathInput.Text = "no file";
            }
        }
        private bool processRetVal(int retCode, string line)
        {
            switch (retCode)
            {
                case -1:
                    MessageBox.Show(line + "添加失败" + "\n" + "数据输入格式有误!");
                    break;
                case 1:
                    MessageBox.Show(line + "添加失败" + "\n" + "数据范围应在(-100000,100000)!");
                    break;
                case 2:
                    MessageBox.Show(line + "添加失败" + "\n" + "两个端点坐标重合!");
                    break;
                case 3:
                    MessageBox.Show(line + "添加失败" + "\n" + "半径应为正数");
                    break;
                case 4:
                    MessageBox.Show(line + "添加失败" + "\n" + "数据范围应在(-100000,100000)!");
                    break;
                default:
                    //添加成功, 记得将其存储
                    this.store(line);
                    return true;
            }
            return false;
        }
        private void store(string buf)
        {
            string[] arr = buf.Split(' ');
            switch (arr[0])
            {
                case "L":
                    StraightLines.AddLast(int.Parse(arr[1]));
                    StraightLines.AddLast(int.Parse(arr[2]));
                    StraightLines.AddLast(int.Parse(arr[3]));
                    StraightLines.AddLast(int.Parse(arr[4]));
                    break;
                case "R":
                    RayLines.AddLast(int.Parse(arr[1]));
                    RayLines.AddLast(int.Parse(arr[2]));
                    RayLines.AddLast(int.Parse(arr[3]));
                    RayLines.AddLast(int.Parse(arr[4]));
                    break;
                case "S":
                    LineSegments.AddLast(int.Parse(arr[1]));
                    LineSegments.AddLast(int.Parse(arr[2]));
                    LineSegments.AddLast(int.Parse(arr[3]));
                    LineSegments.AddLast(int.Parse(arr[4]));
                    break;
                case "C":
                    Circle.AddLast(int.Parse(arr[1]));
                    Circle.AddLast(int.Parse(arr[2]));
                    Circle.AddLast(int.Parse(arr[3]));
                    break;
                default:
                    break;
            }
            this.panel1.Refresh();
        }
        private void MainForm_Load(object sender, EventArgs e)
        {
            MessageBox.Show("欢迎使用");
        }
        private void drawLine()
        {
            int n, dx, dy;
            Point p1, p2;
            p1 = new Point();
            p2 = new Point();

            n = StraightLines.Count() / 4;
            IEnumerator<int> iter = StraightLines.GetEnumerator();
            for (int i = 0; i < n; i++)
            {
                iter.MoveNext();
                p1.X = iter.Current;
                iter.MoveNext();
                p1.Y = iter.Current;
                iter.MoveNext();
                p2.X = iter.Current;
                iter.MoveNext();
                p2.Y = iter.Current;
                dx = p2.X - p1.X;
                dy = p2.Y - p1.Y;
                p1.X -= 20 * dx;
                p1.Y -= 20 * dy;
                p2.X += 20 * dx;
                p2.Y += 20 * dy;

                change(ref p1); change(ref p2);
                g.DrawLine(pen, p1, p2);
            }
        }
        private void drawCircle()
        {
            int n, r;
            Point p1;
            p1 = new Point();

            n = Circle.Count() / 3;
            IEnumerator<int> iter = Circle.GetEnumerator();
            for (int i = 0; i < n; i++)
            {
                iter.MoveNext();
                p1.X = iter.Current;
                iter.MoveNext();
                p1.Y = iter.Current;
                iter.MoveNext();
                r = iter.Current * 40;
                change(ref p1);
                g.DrawEllipse(pen, p1.X - r, p1.Y - r, 2 * r, 2 * r);
            }
        }
        private void drawRay()
        {
            int n, dx, dy;
            Point p1, p2;
            p1 = new Point();
            p2 = new Point();

            n = RayLines.Count() / 4;
            IEnumerator<int> iter = RayLines.GetEnumerator();
            for (int i = 0; i < n; i++)
            {
                iter.MoveNext();
                p1.X = iter.Current;
                iter.MoveNext();
                p1.Y = iter.Current;
                iter.MoveNext();
                p2.X = iter.Current;
                iter.MoveNext();
                p2.Y = iter.Current;
                dx = p2.X - p1.X;
                dy = p2.Y - p1.Y;
                p2.X += 20 * dx;
                p2.Y += 20 * dy;

                change(ref p1); change(ref p2);
                g.DrawLine(pen, p1, p2);
            }
        }
        private void drawLineSegment()
        {
            int n;
            Point p1, p2;
            p1 = new Point();
            p2 = new Point();

            n = LineSegments.Count() / 4;
            IEnumerator<int> iter = LineSegments.GetEnumerator();
            for (int i = 0; i < n; i++)
            {
                iter.MoveNext();
                p1.X = iter.Current;
                iter.MoveNext();
                p1.Y = iter.Current;
                iter.MoveNext();
                p2.X = iter.Current;
                iter.MoveNext();
                p2.Y = iter.Current;
                change(ref p1); change(ref p2);
                g.DrawLine(pen, p1, p2);
            }
        }
        private void change(ref Point p)
        {
            p.X = p.X * 40 + 400;
            p.Y = -p.Y * 40 + 400;
        }
        private void change(ref PointF p)
        {
            p.X = p.X * 40 + 400;
            p.Y = -p.Y * 40 + 400;
        }
        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            drawLine();
            drawCircle();
            drawRay();
            drawLineSegment();

            PointF cPt = new PointF(400, 400);//中心点(坐标轴原点)   
            PointF[] xPt = new PointF[3]{
             new   PointF(cPt.Y+400,cPt.Y),
             new   PointF(cPt.Y+400-15,cPt.Y-8),
             new   PointF(cPt.Y+400-15,cPt.Y+8)};//(X轴右边三角形的三个点坐标）   
            PointF[] yPt = new PointF[3]{
             new   PointF(cPt.X,cPt.X-400),
             new   PointF(cPt.X+8,cPt.X-400+15),
             new   PointF(cPt.X-8,cPt.X-400+15)};//Y轴三角形   

            PointF aPt = new PointF(-10, 0);
            change(ref aPt);
            PointF bPt = new PointF(10, 0);
            change(ref bPt);

            g.DrawLine(Pens.Black, aPt, bPt);//画x轴
            g.DrawPolygon(Pens.Black, xPt);//画X轴箭头三角形
            g.FillPolygon(new SolidBrush(Color.Black), xPt);//X轴箭头填充黑色
            g.DrawString("x", new Font("宋体", 12),
             Brushes.Black, new PointF(bPt.X - 30, bPt.Y + 10));

            //画X轴刻度
            for (int i = -9; i <= 9; i++)
            {
                if (i == 0)
                {
                    g.DrawString("O".ToString(), new Font("宋体", 11), Brushes.Black,
                         new PointF(cPt.X + i * 40, aPt.Y));//X轴坐标
                    continue;
                }
                g.DrawString(i.ToString(), new Font("宋体", 11), Brushes.Black,
                         new PointF(cPt.X + i * 40 - 10, aPt.Y + 5));//X轴坐标
                g.DrawLine(Pens.Black, cPt.X + i * 40, cPt.Y + 400, cPt.X + i * 40, cPt.Y - 400);//X轴刻度
            }
            //画Y轴   
            aPt = new PointF(0, -10);
            change(ref aPt);
            bPt = new PointF(0, 10);
            change(ref bPt);

            g.DrawLine(Pens.Black, aPt, bPt);
            g.DrawPolygon(Pens.Black, yPt);
            g.FillPolygon(new SolidBrush(Color.Black), yPt);
            g.DrawString("y", new Font("宋体", 12), Brushes.Black, new PointF(bPt.X - 30, bPt.Y + 10));

            //画Y轴刻度
            for (int i = -9; i <= 9; i++)
            {
                if (i == 0)
                {
                    continue;
                }
                if (i > 0)
                {
                    g.DrawString(i.ToString(), new Font("宋体", 11), Brushes.Black,
                         new PointF(cPt.X - 20, cPt.Y - (40 * i)));//Y轴坐标
                }
                else
                {
                    g.DrawString(i.ToString(), new Font("宋体", 11), Brushes.Black,
                         new PointF(cPt.X - 20 - 5, cPt.Y - 40 * i));//Y轴坐标
                }
                g.DrawLine(Pens.Black, cPt.X - 400, cPt.Y - 40 * i, cPt.X + 400, cPt.Y - (40 * i));//Y轴刻度
            }

        }
        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }
        private void button2_Click(object sender, EventArgs e)
        {
            int ret;
            string line = null;
            if (textBox1.Text == "L" || textBox1.Text == "R" || textBox1.Text == "S")
            {
                line =
                textBox1.Text + " " +
                textBox2.Text + " " +
                textBox3.Text + " " +
                textBox4.Text + " " +
                textBox5.Text;
            }
            else
            {
                line =
                 textBox1.Text + " " +
                 textBox2.Text + " " +
                 textBox3.Text + " " +
                 textBox6.Text;
            }
            ret = add_Figure(new StringBuilder(line));
            bool tmp = processRetVal(ret, line);
            num.Text = "交点数目: " + get_NumOfIntersectionPoints();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if (this.saveFileDialog1.ShowDialog() == DialogResult.OK
               && !string.IsNullOrEmpty(this.saveFileDialog1.FileName))
            {
                MessageBox.Show("结果已经保存至:" + this.saveFileDialog1.FileName);
            }
            else
            {
                MessageBox.Show("结果保存失败\n");
            }
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            dispose_PlaneContainer();
            MessageBox.Show("再见");
        }
    }

}
