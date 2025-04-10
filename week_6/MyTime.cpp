#include "MyTime.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// 생성자
MyTime::MyTime() {
    reset();
}

// 초 단위 시간 변환
void MyTime::convert(double duration) {
    int total_msec = static_cast<int>(round(duration * 1000));
    hour = total_msec / (3600 * 1000);
    total_msec %= 3600 * 1000;
    min = total_msec / (60 * 1000);
    total_msec %= 60 * 1000;
    sec = total_msec / 1000;
    msec = total_msec % 1000;
}

// 시간 출력
void MyTime::print() {
    cout << setfill('0')
         << setw(2) << hour << ":"
         << setw(2) << min << ":"
         << setw(2) << sec << ":"
         << setw(3) << msec << endl;
}

// 시간 초기화
void MyTime::reset() {
    hour = min = sec = msec = 0;
}

// 시간 덧셈
MyTime MyTime::add(MyTime t) {
    MyTime result;
    result.msec = msec + t.msec;
    result.sec = sec + t.sec + result.msec / 1000;
    result.msec %= 1000;
    result.min = min + t.min + result.sec / 60;
    result.sec %= 60;
    result.hour = hour + t.hour + result.min / 60;
    result.min %= 60;
    return result;
}

// 사용자 입력 받기
void MyTime::read() {
    double duration;
    cout << "초 단위 시간(double)을 입력하세요: ";
    cin >> duration;
    convert(duration);
}
