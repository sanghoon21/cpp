#include <iostream>
#include <iomanip> // setprecision 사용을 위한 라이브러리
using namespace std;

int main() {
    int n;
    cout << "정수 n을 입력하세요: ";
    cin >> n;

    if (n <= 0) {
        cout << "n은 양의 정수여야 합니다." << endl;
        return 1;
    }

    double pi = 0.0; // π의 근사값 저장
    for (int i = 0; i < n; i++) {
        double term = 1.0 / (2 * i + 1); // 1/1, 1/3, 1/5, ...
        if (i % 2 == 0) 
            pi += term; // 짝수 번째 항은 더하기
        else 
            pi -= term; // 홀수 번째 항은 빼기
    }

    pi *= 4; // 최종적으로 4를 곱하여 π 근사값 계산

    cout << "근사값으로 계산된 π: " << fixed << setprecision(10) << pi << endl;
    
    return 0;
}