#include <iostream>
using namespace std;

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    void print() {
        cout << real << " + " << imag << "i" << endl;
    }
};

Complex add(Complex a, Complex b) {
    return Complex(a.real + b.real, a.imag + b.imag);
}

int main() {
    Complex a(1, 2), b(3, 4);
    Complex c = add(a, b);
    cout << "방식 2: ";
    c.print();
    return 0;
}
