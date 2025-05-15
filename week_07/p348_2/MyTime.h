#ifndef MYTIME_H
#define MYTIME_H

class MyTime {
private:
    int hour; // 시간
    int min;  // 분
    int sec;  // 초
    int msec; // 밀리초

public:
    MyTime();                      // 기본 생성자

    // *추가(1번): 새로운 매개변수 생성자(시, 분, 초, 밀리초) 선언 추가.
    MyTime(int h, int m, int s, int ms);

    // *추가(2번): 새로운 매개변수 생성자 (초 단위 실수형 시간)
    MyTime(double duration);

    void convert(double duration); // 초 단위 시간을 시:분:초:밀리초로 변환
    void print();                  // 시간 출력
    MyTime add(MyTime t);          // 두 시간 더하기
    void reset();                  // 시간 초기화
    void read();                   // 사용자 입력 받기
};

#endif