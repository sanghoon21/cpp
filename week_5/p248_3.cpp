#include <iostream>
#include <cmath> // round 함수 사용

struct MyTime {
    int hour;   // 시
    int min;    // 분
    int sec;    // 초
    int msec;   // 밀리초
};

// 초 단위의 실수형 시간을 MyTime 구조체로 변환하는 함수
MyTime convertToMyTime(double totalSeconds) {
    MyTime t;

    // 초와 밀리초로 분리
    t.msec = static_cast<int>(round((totalSeconds - static_cast<int>(totalSeconds)) * 1000));  
    t.sec = static_cast<int>(totalSeconds) % 60;  

    // 분과 시 계산
    int totalMinutes = static_cast<int>(totalSeconds) / 60;
    t.min = totalMinutes % 60;
    t.hour = totalMinutes / 60;

    return t;
}

int main() {
    double inputSeconds = 3661.789; // 1시간 1분 1초 789밀리초
    MyTime result = convertToMyTime(inputSeconds);

    std::cout << "변환 결과: "
              << result.hour << "시간 "
              << result.min << "분 "
              << result.sec << "초 "
              << result.msec << "밀리초\n";

    return 0;
}
