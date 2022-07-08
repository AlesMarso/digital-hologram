using System;
using System.Drawing;

namespace dholo
{
    enum WaveType : int
    {
        Sin,
        Six
    }

    public abstract class Wave
    {
        
        public double Phase { get; set; }
        public double Freq { get; set; }

        public int CntPoints { get; set; }
        public int CntT { get; set; }

        public double dt { get; set; }
        public double T { get; set; }

        public PointF[] Points { get; set; }

        public Wave()
        {
            CntPoints = 1024;

            Phase = 0;
            Freq = 1;

            dt = Math.PI / 180;
            T = 1;
            CntT = 1;
        }

        public abstract PointF[] Make();
    }
}
