#include <iostream>
using namespace std;

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex operator+(Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    void print() {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex a(1, 2), b(3, 4);  
    Complex c = a + b;  //c -> 앞선 4개와 다르게 선언과 동시에 초기화 하는 방식
    cout << "5. 연산자 오버로딩: ";
    c.print();
    return 0;
}
