using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace generate_wave
{
    public partial class MainWindow : Form
    {
        public const int StepWidth = 20;
        public const int StepHeight = 20;
        private static double M_2PI = 2 * 3.14159265358979323846;

        public Wave wave;

        private Bitmap image;

        public MainWindow()
        {
            InitializeComponent();

            wave = new SinWave();

            waveType.SelectedIndex = 0;

            wave.CntT = 1;
            wave.Phase = 0;
            wave.CntPoints = 1024;

            wave.Make();
        }

        private void OnPaint(object sender, PaintEventArgs e)
        {
            DrawGrid(e.Graphics);
            DrawChart(e.Graphics);
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

        private void OnSaveImageClick(object sender, EventArgs e)
        {
            try
            {
                if (saveImageDlg.ShowDialog() == DialogResult.OK)
                {
                    image.Save(saveImageDlg.FileName);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void OnCreateImageClick(object sender, EventArgs e)
        {
            try
            {
                var BmpWidth = Convert.ToInt32(pointsCnt.Text);
                var BmpHeight = Convert.ToInt32(pointsCnt.Text);

                image = new Bitmap(BmpWidth, BmpHeight, System.Drawing.Imaging.PixelFormat.Format32bppRgb);

                for (int iy = 0; iy < BmpHeight; iy++)
                {
                    for (int ix = 0; ix < BmpWidth; ix++)
                    {
                        var PixelColor = Convert.ToByte(wave.Points[ix].Y * 255);

                        image.SetPixel(ix, iy, Color.FromArgb(PixelColor, PixelColor, PixelColor));
                    }
                }

                ResultImageWave.Image = image;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void OnEraseImageClick(object sender, EventArgs e)
        {
            ResultImageWave.Image = null;
        }

        private void OnWaveTypeSelectedIndexChanged(object sender, EventArgs e)
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

                wave.Make();

                Chart.Refresh();

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void Chart_Click(object sender, EventArgs e)
        {

        }

        int BitReverseOfCenter(int index, int logm = 16)
        {
            int j = index;

            j = (j & 0x00005555) << 1 | (j & 0x0000AAAA) >> 1;
            j = (j & 0x00003333) << 2 | (j & 0x0000CCCC) >> 2;
            j = (j & 0x00000F0F) << 4 | (j & 0x0000F0F0) >> 4;
            j = (j & 0x000000FF) << 8 | (j & 0x0000FF00) >> 8;

            return j >> (16 - logm);
        }

        void D1_FFT(ref Complex[] input, ref Complex[] output )
        {
            if (input.Length == 0)
                throw new OverflowException();

            int sz = output.Length;
            int numLog2Levels = (int)Math.Log((double)sz, 2.0);

            const int MAX_THEOR_THREADS_NUM = 1024;
            const int MAX_POINTS_COUNT = 4;

            for(int thread_id = 0; thread_id < MAX_THEOR_THREADS_NUM; thread_id++)
            {
                int id = thread_id * MAX_POINTS_COUNT;

                for (int j = 0; j < MAX_POINTS_COUNT; j++)
                {
                    int i = id + j;

                    if (i >= sz)
                        continue;

                    int reverse_i = BitReverseOfCenter(i, numLog2Levels);
                    output[i] = input[reverse_i];
                }
            }

            int numBlocks = sz / 2;
            int numButterflyOperations = 1;
            int offset = 2;
            int offsetId = 1;

            for (int logLevel = 0, _2_k = 2; logLevel < numLog2Levels; logLevel++, _2_k *= 2)
            {
                for (int block = 0, idFirstElemInBlock = 0; block < numBlocks; block++, idFirstElemInBlock += offset)
                {
                    for (int operation = 0; operation < numButterflyOperations; operation++)
                    {
                        double y = (double)(operation) / (double)(_2_k);
                        double phi = M_2PI * y;

                        Complex W = new Complex(Math.Cos(phi), Math.Sin(phi));

                        int rightId = idFirstElemInBlock + operation;
                        int leftId = rightId + offsetId;

                        Complex right = output[rightId];
                        Complex left = output[leftId] * W;

                        output[rightId] = right + left;
                        output[leftId] = right - left;
                    }
                }

                numBlocks /= 2; // numBlocks = numBlocks / 2
                numButterflyOperations *= 2; // numButterflyOperations = numButterflyOperations * 2

                offset *= 2; // offset = offset * 2
                offsetId *= 2; // offsetId = offsetId * 2
            }
        }

        private void oneDimensionFFT_Click(object sender, EventArgs e)
        {
            Complex[] output = new Complex[wave.CntPoints];
            Complex[] input = new Complex[wave.CntPoints];

            for(int i = 0; i < wave.CntPoints; i++)
            {
                input[i] = new Complex((double)wave.Points[i].Y, 0.0);
            }

            D1_FFT(ref input, ref output);

            for(int i = 0; i < wave.CntPoints; i++)
            {
                float ampl = (float)Math.Sqrt(output[i].A * output[i].A + output[i].B * output[i].B);
                wave.Points[i].Y = ampl;
            }

            wave.FindMax();

            for(int i = 0; i < wave.CntPoints; i++)
            {
                wave.Points[i].Y = wave.Points[i].Y / (float)wave.MAX;
            }

            Chart.Refresh();
        }

        private void twoDimensionFFT_Click(object sender, EventArgs e)
        {
            Complex[] output = new Complex[wave.CntPoints];
            Complex[] input = new Complex[wave.CntPoints];

            for (int i = 0; i < wave.CntPoints; i++)
            {
                input[i] = new Complex((double)wave.Points[i].Y, 0.0);

            }

            D1_FFT(ref input, ref output);

            Complex[] temp = new Complex[output.Length];

            float[,] result = new float[output.Length, output.Length];

            float MAX = -1000000000;

            for(int i = 0; i < wave.CntPoints; i++)
            {
                for(int j = 0; j < wave.CntPoints; j++)
                {
                    input[j] = output[i];
                }

                D1_FFT(ref input, ref temp);

                for(int j = 0; j < wave.CntPoints; j++)
                {
                    float ampl = (float)Math.Sqrt(temp[j].A * temp[j].A + temp[j].B * temp[j].B);
                    result[i, j] = ampl;
                    if (ampl > MAX) MAX = ampl;
                }
            }

            try
            {
                var BmpWidth = Convert.ToInt32(temp.Length);
                var BmpHeight = Convert.ToInt32(temp.Length);

                image = new Bitmap(BmpWidth, BmpHeight, System.Drawing.Imaging.PixelFormat.Format24bppRgb);

                for (int iy = 0; iy < BmpHeight; iy++)
                {
                    for (int ix = 0; ix < BmpWidth; ix++)
                    {
                        float pixelVal = 0;
                        if(result[ix, iy] != 0)
                            pixelVal = result[ix, iy] / MAX;

                        var PixelColor = Convert.ToByte(pixelVal * 255);

                        image.SetPixel(ix, iy, Color.FromArgb(PixelColor, PixelColor, PixelColor));
                    }
                }

                ResultImageWave.Image = image;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void FFTSort(ref Complex[] input, ref Complex[] output)
        {
            if (input.Length == 0)
                throw new OverflowException();

            int sz = output.Length;
            int numLog2Levels = (int)Math.Log((double)sz, 2.0);

            const int MAX_THEOR_THREADS_NUM = 1024;
            const int MAX_POINTS_COUNT = 4;

            for (int thread_id = 0; thread_id < MAX_THEOR_THREADS_NUM; thread_id++)
            {
                int id = thread_id * MAX_POINTS_COUNT;

                for (int j = 0; j < MAX_POINTS_COUNT; j++)
                {
                    int i = id + j;

                    if (i >= sz)
                        continue;

                    int reverse_i = BitReverseOfCenter(i, numLog2Levels);
                    output[i] = input[reverse_i];
                }
            }

            return;
        }

        private void FFTSort_Click(object sender, EventArgs e)
        {
            try
            {
                Complex[] output = new Complex[wave.CntPoints];
                Complex[] input = new Complex[wave.CntPoints];

                for (int i = 0; i < wave.CntPoints; i++)
                {
                    input[i] = new Complex((double)wave.Points[i].Y, 0.0);
                }

                FFTSort(ref input, ref output);

                for(int i = 0; i < wave.CntPoints; i++)
                {
                    wave.Points[i].Y = (float)output[i].A;
                }

                Chart.Refresh();

                var BmpWidth = Convert.ToInt32(pointsCnt.Text);
                var BmpHeight = Convert.ToInt32(pointsCnt.Text);

                image = new Bitmap(BmpWidth, BmpHeight, System.Drawing.Imaging.PixelFormat.Format32bppRgb);

                for (int iy = 0; iy < BmpHeight; iy++)
                {
                    for (int ix = 0; ix < BmpWidth; ix++)
                    {
                        var PixelColor = Convert.ToByte(wave.Points[ix].Y * 255);

                        image.SetPixel(ix, iy, Color.FromArgb(PixelColor, PixelColor, PixelColor));
                    }
                }

                ResultImageWave.Image = image;
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
