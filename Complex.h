#pragma once

#include <iostream>

using namespace std;

namespace MyLib
{
	class Complex
	{
	private:
		double re, im;
	public:
		Complex(double r, double i) : re(r), im(i) {}
		Complex(double r) : re(r), im(0.0) {}
		Complex() : re(0.0), im(0.0) {}

		double real();
		double imagin();

		friend Complex operator+(const Complex&, const Complex&);
		friend Complex operator+(const Complex&, const double);
		friend Complex operator+=(const Complex&, const Complex&);
		friend Complex operator+=(const Complex&, const double);

		friend Complex operator-(const Complex&, const Complex&);
		friend Complex operator-(const Complex&, const double);
		friend Complex operator-=(const Complex&, const Complex&);
		friend Complex operator-=(const Complex&, const double);

		friend Complex operator*(const Complex&, const Complex&);
		friend Complex operator*(const Complex&, const double);
		friend Complex operator*=(const Complex&, const Complex&);
		friend Complex operator*=(const Complex&, const double);

		friend Complex operator/(const Complex&, const Complex&);
		friend Complex operator/(const Complex&, const double);
		friend Complex operator/=(const Complex&, const Complex&);
		friend Complex operator/=(const Complex&, const double);

		friend bool operator==(const Complex&, const Complex&);
		friend bool operator!=(const Complex&, const Complex&);

		friend ostream& operator<<(ostream&, const Complex&);

		friend void print(const Complex&);
		friend double arg(const Complex&);
		friend double abs(const Complex&);
		friend Complex pow(const Complex& C, double n = 2.0);
		friend Complex sqrt(const Complex& C, double n = 2.0);

		~Complex() {}
	};
}
