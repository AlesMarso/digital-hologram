using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SharpGL;

namespace dholo
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void OnGLContextRenderPaint(object sender, PaintEventArgs e)
        {
        }

        private void openImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openImageDlg.ShowDialog() == DialogResult.OK)
            {
                pictureBox1.Load(openImageDlg.FileName);
            }
        }

        private void loadHolgram_Click(object sender, EventArgs e)
        {
            if (openImageDlg.ShowDialog() == DialogResult.OK)
            {
                pictureBox1.Load(openImageDlg.FileName);
            }
        }

        private void tabControl_Layout(object sender, LayoutEventArgs e)
        {

        }

        private void openHologramButton_Click(object sender, EventArgs e)
        {
            if (openImageDlg.ShowDialog() == DialogResult.OK)
            {
                pictureBox1.Load(openImageDlg.FileName);
            }
        }

        private void gPUToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        private void waveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GenerateWaveDlg dlg = new GenerateWaveDlg();

            dlg.ShowDialog();

            dlg.Dispose();
        }

        private void glRenderContext_Load(object sender, EventArgs e)
        {
        }

        private void glRenderContext_Resize(object sender, EventArgs e)
        {
        }

        private void OnOpenGLRenderContextPaint(object sender, SharpGL.RenderEventArgs args)
        {
            OpenGL glRender = OpenGLRenderContext.OpenGL;

            glRender.ClearColor(Color.White.R, Color.White.G, Color.White.B, Color.White.A);
            glRender.Clear(OpenGL.GL_COLOR_BUFFER_BIT);

            glRender.Flush();
        }
    }
}
