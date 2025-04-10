#include <iostream>
#include "MyTime.h"

int main() {
    MyTime t1, t2, result;

    std::cout << "[첫 번째 시간 입력]\n";
    t1.read();

    std::cout << "[두 번째 시간 입력]\n";
    t2.read();

    std::cout << "\n[입력된 시간]\n";
    std::cout << "t1: ";
    t1.print();

    std::cout << "t2: ";
    t2.print();

    result = t1.add(t2);

    std::cout << "\n[합산 결과]\n";
    result.print();

    return 0;
}
