#include <stdio.h>
#include "p147_2_5way.h"  // 헤더 파일 포함

// reverse 함수 정의: 정수를 입력받아 각 자리 숫자를 역순으로 변환
int reverse(int num) {
    int reversed = 0;
    while (num > 0) {
        int digit = num % 10;         // 마지막 자리 숫자 추출
        reversed = reversed * 10 + digit; // 역순으로 숫자 추가
        num = num / 10;               // 마지막 자리 제거
    }
    return reversed;
}

// 메인 함수 정의
int main() {
    int number;
    
    // 사용자로부터 정수 입력받기
    printf("Enter a positive integer: ");
    scanf("%d", &number);
    
    // reverse 함수 호출 및 결과 출력
    int result = reverse(number);
    printf("Reversed number: %d\n", result);
    
    return 0;  // 프로그램 종료 상태 반환
}