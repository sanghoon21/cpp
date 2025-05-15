#include <iostream>
using namespace std;

int main() {
    int number;  //사용자에게 숫자를 입력받음
    cout << "정수를 입력하세요 (100000 미만): ";
    cin >> number;

    if (number < 0 || number >= 100000) {
        cout << "입력값이 범위를 벗어났습니다." << endl;
        return 1;
    }

    // 입력값을 각 자리별로 분해
    int 만 = number / 10000; //number를 10000으로 나눠서 만자리 구함
    int 천 = (number % 10000) / 1000; // 1천 단위
    int 백 = (number % 1000) / 100; // 1백 단위
    int 십 = (number % 100) / 10; // 1십 단위
    int 일 = number % 10; // 1일 단위

    // 만 단위 (1일 경우 '1만'이 아니라 '만'만 출력)
    if (만 > 0) cout << (만 == 1 ? "만 " : to_string(만) + "만 ");

    // 천 단위
    if (천 > 0) cout << (천 == 1 ? "천 " : to_string(천) + "천 ");

    // 백 단위
    if (백 > 0) cout << (백 == 1 ? "백 " : to_string(백) + "백 ");

    // 십 단위
    if (십 > 0) cout << (십 == 1 ? "십 " : to_string(십) + "십 ");

    // 일 단위 (0이면 출력하지 않음)
    if (일 > 0) cout << 일;

    cout << endl;
    
    return 0;
}