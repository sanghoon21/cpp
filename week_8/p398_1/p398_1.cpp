#include <iostream>
#include <cstring>
using namespace std;

class Sample {
    char *name;
    static int count; // (1) 정적 변수 선언

public:

    //! 원래 코드: Sample 객체가 몇 개 생성되었는지 알 수 없음
    //* 바꾼 코드: (1) Sample 객체의 개수를 관리하는 정적 변수 count + printCount()
    //* 1. static int count -> 정적 멤버 변수 추가, 객체 수를 클래스 단위로 공유
    //* 2. count++ 및 count-- 로 생성과 소멸을 추적 가능
    //* 3. printCount()로 현재 객체 수 출력 가능

    // (1) 정적 함수로 객체 수 출력
    static void printCount() {
        cout << "Sample 객체 수: " << count << endl;
    }
    
    // (2) 기본 생성자
    Sample() {
        name = nullptr;
        count++;
    }

    //! 원래 코드:
    //! 생성자는 const char* name을 받아도 멤버 변수 name에 저장하지 않음
    //! this->name = name; 같은 얕은 복사조차 없음
    //! 결국 객체 내부 name은 쓰레기 값
    //* 바꾼 코드: (2) Sample(const char*) 생성자에서 this와 new로 name 초기화
    //* this를 명시적으로 사용하여 객체 자신의 멤버에 접근
    //* new로 메모리 할당 -> name이 가리킬 메모리 확보
    //* 각 객체가 고유한 name을 갖게 됨 (독립적 메모리)
    //* strcpy로 문자열 내용을 복사 -> 문자열 안정적으로 저장됨

    // (2) 매개변수가 있는 생성자
    Sample(const char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        count++;
    }


    //! 원래 코드:
    //! Sample b(a); 와 같이 객체 복사 시, 컴파일러가 제공하는 "얕은 복사"만 수행
    //! 얕은 복사는 name 포인터만 복사함 -> 둘이 같은 메모리를 가리킴
    //! 소멸자에서 delete[] name 두 번 호출됨 -> 이중 해제 오류 발생
    //* 바꾼 코드: (4) 복사 생성자 Sample(const Sample&)
    //* 깊은 복사로 개선 - 문자열 데이터를 새 메모리에 깊은 복사
    //* 각 객체가 고유한 name 메모리 소유 -> 충돌 없음
    //* 소멸 시에도 안전하게 메모리 해제 가능!!!!

    // (4) 복사 생성자
    Sample(const Sample& other) {
        if (other.name != nullptr) {
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        } else {
            name = nullptr;
        }
        count++;
    }


    //! 원래 코드:
    //! name이 동적 메모리를 사용하게 될 경우, 해제 안하면 메모리 누수 발생
    //! 여러 개의 Sample 객체가 생성되면 누수량 누적
    //!     누수: new로 메모리를 빌려놓고 delete로 돌려주지 않으면?
    //!          그 메모리는 계속 빌려진 상태로 남아 있게 됨.
    //!          동적으로 할당된 메모리를 해제하지 않으면
    //!          프로그램은 그 메모리를 더 이상 사용하지 않지만,
    //!          운영체제는 그 메모리를 아직 "사용 중"이라고 섕각하게 됨
    //* 바꾼 코드: (3) 소멸자 ~Sample() 에서 동적 메모리 해제
    //* 객체가 소멸될 때 동적으로 할당된 name 메모리를 해제
    //* count-- 도 함께 수행 (객체 수)
    //* 메모리 누수 방지, 프로그램 종료 시 안정적으로 정리 가능

    // (3) 소멸자
    ~Sample() {
        delete[] name;
        count--;
    }


    // // (번외) 문자열 내용과 주소를 출력해주는 멤버함수 printName() 추가
    // void printName() const {  //함수 정의, 반환값 X, 출력만.
    //     // name이 nullptr이 아니라면, 즉 유효한 문자열 메모리를 가리킨다면 실행
    //     if (name != nullptr)
    //         // cout이 문자열 포인터인 name을 만나 해당 포인터가 가리키는 문자열 출력
    //         // void 포인터로 변환하여 포인터 주소 자체를 출력?
    //         cout << "name: " << name << " (주소: " << static_cast<void*>(name) << ")\n" << endl;
    //     else                                    // name 포인터의 주소를 숫자 형태로 출력?
    //         cout << "name: (null)" << endl;
    // }


};

// (1) 정적 변수 정의
int Sample::count = 0;

int main() {
    Sample a("shshsh");
    Sample::printCount();  // 객체 수 출력
    // a.printName();         // a의 name, 주소 출력

    Sample b(a);
    Sample::printCount();  // 객체 수 출력
    // b.printName();         // b의 name, 주소 출력

    return 0;
}