#include "p147_6.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// 구구단 게임 (함수 정의)
void playGuguOnce() {
    int a = rand() % 9 + 1;
    int b = rand() % 9 + 1;
    int answer;
    
    while (true) {
        cout << a << " x " << b << " = ? ";
        cin >> answer;

        if (answer == a * b) {
            cout << "정답!\n";
            break;
        } else {
            cout << "틀렸습니다. 다시 시도하세요.\n";
        }
    }
}

// 두 자리 수 곱셈 게임 (함수 정의)
void playMultiplication() {
    int a = rand() % 90 + 10;
    int b = rand() % 90 + 10;
    int answer;
    
    while (true) {
        cout << a << " x " << b << " = ? ";
        cin >> answer;

        if (answer == a * b) {
            cout << "정답!\n";
            break;
        } else {
            cout << "틀렸습니다. 다시 시도하세요.\n";
        }
    }
}

// 여러 자리 수 덧셈 게임 (함수 정의)
void playAddition(int digits) {
    int num1 = rand() % (int)pow(10, digits);
    int num2 = rand() % (int)pow(10, digits);
    int answer;
    
    while (true) {
        cout << num1 << " + " << num2 << " = ? ";
        cin >> answer;

        if (answer == num1 + num2) {
            cout << "정답!\n";
            break;
        } else {
            cout << "틀렸습니다. 다시 시도하세요.\n";
        }
    }
}

// 게임 시작 (함수 정의)
void startGame() {
    srand(time(0));
    int choice;

    cout << "게임을 선택하세요: \n";
    cout << "1: 구구단 게임\n";
    cout << "2: 두 자리 수 곱셈\n";
    cout << "3~9: 해당 자리 수 덧셈\n";
    cin >> choice;

    if (choice == 1) {
        playGuguOnce();
    } else if (choice == 2) {
        playMultiplication();
    } else if (choice >= 3 && choice <= 9) {
        playAddition(choice);
    } else {
        cout << "잘못된 선택입니다.\n";
    }
}

//메인 함수
int main() {
    startGame();  //함수 호출
    return 0;
}