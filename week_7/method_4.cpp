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
    Complex a(1, 2), b(3, 4), c;
    c = a.add(b);
    cout << "4. 멤버 함수 (return, 참조 전달): ";
    c.print();
    return 0;
}