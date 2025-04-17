#include <iostream>
using namespace std;

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex add(Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    void print() {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex a(1, 2), b(3, 4);
    Complex c = a.add(b);
    cout << "방식 4: ";
    c.print();
    return 0;
}