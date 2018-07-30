#pragma once
#include<iostream>
#include<math.h>

using namespace std;

template<typename T>
class Complex
{
private:
	T re, im;
public:
	explicit Complex(T r, T i) : re(r), im(i)
	{
		static_assert(std::is_floating_point<T>::value, "the template parameter must be a floating-point type");
	}
	explicit Complex(T r) : re(r), im(0.0) 
	{
		static_assert(std::is_floating_point<T>::value, "the template parameter must be a floating-point type");
	}
	explicit Complex() : re(0.0), im(0.0) 
	{
		static_assert(std::is_floating_point<T>::value, "the template parameter must be a floating-point type");
	}

	T real() { return re; }
	T imagin() { return im; }

	friend Complex operator+(const Complex& A, const Complex& B) { return Complex(A.re + B.re, A.im + B.im); }
	friend Complex operator+(const Complex& A, const T b) { return Complex(A.re + b, A.im); }
	friend Complex operator+=(Complex& A, const Complex& B) { return A = A + B; }
	friend Complex operator+=(Complex& A, const T b) { return A = A + b; }

	friend Complex operator-(const Complex& A, const Complex& B) { return Complex(A.re - B.re, A.im - B.im); }
	friend Complex operator-(const Complex& A, const T b) { return Complex(A.re - b, A.im); }
	friend Complex operator-=(Complex& A, const Complex& B) { return A = A - B; }
	friend Complex operator-=(Complex& A, const T b) { return A = A - b; }

	friend Complex operator*(const Complex& A, const Complex& B)
	{
		Complex C;
		C.re = A.re * B.re + A.im * B.im * (-1);
		C.im = A.re * B.im + A.im * B.re;
		return C;
	}
	friend Complex operator*(const Complex& A, const T b) { return Complex(A.re * b, A.im * b); }
	friend Complex operator*=(Complex& A, const Complex& B) { return A = A * B; }
	friend Complex operator*=(Complex& A, const T b) { return A = A * b; }

	friend Complex operator/(const Complex& A, const Complex& B)
	{
		Complex tmp(B.re, B.im * (-1));

		Complex N = A * tmp;
		Complex D = B * tmp;

		return Complex(N.re / D.re, N.im / D.re);
	}
	friend Complex operator/(const Complex& A, const T b) { return Complex(A.re / b, A.im / b); }
	friend Complex operator/=(Complex& A, const Complex& B) { return A = A / B; }
	friend Complex operator/=(Complex& A, const T b) { return A = A / b; }

	friend bool operator==(const Complex& A, const Complex& B) { return (A.re == B.re && A.im == B.im); }
	friend bool operator!=(const Complex& A, const Complex& B) { return !(A == B); }

	friend ostream& operator<<(ostream& os, const Complex& C)
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

	T arg(const Complex& C)
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

	T abs(const Complex& C) { return std::sqrt(C.re * C.re + C.im * C.im); }

	Complex pow(const Complex& C, T n)
	{
		T tmp = std::pow(abs(C), n);
		T a = arg(C);

		return Complex(tmp * cos(n * a), tmp * sin(n * a));
	}
	
	Complex sqrt(const Complex& C, T n)
	{
		T tmp = std::pow(abs(C), 1 / n);
		T a = arg(C);

		return Complex(tmp * cos(a / n), tmp * sin(a / n));
	}
};