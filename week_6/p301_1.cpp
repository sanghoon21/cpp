#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct MyTime {
    int hour;
    int min;
    int sec;
    int msec;
};

// 모든 멤버를 0으로 초기화
void resetTime(MyTime &t) {
    t.hour = 0;
    t.min = 0;
    t.sec = 0;
    t.msec = 0;
}

// 초 단위(double)를 MyTime 구조체로 변환
MyTime convertTime(double duration) {
    MyTime t;
    int total_msec = static_cast<int>(round(duration * 1000));

    t.hour = total_msec / (3600 * 1000);
    total_msec %= 3600 * 1000;

    t.min = total_msec / (60 * 1000);
    total_msec %= 60 * 1000;

    t.sec = total_msec / 1000;
    t.msec = total_msec % 1000;

    return t;
}

// MyTime 출력
void printTime(const MyTime &t) {
    cout << setfill('0')
         << setw(2) << t.hour << ":"
         << setw(2) << t.min << ":"
         << setw(2) << t.sec << ":"
         << setw(3) << t.msec << endl;
}

// 두 시간 더하기
MyTime addTime(const MyTime &t1, const MyTime &t2) {
    MyTime result;
    result.msec = t1.msec + t2.msec;
    result.sec = t1.sec + t2.sec + result.msec / 1000;
    result.msec %= 1000;

    result.min = t1.min + t2.min + result.sec / 60;
    result.sec %= 60;

    result.hour = t1.hour + t2.hour + result.min / 60;
    result.min %= 60;

    return result;
}

int main() {
    double input1, input2;

    cout << "첫 번째 시간(초 단위 실수형): ";
    cin >> input1;

    cout << "두 번째 시간(초 단위 실수형): ";
    cin >> input2;

    MyTime time1 = convertTime(input1);
    MyTime time2 = convertTime(input2);

    cout << "첫 번째 시간: ";
    printTime(time1);

    cout << "두 번째 시간: ";
    printTime(time2);

    MyTime total = addTime(time1, time2);

    cout << "합계 시간: ";
    printTime(total);

    return 0;
}