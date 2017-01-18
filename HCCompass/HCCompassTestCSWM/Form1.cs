using System;
using System.Linq;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using HCCompassLib;

namespace HCCompassTestCSWM
{
    public partial class Form1 : Form
    {
        public static ICompass compass;
        private Graphics comp; //指南针
        private Graphics bubble; // 对中气泡

        public Form1()
        {
            InitializeComponent();
        }

        [DllImport("HCCompass.dll", EntryPoint = "DllRegisterServer")]
        static extern int DllRegisterServer();

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            DllRegisterServer();
            compass = new Compass();
            if (compass.IsLaserOpen())
            {
                button1.Text = "关闭激光";
            }
            else
            {
                button1.Text = "打开激光";
            }

            bubble = tabPage1.CreateGraphics();
            comp = tabPage2.CreateGraphics();
            panel1.Hide();
            timer1.Interval = 500;
            timer1.Enabled = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (compass.IsLaserOpen())
            {
                if (compass.CloseLaser())
                {
                    MessageBox.Show("关闭激光成功");
                    button1.Text = "打开激光";
                }
                else
                {
                    MessageBox.Show("关闭激光失败");
                }
            }
            else
            {
                if (compass.OpenLaser())
                {
                    MessageBox.Show("打开激光成功");
                    button1.Text = "关闭激光";
                }
                else
                {
                    MessageBox.Show("打开激光失败");
                }
            }
        }

        private void Form1_Closing(object sender, CancelEventArgs e)
        {
            compass.CloseLaser();            
        }

        private void UpdateBubble()
        {
            bubble.Clear(Color.White);
            Pen p = new Pen(Color.Black);
            bubble.DrawEllipse(p, panel1.Left, panel1.Top, panel1.Width, panel1.Width);
            bubble.DrawLine(p, panel1.Left, panel1.Top + panel1.Width / 2,
                panel1.Left + panel1.Width, panel1.Top + panel1.Width / 2);
            bubble.DrawLine(p, panel1.Left + panel1.Width / 2, panel1.Top,
                panel1.Left + panel1.Width / 2, panel1.Top + panel1.Width);

            
            int width = panel1.Width;
            int halfWidth = width / 2;
            Point leftTop = new Point(panel1.Left, panel1.Top);
            Point center = new Point(
                leftTop.X + halfWidth, leftTop.Y + halfWidth);
            double dx;
            double dy;
            dx = dy = 0;
            int radius = width / 6;
            int dia = 2 * radius;
            int maxValue = 60;
            if (compass.GetLaserDip(ref dx, ref dy))
            {
                int idx = (int)dx;
                int idy = (int)dy;

                idx = idx % maxValue;
                idy = idy % maxValue;

                Point bc = new Point();
                bc.X = (int)(center.X + ((double)idx / maxValue) * halfWidth);
                bc.Y = (int)(center.Y - ((double)idy / maxValue) * halfWidth);

                bubble.DrawEllipse(p, bc.X - radius, bc.Y - radius,
                    dia, dia);

            }
            
            
        }

        private void UpdateCompass()
        {
            double direction = 0;
            if (compass.GetDirection(ref direction))
            {
                textBox1.Text = direction.ToString();
            }

            int speedX, speedY, speedZ;
            speedX = speedY = speedZ = 0;
            if (compass.GetAngularSpeed(ref speedX, ref speedY, ref speedZ))
            {
                textBox2.Text = speedX.ToString();
                textBox3.Text = speedY.ToString();
                textBox4.Text = speedZ.ToString();
            }

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            UpdateBubble();
            UpdateCompass();
        }

    }
}