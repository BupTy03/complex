#include <iostream>
#include <string>
#include <stdexcept>
#include "complex.hpp"

using namespace std;

int main()
{
	constexpr Complex<float> A{2.0, 4.2};
	constexpr Complex<float> B{5.4};
	constexpr Complex<float> C;

	try{
		cout << "A + B = " << A + B << endl;
		cout << "A - B = " << A - B << endl;
		cout << "A * B = " << A * B << endl;
		cout << "A / B = " << A / B << endl;
		cout << "A / C = " << A / C << endl;
		cout << "A / 0 = " << A / 0.0 << endl;
		cout << "arg(A) = " << to_degrees(arg(A)) << endl;
		cout << "sqrt(A) = " << sqrt(A) << endl;
		cout << "pow(A) = " << pow(A) << endl;
		cout << "abs(A) = " << abs(A) << endl;
	}
	catch(runtime_error& err){
		cout << err.what() << endl;
	}

	return 0;
}
