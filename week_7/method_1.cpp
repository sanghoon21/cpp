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

void add(Complex& a, Complex& b, Complex& result) {
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
}

int main() {
    Complex a(1, 2), b(3, 4), c;
    add(a, b, c);
    cout << "방식 1: ";
    c.print();
    return 0;
}
