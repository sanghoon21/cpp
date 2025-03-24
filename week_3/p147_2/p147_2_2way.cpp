#include <stdio.h>

// reverse 함수 선언
int reverse(int num);

// 메인 함수 정의
int main() {
    int number;   //사용자로부터 입력받을 정수를 저장할 변수 number를 선언
    
    // 사용자로부터 정수 입력받기
    printf("Enter a positive integer: ");  //화면에 출력된 메시지
    scanf("%d", &number);  //사용자로부터 입력을 받는 함수. %d는 정수형으로 입력받는다는 것
                            //입력받은 정수는 number 변수에 저장됨
    
    // reverse 함수 호출 및 결과 출력
    int result = reverse(number);  //입력받은 숫자를 reverse함수에 넣고 돌림
                                   //result 변수에 reverse함수의 출력인 reversed를 저장
    printf("Reversed number: %d\n", result);  //정수형 변수 result 출력
    
    return 0;  // 프로그램 종료 상태 반환
}

// reverse 함수 정의: 정수를 입력받아 각 자리 숫자를 역순으로 변환
int reverse(int num) {  //num: 입력된 정수
    int reversed = 0;   //reversed: 역순으로 만들어갈 숫자를 저장하는 변수
    while (num > 0) {   //num이 0보다 큰 동안 반복
            //digit: num의 마지막 자리 숫자
        int digit = num % 10;         //num을 10으로 나눈 나머지 값을 digit에 저장
                                      // = (num의 마지막 자리 숫자)
                                      // ex. 12345 % 10 = 5(나머지)

        reversed = reversed * 10 + digit; // 역순으로 숫자 추가 (5->54->543 ... ->54321)
        num = num / 10;               // 마지막 자리 제거 (12345 / 10 = 1234)
    }                                   //num = 12345->1234->123 ... ->1->0
    return reversed;   //최종적으로 54321 반환
}