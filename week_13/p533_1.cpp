#include <iostream>
#include <iomanip>
#include <stdexcept>

// operator+(const TimeHMS& other)
// (const TimeHMS& other) => 중복 정의한 연산자를 사용한 연산에 참여하는? 존재. t2.
// t1: 연산 당하는 존재?

class TimeHMS {
    int hour, min, sec;
public:
    TimeHMS(int h = 0, int m = 0, int s = 0) : hour(h), min(m), sec(s) {}
// other 는 TimeHMS 클래스의 참조 타입 객체.
//     연산에 참여하는 두 번째 TimeHMS 객체를 나타냄. (여기에서 t2)
//     t3 = t1 + t2를 호출할 때: t2는 other 매개변수로 전달되며, const TimeHMS& 타입으로 참조됨.
// const로 other가 읽기 전용으로 사용되도록 설정.


    // (1) + 연산자 중복: 시간 더하기
// !+ 연산자는 두 TimeHMS 객체의 시간을 더함.
// 두 객체의 초, 분, 시를 각각 더한 뒤, 초가 60 이상이면 분으로, 분이 60 이상이면 시로 올림 처리.
// 결과는 새로운 TimeHMS 객체로 반환.
    TimeHMS operator+(const TimeHMS& other) const {
        int totalSec = sec + other.sec;
        int carryMin = totalSec / 60;
        int newSec = totalSec % 60;
        int totalMin = min + other.min + carryMin;
        int carryHour = totalMin / 60;
        int newMin = totalMin % 60;
        int newHour = hour + other.hour + carryHour;
        return TimeHMS(newHour, newMin, newSec);
        // TimtHMS 클래스의 새로운 객체를 생성하여 반환함. 이 반환값이 t3에 저장됨.
    }


    // (2) - 연산자 중복: 시간 빼기
// !- 연산자는 첫 번째 객체에서 두 번째 객체의 시간을 뺌.
// 시간을 초 단위로 변환 후 빼기를 수행.
// 결과가 음수면 0으로 설정. 초를 다시 시, 분, 초로 변환해 반환.
    TimeHMS operator-(const TimeHMS& other) const {
        int totalSec1 = hour * 3600 + min * 60 + sec;
        int totalSec2 = other.hour * 3600 + other.min * 60 + other.sec;
        int diffSec = abs(totalSec1 - totalSec2);  // abs = 절대값 사용 (두 시간의 절대적 차이)
        int newHour = diffSec / 3600;
        diffSec %= 3600;  // diffSec 값을 3600으로 나눈 나머지로 갱신한다는 것. (ex. diffSec이 3670s => 시로 3600s 쓰고, 남은 70초만 남김)
        int newMin = diffSec / 60;
        int newSec = diffSec % 60;
        return TimeHMS(newHour, newMin, newSec);
    }


    // (3) ==, != 연산자 중복: 시간 비교
//! ==는 두 객체의 시, 분, 초가 모두 같은지 확인, !=는 그 반대.
// 세 멤버 변수를 비교해 동일하면 true 반환. !=는 == 결과를 부정.
    bool operator==(const TimeHMS& other) const {
        return hour == other.hour && min == other.min && sec == other.sec;
    }           
    bool operator!=(const TimeHMS& other) const {
        return !(*this == other);  // 이미 정의한 == 연산자를 재사용하여 구현.
    }         // t1, t2가 같지 않으면 (!) true 반환. 같으면 false 반환.


    // (4) 전위 증감 연산자: 한 시간 증감. (++t1)
//! 전위 ++는 시간을 1시간 증가, --는 1시간 감소. (음수 시간은 방지.)
// ++는 hour를 1 증가시키고, --는 hour가 0보다 크면 1 감소
    TimeHMS& operator++() {  //? 전위 증감 연산자: 매개변수 X, 객체를 직접 1시간 증가 또는 감소시킴.
        hour++;
        return *this;    //? 반환값은 변경된 자기 자신을 참조로 반환.
    }
    TimeHMS& operator--() {
        if (hour > 0) hour--;
        return *this;
    }
// 객체 자체를 수정한 후 참조(TimeHMS&)를 반환해 연속적인 연산을 지원함.


