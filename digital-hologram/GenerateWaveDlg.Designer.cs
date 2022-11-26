
namespace dholo
{
    partial class GenerateWaveDlg
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Chart = new System.Windows.Forms.PictureBox();
            this.waveType = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.phase = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.wavesCnt = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.ResultImageWave = new System.Windows.Forms.PictureBox();
            this.saveImage = new System.Windows.Forms.Button();
            this.createImage = new System.Windows.Forms.Button();
            this.eraseImage = new System.Windows.Forms.Button();
            this.pointsCnt = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.saveImageDlg = new System.Windows.Forms.SaveFileDialog();
            ((System.ComponentModel.ISupportInitialize)(this.Chart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ResultImageWave)).BeginInit();
            this.SuspendLayout();
            // 
            // Chart
            // 
            this.Chart.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.Chart.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Chart.Location = new System.Drawing.Point(8, 8);
            this.Chart.Margin = new System.Windows.Forms.Padding(0);
            this.Chart.Name = "Chart";
            this.Chart.Size = new System.Drawing.Size(558, 323);
            this.Chart.TabIndex = 0;
            this.Chart.TabStop = false;
            this.Chart.Click += new System.EventHandler(this.Chart_Click);
            this.Chart.Paint += new System.Windows.Forms.PaintEventHandler(this.OnChartPaint);
            // 
            // waveType
            // 
            this.waveType.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.waveType.FormattingEnabled = true;
            this.waveType.Items.AddRange(new object[] {
            "sin(x)",
            "sin(x)/x"});
            this.waveType.Location = new System.Drawing.Point(95, 337);
            this.waveType.Name = "waveType";
            this.waveType.Size = new System.Drawing.Size(70, 25);
            this.waveType.TabIndex = 1;
            this.waveType.SelectedIndexChanged += new System.EventHandler(this.OnWaveTypeSelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.label1.Location = new System.Drawing.Point(12, 340);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 19);
            this.label1.TabIndex = 2;
            this.label1.Text = "Вид волны";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // phase
            // 
            this.phase.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.phase.Location = new System.Drawing.Point(216, 337);
            this.phase.Name = "phase";
            this.phase.Size = new System.Drawing.Size(48, 25);
            this.phase.TabIndex = 6;
            this.phase.Text = "0,0";
            this.phase.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.phase.TextChanged += new System.EventHandler(this.OnWaveTypeSelectedIndexChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.label3.Location = new System.Drawing.Point(171, 340);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(39, 19);
            this.label3.TabIndex = 5;
            this.label3.Text = "Фаза";
            this.label3.Click += new System.EventHandler(this.label3_Click);
            // 
            // wavesCnt
            // 
            this.wavesCnt.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.wavesCnt.Location = new System.Drawing.Point(363, 337);
            this.wavesCnt.Name = "wavesCnt";
            this.wavesCnt.Size = new System.Drawing.Size(37, 25);
            this.wavesCnt.TabIndex = 8;
            this.wavesCnt.Text = "1";
            this.wavesCnt.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.wavesCnt.TextChanged += new System.EventHandler(this.OnWaveTypeSelectedIndexChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.label4.Location = new System.Drawing.Point(270, 340);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(87, 19);
            this.label4.TabIndex = 7;
            this.label4.Text = "Кол-во волн";
            this.label4.Click += new System.EventHandler(this.label4_Click);
            // 
            // ResultImageWave
            // 
            this.ResultImageWave.BackColor = System.Drawing.Color.Silver;
            this.ResultImageWave.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ResultImageWave.Location = new System.Drawing.Point(575, 8);
            this.ResultImageWave.Name = "ResultImageWave";
            this.ResultImageWave.Size = new System.Drawing.Size(323, 323);
            this.ResultImageWave.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.ResultImageWave.TabIndex = 9;
            this.ResultImageWave.TabStop = false;
            this.ResultImageWave.Click += new System.EventHandler(this.ResultImageWave_Click);
            // 
            // saveImage
            // 
            this.saveImage.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.saveImage.Location = new System.Drawing.Point(575, 335);
            this.saveImage.Name = "saveImage";
            this.saveImage.Size = new System.Drawing.Size(85, 26);
            this.saveImage.TabIndex = 14;
            this.saveImage.Text = "Сохранить";
            this.saveImage.UseVisualStyleBackColor = true;
            this.saveImage.Click += new System.EventHandler(this.OnSaveImageClick);
            // 
            // createImage
            // 
            this.createImage.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.createImage.Location = new System.Drawing.Point(697, 335);
            this.createImage.Name = "createImage";
            this.createImage.Size = new System.Drawing.Size(85, 26);
            this.createImage.TabIndex = 15;
            this.createImage.Text = "Создать";
            this.createImage.UseVisualStyleBackColor = true;
            this.createImage.Click += new System.EventHandler(this.OnCreateImageClick);
            // 
            // eraseImage
            // 
            this.eraseImage.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.eraseImage.Location = new System.Drawing.Point(813, 335);
            this.eraseImage.Name = "eraseImage";
            this.eraseImage.Size = new System.Drawing.Size(85, 26);
            this.eraseImage.TabIndex = 16;
            this.eraseImage.Text = "Очистить";
            this.eraseImage.UseVisualStyleBackColor = true;
            this.eraseImage.Click += new System.EventHandler(this.OnEraseImageClick);
            // 
            // pointsCnt
            // 
            this.pointsCnt.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.pointsCnt.Location = new System.Drawing.Point(505, 337);
            this.pointsCnt.Name = "pointsCnt";
            this.pointsCnt.Size = new System.Drawing.Size(61, 25);
            this.pointsCnt.TabIndex = 18;
            this.pointsCnt.Text = "1024";
            this.pointsCnt.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.pointsCnt.TextChanged += new System.EventHandler(this.OnWaveTypeSelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.label2.Location = new System.Drawing.Point(406, 340);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(93, 19);
            this.label2.TabIndex = 17;
            this.label2.Text = "Кол-во точек";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // GenerateWaveDlg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(910, 371);
            this.Controls.Add(this.pointsCnt);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.eraseImage);
            this.Controls.Add(this.createImage);
            this.Controls.Add(this.saveImage);
            this.Controls.Add(this.ResultImageWave);
            this.Controls.Add(this.wavesCnt);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.phase);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.waveType);
            this.Controls.Add(this.Chart);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximumSize = new System.Drawing.Size(994, 410);
            this.Name = "GenerateWaveDlg";
            this.Text = "GenerateWaveDlg";
            ((System.ComponentModel.ISupportInitialize)(this.Chart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ResultImageWave)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox Chart;
        private System.Windows.Forms.ComboBox waveType;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox phase;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox wavesCnt;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.PictureBox ResultImageWave;
        private System.Windows.Forms.Button saveImage;
        private System.Windows.Forms.Button createImage;
        private System.Windows.Forms.Button eraseImage;
        private System.Windows.Forms.TextBox pointsCnt;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.SaveFileDialog saveImageDlg;
    }
}