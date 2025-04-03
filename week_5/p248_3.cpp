#include <iostream>
#include <iomanip> // setw, setfill 사용
#include <cmath>   // round 함수 사용

struct MyTime {
    int hour;   // 시
    int min;    // 분
    int sec;    // 초
    int msec;   // 밀리초
};

// MyTime 객체를 HH:MM:SS:MMM 형식으로 출력하는 함수
void printTime(MyTime duration) {
    std::cout << std::setfill('0') 
              << std::setw(2) << duration.hour << ":"  
              << std::setw(2) << duration.min << ":"
              << std::setw(2) << duration.sec << ":"
              << std::setw(3) << duration.msec  
              << std::endl;
}

// 사용자 입력을 받아 MyTime 객체 생성
MyTime inputTime() {
    MyTime t;
    std::cout << "시간 입력 (HH MM SS MMM): ";
    std::cin >> t.hour >> t.min >> t.sec >> t.msec;
    return t;
}

/*
    ✅ 방법 1: 반환값을 이용하여 두 개의 시간을 더하는 함수
    - 새로운 MyTime 객체를 반환하는 방식
    - 함수 내에서 결과를 계산한 후 반환
    - 불필요한 객체 복사가 발생할 수 있어 성능상 비효율적일 수도 있음
*/
MyTime addTime(MyTime t1, MyTime t2) {
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

/*
    ✅ 방법 2: 참조 매개변수를 사용하여 두 개의 시간을 더하는 함수
    - 참조 매개변수를 사용하여 결과를 직접 저장
    - 함수 호출 시 객체를 복사하지 않으므로 성능이 좋음
    - nullptr 체크가 필요하지 않음
*/
void addTime(MyTime t1, MyTime t2, MyTime& t3) {
    t3.msec = t1.msec + t2.msec;
    t3.sec = t1.sec + t2.sec + t3.msec / 1000;
    t3.msec %= 1000;

    t3.min = t1.min + t2.min + t3.sec / 60;
    t3.sec %= 60;

    t3.hour = t1.hour + t2.hour + t3.min / 60;
    t3.min %= 60;
}

/*
    ✅ 방법 3: 포인터 매개변수를 사용하여 두 개의 시간을 더하는 함수
    - 포인터 매개변수를 사용하여 결과를 저장
    - 함수 내부에서 nullptr 체크가 필요함
    - 참조 방식과 비슷하지만, 포인터를 사용해야 한다는 점에서 차이가 있음
*/
void addTime(MyTime t1, MyTime t2, MyTime* pt) {
    if (pt) { // nullptr 방지
        pt->msec = t1.msec + t2.msec;
        pt->sec = t1.sec + t2.sec + pt->msec / 1000;
        pt->msec %= 1000;

        pt->min = t1.min + t2.min + pt->sec / 60;
        pt->sec %= 60;

        pt->hour = t1.hour + t2.hour + pt->min / 60;
        pt->min %= 60;
    }
}

int main() {
    // 사용자로부터 두 개의 시간 입력받기
    MyTime t1 = inputTime();
    MyTime t2 = inputTime();

    // 방법 1 테스트
    MyTime result1 = addTime(t1, t2);
    std::cout << "방법 1 (반환값 사용): ";
    printTime(result1);

    // 방법 2 테스트
    MyTime result2;
    addTime(t1, t2, result2);
    std::cout << "방법 2 (참조 사용): ";
    printTime(result2);

    // 방법 3 테스트
    MyTime result3;
    addTime(t1, t2, &result3);
    std::cout << "방법 3 (포인터 사용): ";
    printTime(result3);

    return 0;
}

