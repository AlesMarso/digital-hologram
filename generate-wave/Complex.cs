using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace generate_wave
{
    class Complex
    {
        public double A { get; set; }
        public double B { get; set; }

        public Complex()
        {
            A = 0.0f;
            B = 0.0f;
        }

        public Complex(double a, double b)
        {
            A = a;
            B = b;
        }

        public void SetA(double a)
        {
            A = a;
        }

        public void SetB(double b)
        {
            B = b;
        }

        public static Complex operator+(Complex right, Complex left)
        {
           double a = right.A + left.A;
           double b = right.B + left.B;

            return new Complex(a, b);
        }

        public static Complex operator-(Complex right, Complex left)
        {
            double a = right.A - left.A;
            double b = right.B - left.B;

            return new Complex(a, b);
        }

        public static Complex operator*(Complex right, Complex left)
        {
            double a = (right.A * left.A) - (right.B * left.B);
            double b = (right.A * left.B) + (right.B * left.A);

            return new Complex(a, b);
        }

        public static Complex operator+(Complex right, double left)
        {
            double a = right.A + left;
            double b = right.B + left;

            return new Complex(a, b);
        }
    }
}
