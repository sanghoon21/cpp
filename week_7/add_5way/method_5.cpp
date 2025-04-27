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


    Complex c = a + b;            //c -> 앞선 4개와 다르게 선언과 동시에 초기화 하는 방식
        // 코드상으로는 + 이지만, 실제로는 a.operator+(b) 로 해석됨.(멤버 함수 호출과 동일)
            // a 객체가 operator+() 함수를 호출하였으니, a 객체의 실수부와 허수부에 더해야 한다. 무엇을?
                // b 객체의 실수부와 허수부를 a 객체의 실수부와 허수부에 더해야 함.
                // (이전의 add와 동일하지만, 좀 더 직관적. [+ 로 나타내서])
        // 겉으로 보기에는 + 연산자를 사용하는 것 처럼 보이지만, 멤버 함수 호출이라는 것
        // operator+() 함수의 반환(더해진 결과인 새로운 객체)을 c 에 대입.
    cout << "5. 연산자 오버로딩: ";
    c.print();
    return 0;
}

