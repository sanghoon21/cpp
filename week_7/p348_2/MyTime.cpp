#include "MyTime.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//                      (1번 추가 사항)

// -----멤버 초기화 리스트 미사용 (사용X -> 주석처리)-----------------------------
// 기본 생성자: reset() 호출로 모든 멤버를 0으로 초기화
MyTime::MyTime() {
    reset();
}

// 매개변수 생성자: 매개변수 값을 직접 할당. 시, 분, 초, 밀리초를 받아 초기화
MyTime::MyTime(int h, int m, int s, int ms) {
    hour = h;
    min = m;
    sec = s;
    msec = ms;
}
// -------------------------------------------------------------------------------------


// -----멤버 초기화 리스트를 사용한 생성자 (사용X -> 주석처리)------------------------------------
// // 기본 생성자: 멤버 초기화 리스트로 모든 멤버를 0으로 초기화
// MyTime::MyTime() : hour(0), min(0), sec(0), msec(0) {
// }

// // 매개변수 생성자: 멤버 초기화 리스트로 매개변수 값을 직접 초기화
// MyTime::MyTime(int h, int m, int s, int ms) : hour(h), min(m), sec(s), msec(ms) {
// }
// ------------------------------------------------------------------------------------


// 매개변수 생성자: 초 단위 실수형 시간을 받아 초기화 (2번 추가사항)
MyTime::MyTime(double duration) {
    // 이전: 객체 생성 후 초기화 단계를 별도로 진행, (사용자 입력이나 별도 초기화 호출이 필요한 상황에 적합.)
        // 기본 생성자 MyTime()으로 객체를 생성하고,
        // 객체 생성 후 추가적인 함수(read, convert)를 호출하여 초기화(값대입)해야함.
        // 그 전까지 객체는 기본값(hour=0, min=0, sec=0, msec=0)으로만 존재함.
    // 현재: 객체가 생성될 때, 바로 실수형 시간(double duration)을 입력받아 초기화(값대입)됨.
        // 초기화가 생성자 호출과 함께 즉시 이루어지기에, 객체가 만들어진 직후부터 유효한 시간데이터 가짐.
        // 예) MyTime t(3661.5);
        // -> 객체 생성과 동시에 3661.5초가 hour=1, min=1, sec=1, msec=500으로 변환되어 저장
    convert(duration);
}




// 2. 초 단위 시간을 시:분:초:밀리초로 변환 (시 분 초 밀리초를 차례로 게산하여 클래스 내부 멤버에 저장)
void MyTime::convert(double duration) {
    int total_msec = static_cast<int>(round(duration * 1000));
    hour = total_msec / (3600 * 1000); // 시간 계산
    total_msec %= 3600 * 1000;
    min = total_msec / (60 * 1000);    // 분 계산
    total_msec %= 60 * 1000;
    sec = total_msec / 1000;           // 초 계산
    msec = total_msec % 1000;          // 밀리초 계산
}

// 4. 시간 출력 : 내부 시간 데이터를 지정된 형식으로 출력 
// 입출력 조작자를 사용하여 숫자를 원하는 자리 수만큼 출력하고, 빈 자리는 0 채우기
void MyTime::print() {
    cout << setfill('0')               // 빈칸을 0으로 채움
         << setw(2) << hour << ":"     // 시간 2자리 출력
         << setw(2) << min << ":"      // 분 2자리 출력
         << setw(2) << sec << ":"      // 초 2자리 출력
         << setw(3) << msec << endl;   // 밀리초 3자리 출력
}

// 5. 시간 초기화: 모든 시간 필드를 0으로 설정
void MyTime::reset() {
    hour = min = sec = msec = 0;
}

// 3. 시간 덧셈: 두 시간 객체를 더하고 넘치는 값 이월 처리
MyTime MyTime::add(MyTime t) {
    MyTime result;
    result.msec = msec + t.msec;       // 밀리초 더하기
    result.sec = sec + t.sec + result.msec / 1000; // 초 더하기 및 밀리초 이월
    result.msec %= 1000;
    result.min = min + t.min + result.sec / 60;    // 분 더하기 및 초 이월
    result.sec %= 60;
    result.hour = hour + t.hour + result.min / 60; // 시간 더하기 및 분 이월
    result.min %= 60;
    return result;
}

//1. 사용자 메시지 출력 후 실수형 시간 입력 받기
void MyTime::read() {
    double duration;
    cout << "초 단위 시간(double)을 입력하세요: ";
    cin >> duration;
    convert(duration); // convert()함수를 호출해서, 입력된 초를 시:분:초:밀리초로 변환
}