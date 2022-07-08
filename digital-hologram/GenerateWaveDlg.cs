using System;
using System.Drawing;
using System.Windows.Forms;
using dholo.wave;

namespace dholo
{
    public partial class GenerateWaveDlg : Form
    {
        public const int StepWidth = 20;
        public const int StepHeight = 20;

        public Wave wave;

        private Bitmap image;

        public GenerateWaveDlg()
        {
            InitializeComponent();

            wave = new SinWave();

            waveType.SelectedIndex = 0;
        }

        private void waveRender_Paint(object sender, PaintEventArgs e)
        {
            DrawGrid(e.Graphics);
            DrawChart(e.Graphics);
        }

        private void GenerateWaveDlg_Load(object sender, EventArgs e)
        {

        }

        private void DrawGrid(Graphics render)
        {
            int CountHorLines = Chart.Width / StepWidth + 1;
            int CountVertLines = Chart.Height / StepHeight + 1;

            Point top = new Point(0, 0);
            Point bottom = new Point(top.X, top.Y + Height);

            Point right = new Point(0, 0);
            Point left = new Point(right.X + Width, right.Y);

            Pen linePen = new Pen(Color.LightGray);
            linePen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;

            for (int hori = 1; hori < CountHorLines; hori++)
            {
                Point p1 = new Point(top.X + hori * StepWidth, top.Y);
                Point p2 = new Point(bottom.X + hori * StepWidth, bottom.Y);

                render.DrawLine(linePen, p1, p2);
            }

            for (int veri = 1; veri < CountVertLines; veri++)
            {
                Point p1 = new Point(right.X, right.Y + veri * StepHeight);
                Point p2 = new Point(left.X, left.Y + veri * StepHeight);

                render.DrawLine(linePen, p1, p2);
            }
        }

        private void DrawChart(Graphics render)
        {
            wave.Make();

            var len = wave.Points.Length - 1;

            PointF p1 = wave.Points[0];
            p1.Y = (1 - p1.Y) * Chart.Height;

            var dx = Convert.ToSingle(Chart.Width) / Convert.ToSingle(wave.CntPoints - 1);

            for (int i = 1; i < len; i++)
            {
                var x = p1.X + dx;
                var y = (1 - wave.Points[i + 1].Y) * Chart.Height;

                var p2 = new PointF(x, y);

                render.DrawLine(Pens.Black, p1, p2);

                p1 = p2;
            }
        }

        private void waveType_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                WaveType wvType = (WaveType)waveType.SelectedIndex;

                switch (wvType)
                {
                    case WaveType.Sin:
                        {
                            wave = new SinWave();
                        }
                        break;

                    case WaveType.Six:
                        {

                        }
                        break;
                }

                wave.CntT = wavesCnt.Text.Length == 0 ? 1 : Convert.ToInt32(wavesCnt.Text);
                wave.Phase = phase.Text.Length == 0 ? 0 : Convert.ToSingle(phase.Text);
                wave.CntPoints = pointsCnt.Text.Length == 0 ? 1024 : Convert.ToInt32(pointsCnt.Text);

                Chart.Refresh();

            } 
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void saveImage_Click(object sender, EventArgs e)
        {
            try
            {
                if(saveImageDlg.ShowDialog() == DialogResult.OK)
                {
                    image.Save(saveImageDlg.FileName);
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void createImage_Click(object sender, EventArgs e)
        {
            try
            {
                var BmpWidth = Convert.ToInt32(pointsCnt.Text);
                var BmpHeight = Convert.ToInt32(pointsCnt.Text);

                image = new Bitmap(BmpWidth, BmpHeight, System.Drawing.Imaging.PixelFormat.Format24bppRgb);

                for(int iy = 0; iy < BmpHeight; iy++)
                {
                    for(int ix = 0; ix < BmpWidth; ix++)
                    {
                       var PixelColor = Convert.ToByte(wave.Points[ix].Y * 255);

                       image.SetPixel(ix, iy, Color.FromArgb(PixelColor, PixelColor, PixelColor));
                    }
                }

                resultImage.Image = image;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void eraseImage_Click(object sender, EventArgs e)
        {

        }
    }
}
