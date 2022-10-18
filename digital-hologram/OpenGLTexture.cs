using System;
using System.Windows.Forms;
//using OpenTK.Graphics.OpenGL;
using OpenTK.Graphics.OpenGL4;
using System.Drawing;
using System.Drawing.Imaging;

namespace dholo
{
    class OpenGLTexture
    {
        public int TextureID { get; set; }

        public OpenGLTexture()
        {

        }

        public void CreateTexture(string imgpath)
        {
            Bitmap bitmap = new Bitmap(imgpath);
            BitmapData BiTMapData = null;

            int[] Texture = new int[1];

            GL.GenTextures(1, Texture);

            TextureID = Texture[0];
            GL.BindTexture(TextureTarget.Texture2D, TextureID);

            int res = 0;
            GL.GenBuffers(1, out res);
            GL.BindBuffer(BufferTarget.ArrayBuffer, res);

            int ImgWidth = bitmap.Width;
            int ImgHeight = bitmap.Height;

            Rectangle ImgArea = new Rectangle(new Point(0, 0), new Size(ImgWidth, ImgHeight));
            BiTMapData = bitmap.LockBits(ImgArea, ImageLockMode.ReadOnly, bitmap.PixelFormat);

            IntPtr bmpDatPtr = BiTMapData.Scan0;

            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgb8, ImgWidth, ImgHeight, 0, OpenTK.Graphics.OpenGL4.PixelFormat.Bgr, PixelType.UnsignedByte, bmpDatPtr);

            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);

            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapS, (int)TextureWrapMode.ClampToBorder);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapT, (int)TextureWrapMode.ClampToBorder);

            if(BiTMapData != null)
                bitmap.UnlockBits(BiTMapData);
        }
    }
}