    // (5) 후위 증감 연산자: 1초 증감. (t1++)
//! 1초를 증감시키며, 초가 60 이상이거나 0 미만이면 분과 시를 조정.
// 후위 연산은 현재 객체를 복사해 반환, 본 객체는 초 단위로 증감. 초가 벗어나면 분과 시를 조정.
    TimeHMS operator++(int) {  //? 후위 증감 연산자: int라는 더미 매개변수(단지 구분을 위한. 실제로 값 받지 X)를 넣어서 후위 연산자임을 구분. => 호출될 때 ++(int)로 되어 있어서 컴파일러가 후위 증감 연산자로 인식.
        TimeHMS temp = *this;
        sec++;
        if (sec >= 60) {
            sec -= 60;
            min++;
            if (min >= 60) {
                min -= 60;
                hour++;
            }
        }
        return temp;  //? 반환값은 변경 전 복사본. 실제 객체(t1)는 1초 단위로 변화.
    }
    TimeHMS operator--(int) {
        TimeHMS temp = *this;
        sec--;
        if (sec < 0) {
            sec += 60;
            min--;
            if (min < 0) {
                min += 60;
                if (hour > 0) hour--;
            }
        }
        return temp;
    }


    // (6) 인덱스 연산자: 시, 분, 초 반환
//! 인덱스 0, 1, 2가 각각 시, 분, 초를 반환하도록 정의.
// 유효하지 않은 인덱스는 예외 발생. (그 외 값(예: t[3])은 예외 발생)
    int operator[](int index) const {
        if (index == 0) return hour;  // t[0]이면 hour 반환
        if (index == 1) return min;
        if (index == 2) return sec;
        throw std::out_of_range("Index out of range");
    }


    // (7) int 형 변환: 초 단위 변환
//! (int)t1은 시간을 초 단위로 변환.
// 시를 3600초, 분을 60초로 변환해 총 초를 계산.
    operator int() const {
        return hour * 3600 + min * 60 + sec;
    }


    // (8) double 형 변환: 시간 단위 변환
//! (double)t1은 시간을 시간 단위(소수 포함)로 변환.
// 분과 초를 시간 단위로 변환해 소수점 포함 값 반환.
    operator double() const {
        return hour + min / 60.0 + sec / 3600.0;
    }


    // (9) 곱셈 연산자: 시간 배수 계산
//! 정수와 TimeHMS 객체를 곱해 배수 시간 계산. 분과 초는 0~59 유지.
// 시간을 초로 변환 후 정수를 곱하고, 다시 시, 분, 초로 변환. 음수 방지.
    friend TimeHMS operator*(int n, const TimeHMS& t) {
        int totalSec = (t.hour * 3600 + t.min * 60 + t.sec) * n;
        if (totalSec < 0) totalSec = 0;
        int newHour = totalSec / 3600;
        totalSec %= 3600;
        int newMin = totalSec / 60;
        int newSec = totalSec % 60;
        return TimeHMS(newHour, newMin, newSec);
    }


    // (10) 입출력 연산자
//! cin >> t1로 시간 입력, cout << t1로 보기 좋게 출력.
// std::cin >> t1과 같은 형식으로 TimeHMS 객체에 데이터를 입력받을 수 있도록 입력 스트림 연산자(>>)를 오버로딩함.
    friend std::istream& operator>>(std::istream& is, TimeHMS& t) {  
        // std::istream& is: 입력 스트림 객체(예: std::cin)를 참조로 받음. 
        // TimeHMS& t: 입력 데이터를 저장할 TimeHMS 객체를 참조로 받음. 참조를 사용하므로 입력값으로 객체가 수정됨.
        is >> t.hour >> t.min >> t.sec;  // 입력 스트림에서 시, 분, 초를 순서대로 읽어 t의 멤버 변수에 저장. (예: 1 20 30 입력 시 t.hour = 1, t.min = 20, t.sec = 30).
        if (t.sec >= 60) { t.min += t.sec / 60; t.sec %= 60; }  // 61초 = 1분 1초
        if (t.min >= 60) { t.hour += t.min / 60; t.min %= 60; }  // 61분 = 1시간 1분
        return is;  // 입력 스트림을 반환해 연속 입력(cin >> t1 >> t2)이 가능하도록 함.
    }
    friend std::ostream& operator<<(std::ostream& os, const TimeHMS& t) {
        // std::ostream& os: 출력 스트림 객체(예: std::cout)를 참조로 받음.
        // const TimeHMS& t: 출력할 TimeHMS 객체를 상수 참조로 받음. 상수 참조를 사용하여 객체 수정 없이 읽기만 함.
        os << std::setfill('0') << std::setw(2) << t.hour << ":"   // (시 분 초 공통) 빈 자리 0으로 채움. 각 숫자를 2자리로 고정.
           << std::setfill('0') << std::setw(2) << t.min << ":"    // t.hour << ":" << t.min << ":" << t.sec: 시, 분, 초를 HH:MM:SS 형식으로 출력
           << std::setfill('0') << std::setw(2) << t.sec;
        return os;   // 출력 스트림을 반환해 연속 출력(cout << t1 << t2)이 가능하도록 함.
    }
};

