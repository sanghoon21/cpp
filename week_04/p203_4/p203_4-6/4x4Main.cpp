#include "Ranking.h"
#include <iostream>

extern int playFifteenPuzzle(int size, bool isHeartPuzzle);

int main() {
    loadRanking("ranking.bin"); // 이진 파일로 변경
    char choice;
    std::cout << "옵션을 선택하세요:\n";
    std::cout << "1. 퍼즐 크기 선택 (3, 4, 5)\n";
    std::cout << "2. 하트 그림 퍼즐 (4x4)\n";
    std::cout << "선택 (1/2): ";
    std::cin >> choice;
    while (getchar() != '\n'); // 입력 버퍼 비우기

    int size;
    bool isHeartPuzzle = false;
    if (choice == '2') {
        size = 4; // 하트 그림은 4x4 고정
        isHeartPuzzle = true;
    } else {
        std::cout << "퍼즐 크기를 선택하세요 (3, 4, 5): ";
        std::cin >> size;
        if (size < 3 || size > 5) {
            std::cout << "잘못된 입력입니다. 4x4로 기본 설정됩니다.\n";
            size = 4;
        }
    }

    int rank = playFifteenPuzzle(size, isHeartPuzzle);
    printRanking();
    storeRanking("ranking.bin"); // 이진 파일로 변경
    return 0;
}