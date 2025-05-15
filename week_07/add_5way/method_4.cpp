#include <iostream>
using namespace std;

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex add(Complex& other) {
        return Complex(real + other.real, imag + other.imag);
        // real은 a.real
        // other.real은 b.real
    }

    void print() {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex a(1, 2), b(3, 4), c;

    // 1. a에 b가 더해지게 되고, 더해진 결과(새 객체)가 반환되어 이를 c에 대입.
    c = a.add(b);
    cout << "4. 멤버 함수 (return, 참조 전달): ";
    c.print();
    return 0;
}


// a 객체의 add 멤버함수 호출, b라는 복소수 객체(3 + 4i)를 참조로 가리킴(other),
// 참조한 b의 실수부와 허수부를 add함수를 호출한 객체인 a의 실수부와 허수부에 더함.
// 더한 결과(새로운 객체)를 반환해서 c 객체에 대입 (c도 Complex형 객체임)