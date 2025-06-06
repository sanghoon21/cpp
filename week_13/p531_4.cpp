#include <iostream>
#include <cstdlib> // rand()를 위해 필요
using namespace std;

class SampleList 
{
// SampleList 클래스는 list라는 이름의 int 타입 배열을 멤버 변수로 가짐
// 크기는 100으로 고정됨.
    int list[100];

public:
// SampleList 객체 생성되면 생성자 호출됨.
// 생성자 내부에서 for 루프가 실행, 인덱스 x는 0 -> 99까지 반복됨.
  // 각 반복에서 0 ~ 999 사이의 임의의 정수 생성. 생성된 값을 list[x]에 저장.
  // => list 배열의 100개 요소가 각각 0 ~ 999 사이의 무작위 값으로 초기화됨.
    SampleList() {
        for (int x = 0; x < 100; x++) {
            list[x] = rand() % 1000;
        }
    }
// 결과적으로 객체 생성이 완료되면, list 배열은 무작위 값으로 채워진 상태가 됨.
// ex) SampleList sl; 호출 => sl.list는 {742, 19, 453, ..., 128} 같은 형태로 초기화될 수 있음.
// 0에 742, 1에 19 ...



//! 연산자 중복
//! 원래 C++에서 구현된 []와 ()에 해당하는 기능대로 쓰지 않고, 내가 쓰고 싶은 대로 중복 정의해서 사용함.
    // (1) 인덱스 연산자 중복
// operator[]는 주어진 index에 해당하는 list 배열의 요소를 int& 타입으로 반환.
//! 원래 []는 배열이나 컨테이너에 대해 요소 접근을 의미하지만,
//! SampleList 클래스에서는 list 배열에 접근하는 방식으로 동작을 중복 정의함.

    int& operator[](int index) 
    {
        return list[index];
    }

    // (2) 함수 호출 연산자 중복 (단일 인덱스)
// operator()도 주어진 index에 해당하는 list 배열의 요소를 int& 타입으로 반환.
//! 원래 ()는 함수 호출을 의미하지만,
//! SampleList 에서는 배열 요소 접근(단일 인덱스 또는 두 수의 곱을 인덱스로 사용)으로 동작을 중복 정의함.
    int& operator()(int index) {
        return list[index];
    }

    // (3) 함수 호출 연산자 중복 (두 수의 곱)
// operator()(int a, int b)는 a * b를 계산한 값에 해당하는 인덱스의 list 요소를 int& 타입으로 반환.
    int& operator()(int a, int b) {
        return list[a * b];
    }
};

// 메인함수로 테스트.
int main() {
    // 객체 생성
    SampleList sl;

    // sl[5]로 5번째 인덱스 값 확인
    cout << "sl[5]: " << sl[5] << endl;

    // sl(5)로 5번째 인덱스 값 확인
    cout << "sl(5): " << sl(5) << endl;

    // sl(2, 3)로 6번째 인덱스 값 확인
    cout << "sl(2, 3): " << sl(2, 3) << endl;

    return 0;
}
