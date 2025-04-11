//MyTime.cpp : MyTime 클래스의 함수들을 실제로 정의.
    // (멤버 함수들이 어떻게 작동하는지 구현됨)

#include "MyTime.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// 생성자
MyTime::MyTime() {
    reset();
}


// 2. 초 단위 시간 변환 (시 분 초 밀리초를 차례로 게산하여 클래스 내부 멤버에 저장)
void MyTime::convert(double duration) {
    int total_msec = static_cast<int>(round(duration * 1000));
    hour = total_msec / (3600 * 1000);
    total_msec %= 3600 * 1000;
    min = total_msec / (60 * 1000);
    total_msec %= 60 * 1000;
    sec = total_msec / 1000;
    msec = total_msec % 1000;
}


// 4. 시간 출력 : 내부 시간 데이터를 출력 
// 입출력 조작자를 사용하여 숫자를 원하는 자리 수만큼 출력하고, 빈 자리는 0 채우기
void MyTime::print() {
    cout << setfill('0')  //빈칸 0으로 채워라
         << setw(2) << hour << ":"  //숫자를 2자리로 만들어서 출력하라
         << setw(2) << min << ":"
         << setw(2) << sec << ":"
         << setw(3) << msec << endl;
}


// 5. 모든 시간 필드를 0으로 초기화
void MyTime::reset() {
    hour = min = sec = msec = 0;
}


// 3. 시간 덧셈 : 두 시간 객체의 각 요소를 더하고 넘치는 값 이월 처리
MyTime MyTime::add(MyTime t) {
    MyTime result;
    result.msec = msec + t.msec;  //t1 + t2 = result
    result.sec = sec + t.sec + result.msec / 1000;
    result.msec %= 1000;
    result.min = min + t.min + result.sec / 60;
    result.sec %= 60;
    result.hour = hour + t.hour + result.min / 60;
    result.min %= 60;
    return result;
}


//1. 사용자 메시지 출력 후 실수형 시간 입력 받기
void MyTime::read() {
    double duration;
    cout << "초 단위 시간(double)을 입력하세요: ";
    cin >> duration;
    convert(duration);   //convert()함수 호출로 초를 시:분:초:밀리초로 분해
}