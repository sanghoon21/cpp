#include <iostream>
using namespace std;

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // 2. 멤버 함수 정의
    //     c 객체의 내부 멤버(real, imag)를 직접 수정함.
    void add(Complex& a, Complex& b) {
        real = a.real + b.real;
        imag = a.imag + b.imag;
    }

    //3. 수정된 멤버변수(real, imag)를 복소수 형태로 출력
    void print() {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex a(1, 2), b(3, 4), c;

    // 1. 객체 c가 맴버함수 add() 호출 -> a, b를 참조로 넘겨받아서 자기 자신인 c를 수정.
    c.add(a, b);  //c 객체가 멤버 함수 호출자. "내가 계산 결과를 가질게!"라는 의미.
    cout << "3. 멤버 함수 (void, 참조 전달): ";
    c.print();
    return 0;
}
