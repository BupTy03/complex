#include <iostream>
#include "Complex.h"

using namespace std;
using namespace MyLib;

int main()
{
    Complex A(1,5);// с = a + bi
    Complex B(1,5);

    print(A + B);
    print(A - B);
    print(A * B);
    print(A / B);

    if(A == B)
        cout << "A == B" << endl;
    else cout << "A != B" << endl;


    return 0;
}