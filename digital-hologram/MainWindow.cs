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

namespace dholo
{
    public partial class MainWindow : Form
    {
        private double RightGLRenderContextOrtho;
        private double LeftGLRenderContextOrtho;
        private double BottomGLRenderContextOrtho;
        private double TopGLRenderContextOrtho;
        private double NearGLRenderContextOrtho;
        private double FarGLRenderContextOrtho;

        private uint[] Texture;

        private Color QuadColor;
        private Color BckgColor;

        private bool IsTextureCreated;

        private string ImgPath;
        private Bitmap ImgText;
        private int VBO;

        private float[] vertices = new float[12]
        {
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
        };

        public MainWindow()
        {
            Texture = new uint[1];
            IsTextureCreated = false;
            ImgPath = @"C:\Users\ales1\nstu-stuff\masterthesis\digital-hologram\digital-hologram\img\img.jpg";
            ImgText = new Bitmap(ImgPath);

            QuadColor = Color.Black;
            BckgColor = Color.White;

            InitializeComponent();

            VBO = CreateVBO();
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

            NearGLRenderContextOrtho = -1.0f;
            FarGLRenderContextOrtho = -2.0f;
        }

        private void UseImgButton_Click(object sender, EventArgs e)
        {
        }

        private void GenTexture(ref Bitmap bitmap)
        {
            BitmapData BiTMapData = null;

            try
            {
                GL.GenTextures(1, Texture);
                GL.BindTexture(TextureTarget.Texture2D, Texture[0]);

                int ImgWidth = bitmap.Width;
                int ImgHeight = bitmap.Height;

                Rectangle ImgArea = new Rectangle(new Point(0, 0), new Size(ImgWidth, ImgHeight));
                BiTMapData = bitmap.LockBits(
                    ImgArea, 
                    ImageLockMode.ReadOnly, 
                    bitmap.PixelFormat);
                
                IntPtr bmpDatPtr = BiTMapData.Scan0;

                GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgb8, ImgWidth, ImgHeight, 0, OpenTK.Graphics.OpenGL.PixelFormat.Bgr, PixelType.UnsignedByte, bmpDatPtr);

                GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);
                GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);

                GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapS, (int)TextureWrapMode.ClampToBorder);
                GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapT, (int)TextureWrapMode.ClampToBorder);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
                if(BiTMapData != null)
                    bitmap.UnlockBits(BiTMapData);
            }
        }

        private int CreateVBO()
        {
            uint[] vbo = new uint[1];
            int VBOId = 0;
            try
            {
                //var sh = GL.CreateShader(ShaderType.ComputeShader);

                //GL.GenBuffers(1, vbo);
                //GL.BindBuffer(BufferTarget.ArrayBuffer, VBOId);
                //GL.BufferData(BufferTarget.ArrayBuffer, sizeof(float) * 12, vertices, BufferUsageHint.StaticDraw);
                //GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            return VBOId;
        }

        private void OnOpenGLRenderContextPaint(object sender, PaintEventArgs e)
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.LoadIdentity();

            if(!IsTextureCreated)
            {
                GenTexture(ref ImgText);
            
                IsTextureCreated = true;
            }

            if(IsTextureCreated)
            {
                GL.Enable(EnableCap.Texture2D);
                GL.BindTexture(TextureTarget.Texture2D, Texture[0]);

#pragma warning disable CS0618 // Type or member is obsolete
                GL.Begin(BeginMode.Quads);
#pragma warning restore CS0618 // Type or member is obsolete
                {
                    GL.Color4(Color.White); //Must have, weirdness!
                    GL.TexCoord2(1.0f, 1.0f);
                    GL.Vertex2(1.0f, 1.0f);
                    GL.TexCoord2(0.0f, 1.0f);
                    GL.Vertex2(-1.0f, 1.0f);
                    GL.TexCoord2(0.0f, 0.0f);
                    GL.Vertex2(-1.0f, -1.0f);
                    GL.TexCoord2(1.0f, 0.0f);
                    GL.Vertex2(1.0f, -1.0f);
                }
                GL.End();
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
