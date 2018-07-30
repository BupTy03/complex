#include <iostream>
#include "complex.hpp"

using namespace std;

int main()
{
	Complex<float> A{2.0, 4.2};
	Complex<float> B{5.4};

	cout << A + B << endl;

	return 0;
}