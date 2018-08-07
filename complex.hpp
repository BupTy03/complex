#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>

template<typename T>
constexpr inline T to_degrees(T x) noexcept
{
	static_assert(std::is_floating_point<T>::value, "the template parameter must be a floating-point type");
	return x * 180.0 / M_PI;
}

struct Complex_error : std::runtime_error{
	explicit Complex_error(const char* q) : std::runtime_error(q){}
	explicit Complex_error(const std::string& s) : std::runtime_error(s){}
};

void error(const char* name)
{
	throw Complex_error(name);
}

template<typename T>
class Complex
{
private:
	T re, im;
public:
	constexpr explicit Complex(T r, T i) noexcept  : re(r), im(i)
	{
		static_assert(std::is_floating_point<T>::value, "the template parameter must be a floating-point type");
	}
	constexpr explicit Complex(T r) noexcept : re(r), im(0.0)
	{
		static_assert(std::is_floating_point<T>::value, "the template parameter must be a floating-point type");
	}
	constexpr Complex() noexcept : re(0.0), im(0.0)
	{
		static_assert(std::is_floating_point<T>::value, "the template parameter must be a floating-point type");
	}

	constexpr inline T real() noexcept { return re; }
	constexpr inline T imagin() noexcept { return im; }

	constexpr friend Complex operator+(const Complex& A, const Complex& B) noexcept { return Complex(A.re + B.re, A.im + B.im); }
	constexpr friend Complex operator+(const Complex& A, const T b) noexcept { return Complex(A.re + b, A.im); }
	constexpr friend Complex operator+=(Complex& A, const Complex& B) noexcept { return A = A + B; }
	constexpr friend Complex operator+=(Complex& A, const T b) noexcept { return A = A + b; }

	constexpr friend Complex operator-(const Complex& A, const Complex& B) noexcept { return Complex(A.re - B.re, A.im - B.im); }
	constexpr friend Complex operator-(const Complex& A, const T b) noexcept { return Complex(A.re - b, A.im); }
	constexpr friend Complex operator-=(Complex& A, const Complex& B) noexcept { return A = A - B; }
	constexpr friend Complex operator-=(Complex& A, const T b) noexcept { return A = A - b; }

	constexpr friend Complex operator*(const Complex& A, const Complex& B) noexcept { return Complex(A.re * B.re - A.im * B.im, A.re * B.im + A.im * B.re); }
	constexpr friend Complex operator*(const Complex& A, const T b) noexcept { return Complex(A.re * b, A.im * b); }
	constexpr friend Complex operator*=(Complex& A, const Complex& B) noexcept { return A = A * B; }
	constexpr friend Complex operator*=(Complex& A, const T b) noexcept { return A = A * b; }

	constexpr friend Complex operator/(const Complex& A, const Complex& B)
	{
		if(B.re == 0 && B.im == 0)
			error("division by zero");

		Complex tmp(B.re, B.im * (-1));

		Complex N = A * tmp;
		Complex D = B * tmp;

		return Complex(N.re / D.re, N.im / D.re);
	}
	constexpr inline friend Complex operator/(const Complex& A, const T b) 
	{ 
		if(b == 0)
			error("division by zero");

		return Complex(A.re / b, A.im / b); 
	}
	constexpr friend Complex operator/=(Complex& A, const Complex& B) { return A = A / B; }
	constexpr friend Complex operator/=(Complex& A, const T b) { return A = A / b; }

	constexpr inline friend bool operator==(const Complex& A, const Complex& B) noexcept { return (A.re == B.re && A.im == B.im); }
	constexpr inline friend bool operator!=(const Complex& A, const Complex& B) noexcept { return !(A == B); }

	friend std::ostream& operator<<(std::ostream& os, const Complex& C)
	{
		if (C.re == 0)
		{
			if (C.im == 0)
				os << "0";
			else
				os << C.im << "i";
		}
		else {
			if (C.im == 0)
				os << C.re;
			else if(C.im > 0)
				os << C.re << " + " << C.im << "i";
			else
				os << C.re << " " << C.im << "i"; 
		}

		return os;
	}

	friend T arg(const Complex& C)
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
			return atan2(C.im, C.re);

		if (C.re < 0)
		{
			if (C.im == 0)
				return 180.0;

			if (C.im > 0)
				return atan2(C.im, C.re) + 180.0;

			if (C.im < 0)
				return atan2(C.im, C.re) - 180.0;
		}
	}

	friend T abs(const Complex& C) { return sqrt(C.re * C.re + C.im * C.im); }

	friend Complex pow(const Complex& C, T n = 2.0)
	{
		T tmp = pow(abs(C), n);
		T a = arg(C);

		return Complex(tmp * cos(n * a), tmp * sin(n * a));
	}
	
	friend Complex sqrt(const Complex& C, T n = 2.0)
	{
		T tmp = pow(abs(C), 1 / n);
		T a = arg(C);

		return Complex(tmp * cos(a / n), tmp * sin(a / n));
	}
};