// (9), (10)이 friend를 사용한 이유
// 이 연산자들이 클래스의 멤버 함수로 구현하기에 적합하지 않기 때문.
//! c++에서 연산자 오버로딩은 기본적으로 왼쪽 피연산자가 클래스 객체일 때 멤버 함수로 구현됨. (예: t1 * 2라면 TimeHMS::operator*(int)로 가능).
// (1)~(8)번 연산자(+, -, ==, !=, ++, --, [], 형 변환 연산자)는 모두 TimeHMS 객체가 왼쪽 피연산자이거나 단항 연산자이므로, 클래스 내부에서 멤버 함수로 구현 가능
// 멤버 함수는 this를 통해 객체의 private 멤버에 자연스럽게 접근하므로 friend가 필요 없음.
//   ex) 
//   t1 + t2 → TimeHMS::operator+(const TimeHMS& other): this가 t1이고, other가 t2이므로 멤버 함수로 충분.
//   ++t1 → TimeHMS::operator++(): 단항 연산자이므로 this만 사용.
//   (int)t1 → TimeHMS::operator int(): 역시 this만 필요.
// 반면, (9)와 (10)은 왼쪽 피연산자가 TimeHMS가 아니거나(2 * t1, std::cin >> t1) 외부 클래스(std::istream, std::ostream)와의 상호작용이 필요.
// => 전역 함수로 구현하고 friend로 private 멤버 접근 권한을 부여해야 함.
//? 근데 왜 전역함수임?
//? => 2 * t1에서 왼쪽 피연산자는 int이고, 오른쪽은 TimeHMS 객체임.
//?    멤버 함수는 첫 번째 피연산자가 클래스 객체(this)여야 하므로, t1 * 2는 구현 가능하지만 2 * t1은 불가능함.
//?    따라서 전역 함수로 정의해 int를 첫 번째 매개변수로 받음.

int main() {
    TimeHMS t1(1, 20, 30), t2(4, 35, 40), t3;

    // (1) + 연산자 테스트
    t3 = t1 + t2;
    std::cout << "t1 + t2 = " << t3 << " (5:56:10 expected)" << std::endl;

    // (2) - 연산자 테스트
    t3 = t2 - t1;
    std::cout << "t2 - t1 = " << t3 << " (3:15:10 expected)" << std::endl;

    // (3) ==, != 연산자 테스트
    std::cout << "t1 == t2: " << (t1 == t2 ? "true" : "false") << " (false expected)" << std::endl;
    std::cout << "t1 != t2: " << (t1 != t2 ? "true" : "false") << " (true expected)" << std::endl;

    // (4) 전위 증감 연산자 테스트
    ++t1;
    std::cout << "++t1 = " << t1 << " (2:20:30 expected)" << std::endl;
    --t1;
    std::cout << "--t1 = " << t1 << " (1:20:30 expected)" << std::endl;

    // (5) 후위 증감 연산자 테스트
    t3 = t1++;   // t3: 원래 시간(temp), t1: 후위 증감 연산자 적용 후 시간
    std::cout << "t1++ = " << t3 << ", t1 = " << t1 << " (1:20:30, 1:20:31 expected)" << std::endl;
    t3 = t1--;
    std::cout << "t1-- = " << t3 << ", t1 = " << t1 << " (1:20:31, 1:20:30 expected)" << std::endl;

    // (6) 인덱스 연산자 테스트
    std::cout << "t1[0] = " << t1[0] << ", t1[1] = " << t1[1] << ", t1[2] = " << t1[2]
              << " (1, 20, 30 expected)" << std::endl;

    // (7) int 형 변환 테스트
    std::cout << "(int)t1 = " << (int)t1 << " seconds (4830 expected)" << std::endl;

    // (8) double 형 변환 테스트
    std::cout << "(double)t1 = " << (double)t1 << " hours (1.34167 expected)" << std::endl;

    // (9) 곱셈 연산자 테스트
    t3 = 2 * t1;
    std::cout << "2 * t1 = " << t3 << " (2:41:00 expected)" << std::endl;

    // (10) 입출력 연산자 테스트
    std::cout << "Enter time (hour min sec): ";
    std::cin >> t3;
    std::cout << "You entered: " << t3 << std::endl;

    return 0;
}