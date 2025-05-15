//Main.cpp : 사용자로부터 시간을 입력받고, 입력된 두 시간의 합산 결과 출력


#include <iostream>
#include "MyTime.h"

// 0. 프로그램 시작되면 메인함수 실행됨 


int main() {

    //1. MyTime 클래스 객체 t1, t2, result를 선언.
        //생성자 MyTime()이 자동호출되어 세 객체의 시간값이 모두 0으로 초기화됨
        //생성자: 클래스가 객체를 "생성"할 때 실행되는 함수. 처음 쓸 때 깨끗한 상태에서 사용할 수 있도록 해주는 함수
    MyTime t1, t2, result;


    //2. 사용자의 입력을 받기 위한 read() 멤버함수 호출
    std::cout << "[첫 번째 시간 입력]\n";
    t1.read();   //. => 객체의 요소에 접근하는 것

    std::cout << "[두 번째 시간 입력]\n";
    t2.read();


    //3. 시간 정보를 출력하기 위한 print() 멤버함수 호출
    std::cout << "\n[입력된 시간]\n";
    std::cout << "t1: ";
    t1.print();

    std::cout << "t2: ";
    t2.print();


    //4. 두 가지의 시간을 합산하기 위해 add() 멤버함수 호출
    result = t1.add(t2);


    //5. 결과를 다시 print()함수로 출력
    std::cout << "\n[합산 결과]\n";  //01:02:05:789
    result.print();

    return 0;
}
