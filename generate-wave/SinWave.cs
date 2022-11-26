using System;
using System.Drawing;

namespace generate_wave
{
    class SinWave : Wave
    {
        public SinWave()
        {
            T = 2 * Math.PI;
        }

        public override PointF[] Make()
        {
            Points = new PointF[CntPoints];

            dt = Convert.ToSingle(CntT * T) / Convert.ToSingle(CntPoints);

            double t = 0.0f;

            for (int iPoint = 0; iPoint < CntPoints; iPoint++)
            {
                double argument = t * Freq + Phase;
                double sin = (Math.Sin(argument) + 1) / 2;

                Points[iPoint].X = Convert.ToSingle(t);
                Points[iPoint].Y = Convert.ToSingle(sin);

                t += dt;
            }

            return Points;
        }
    }
}
