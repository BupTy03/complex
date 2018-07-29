#include <cmath>
//#include <iostream>
//#include <exception>
#include "Complex.h"

using namespace std;
namespace MyLib
{
	double Complex::real() { return re; }
	double Complex::imagin() { return im; }

	Complex operator+(const Complex& A, const Complex& B) { return Complex(A.re + B.re, A.im + B.im); }
	Complex operator+(const Complex& A, const double b) { return Complex(A.re + b, A.im); }
	Complex operator+=(Complex& A, const Complex& B) { return A = A + B; }
	Complex operator+=(Complex& A, const double b) { return A = A + b; }

	Complex operator-(const Complex& A, const Complex& B) { return Complex(A.re - B.re, A.im - B.im); }
	Complex operator-(const Complex& A, const double b) { return Complex(A.re - b, A.im); }
	Complex operator-=(Complex& A, const Complex& B) { return A = A - B; }
	Complex operator-=(Complex& A, const double b) { return A = A - b; }

	Complex operator*(const Complex& A, const Complex& B)
	{
		Complex C;
		C.re = A.re * B.re + A.im * B.im * (-1);
		C.im = A.re * B.im + A.im * B.re;
		return C;
	}
	Complex operator*(const Complex& A, const double b) { return Complex(A.re * b, A.im * b); }
	Complex operator*=(Complex& A, const Complex& B) { return A = A * B; }
	Complex operator*=(Complex& A, const double b) { return A = A * b; }

	Complex operator/(const Complex& A, const Complex& B)
	{
		Complex T(B.re, B.im * (-1));

		Complex N = A * T;
		Complex D = B * T;

		return Complex(N.re / D.re, N.im / D.re);
	}
	Complex operator/(const Complex& A, const double b) { return Complex(A.re / b, A.im / b); }
	Complex operator/=(Complex& A, const Complex& B) { return A = A / B; }
	Complex operator/=(Complex& A, const double b) { return A = A / b; }

	bool operator==(const Complex& A, const Complex& B) { return (A.re == B.re && A.im == B.im); }
	bool operator!=(const Complex& A, const Complex& B) { return !(A == B); }

	ostream& operator<<(ostream& os, const Complex& C)
	{
		if (C.re == 0)
		{
			if (C.im == 0) {
				os << "z = 0";
				return os;
			}
			else {
				os << "z = " << C.im << "i";
				return os;
			}
		}
		else {
			if (C.im == 0) {
				os << "z = " << C.re;
				return os;
			}
			else {
				os << "z = " << C.re << " + " << C.im << "i";
				return os;
			}
		}

		return os;
	}

	double arg(const Complex& C)
	{
		if (C.re == 0)
		{
			if (C.im > 0)
				return 90.0;
			if (C.im < 0)
				return 270.0;
			if (C.im == 0)
				return 0.0;
		}

		if (C.re > 0)
			return atan(C.im / C.re);

		if (C.re < 0)
		{
			if (C.im == 0)
				return 180.0;

			if (C.im > 0)
				return 180.0 + atan(C.im / C.re);

			if (C.im < 0)
				return -180.0 + atan(C.im / C.re);
		}
	}

	double abs(const Complex& C) { return std::sqrt(C.re * C.re + C.im * C.im); }

	Complex pow(const Complex& C, double n)
	{
		double tmp = std::pow(abs(C), n);
		double a = arg(C);

		return Complex(tmp * cos(n * a), tmp * sin(n * a));
	}
	
	Complex sqrt(const Complex& C, double n)
	{
		double tmp = std::pow(abs(C), 1 / n);
		double a = arg(C);

		return Complex(tmp * cos(a / n), tmp * sin(a / n));
	}
}