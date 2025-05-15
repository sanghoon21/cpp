//총 3개의 파일로 구성

//MyTime.h : 클래스의 멤버 변수와 멤버 함수들의 선언만 포함되어있음
    //다른 파일에서 #include "MyTime.h"를 통해 MyTime 클래스를 사용할 수 있게 함



#ifndef MYTIME_H
#define MYTIME_H

class MyTime {
private:
    int hour;
    int min;
    int sec;
    int msec;

public:
    MyTime();                      // 생성자
    void convert(double duration); // 초 단위 시간 변환
    void print();                  // 시간 출력
    MyTime add(MyTime t);          // 시간 더하기
    void reset();                  // 시간 초기화
    void read();                   // 사용자 입력 받기
};

#endif
