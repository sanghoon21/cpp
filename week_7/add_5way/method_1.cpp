// 모든 코드의 기본 흐름
// 두 복소수 a, b를 생성
// 덧셈 함수를 호출하여 c에 결과 저장
// 출력 함수로 결과 확인


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

//3. 각각 a, b, c를 가리킴, result가 함수 내부에서 직접 계산되어 바뀜
void add(Complex& a, Complex& b, Complex& result) {
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
}

int main() {
    Complex a(1, 2), b(3, 4), c;  // 1. a, b, c 객체 생성 (복소수 만들기)
                                // () + ()i 형태의 복소수가 생성됨
    
    // 2. a, b 값(복소수)을 참조로 함수에 전달, c도 참조로 전달하여 함수 안에서 값을 직접 채움
    add(a, b, c);

    cout << "1. 일반 함수 (void, 참조 전달): ";
    c.print();
    return 0;
}
