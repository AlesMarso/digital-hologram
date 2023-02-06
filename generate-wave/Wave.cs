using System;
using System.Drawing;

namespace generate_wave
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
        public double MAX { get; set; }
        public double MIN { get; set; }

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

        public void FindMax()
        {
            MAX = -100000000;

            foreach (var point in Points)
            {
                if (point.Y > MAX) MAX = point.Y;
            }
        }

        public void FinMin()
        {
            MIN = 100000000;

            foreach (var point in Points)
            {
                if (point.Y < MIN) MIN = point.Y;
            }
        }
    }
}
