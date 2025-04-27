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

// 2. a, b가 add() 함수에 입력되어 또다른 객체가 반환(return)됨
// add()에 입력되어서 계산된 값(Complex형(복소수 형태) 객체)을 반환하여 c에 대입
Complex add(Complex a, Complex b) {
    // add 함수가 리턴되며 생성된 객체가 c에 대입됨
    return Complex(a.real + b.real, a.imag + b.imag);
}

int main() {
    Complex a(1, 2), b(3, 4), c;  //c -> 먼저 선언(생성) 후 아래에서 값 대입(초기화)
    
    // 1. a, b가 값으로 전달되며 복사됨, 함수가 결과값 Complex를 리턴하고 이를 c에 대입
    c = add(a, b);
    
    cout << "2. 일반 함수 (return, 값 전달): ";
    c.print();
    return 0;
}