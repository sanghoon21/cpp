#include <iostream>
#include <cstring>
using namespace std;

class Sample {
    char *name;
    static int count; // (1) 정적 변수 선언

public:
    // (1) 정적 함수로 객체 수 출력
    static void printCount() {
        cout << "Sample 객체 수: " << count << endl;
    }

    // (2) 기본 생성자
    Sample() {
        name = nullptr;
        count++;
    }

    // (2) 매개변수가 있는 생성자
    Sample(const char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        count++;
    }

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

    // (3) 소멸자
    ~Sample() {
        delete[] name;
        count--;
    }
};

// (1) 정적 변수 정의
int Sample::count = 0;

int main() {
    Sample a("sample");
    Sample::printCount();  // 객체 수 출력
    Sample b(a);
    Sample::printCount();  // 객체 수 출력

    return 0;
}
