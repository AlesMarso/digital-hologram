using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using OpenTK.Graphics.OpenGL;
using OpenTK.Platform.Windows;
using OpenCL.Net;
using OpenGL;

namespace dholo
{
    public partial class MainWindow : Form
    {
        private double RightGLRenderContextOrtho;
        private double LeftGLRenderContextOrtho;
        private double BottomGLRenderContextOrtho;
        private double TopGLRenderContextOrtho;

        private Color QuadColor;
        private Color BckgColor;

        private bool IsTextureCreated;

        private string ImgPath;
        private Bitmap ImgText;
        private int VBO;

        private OpenGLTexture Texture;

        private float[] vertices = new float[12]
        {
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
        };

        public MainWindow()
        {
            IsTextureCreated = false;
            ImgPath = @"C:\Users\ales1\nstu-stuff\masterthesis\digital-hologram\digital-hologram\img\img.jpg";

            QuadColor = Color.Black;
            BckgColor = Color.White;

            InitializeComponent();

            Texture = new OpenGLTexture();

            var t = OpenGL.Gl.GenBuffer();

            var a = 1;
        }

        private void openImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        private void loadHolgram_Click(object sender, EventArgs e)
        {
        }

        private void tabControl_Layout(object sender, LayoutEventArgs e)
        {

        }

        private void openHologramButton_Click(object sender, EventArgs e)
        {
        }

        private void waveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GenerateWaveDlg dlg = new GenerateWaveDlg();

            dlg.ShowDialog();

            dlg.Dispose();
        }

        private void LoadImageButton_Click(object sender, EventArgs e)
        {
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            RightGLRenderContextOrtho = OpenGLRenderContext.Width / 2;
            LeftGLRenderContextOrtho = -RightGLRenderContextOrtho;

            TopGLRenderContextOrtho = OpenGLRenderContext.Height / 2;
            BottomGLRenderContextOrtho = -TopGLRenderContextOrtho;

            
        }

        private void UseImgButton_Click(object sender, EventArgs e)
        {
        }

        private void OnOpenGLRenderContextPaint(object sender, PaintEventArgs e)
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.LoadIdentity();

            if(!IsTextureCreated)
            {
                Texture.CreateTexture(ImgPath);

                IsTextureCreated = true;
            }

            if(IsTextureCreated)
            {
                GL.Enable(EnableCap.Texture2D);

                GL.BindTexture(TextureTarget.Texture2D, Texture.TextureID);
                GL.Begin(BeginMode.Quads);
                {
                    GL.Color4(Color.White);
                    GL.TexCoord2(1.0f, 1.0f);
                    GL.Vertex2(1.0f, 1.0f);
                    GL.TexCoord2(0.0f, 1.0f);
                    GL.Vertex2(0.0f, 1.0f);
                    GL.TexCoord2(0.0f, 0.0f);
                    GL.Vertex2(0.0f, 0.0f);
                    GL.TexCoord2(1.0f, 0.0f);
                    GL.Vertex2(1.0f, 0.0f);
                }
                GL.End();
                GL.BindTexture(TextureTarget.Texture2D, 0);
                
                GL.Disable(EnableCap.Texture2D);
            }

            OpenGLRenderContext.SwapBuffers();
        }

        private void OpenGLRenderContext_Resize(object sender, EventArgs e)
        {
            GL.Viewport(0, 0, OpenGLRenderContext.Width, OpenGLRenderContext.Height);

            OpenGLRenderContext.Invalidate();
            OpenGLRenderContext.Update();
        }

        private void OpenGLRenderContext_Load(object sender, EventArgs e)
        {
            GL.ClearColor(Color.White);
        }
    }
}
