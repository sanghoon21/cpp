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
