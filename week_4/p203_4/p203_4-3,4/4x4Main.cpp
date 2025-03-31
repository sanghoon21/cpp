#include "Ranking.h"
#include <iostream>

extern int playFifteenPuzzle(int size);

int main() {
    loadRanking("ranking.txt");
    int size;
    std::cout << "퍼즐 크기를 선택하세요 (3, 4, 5): ";
    std::cin >> size;
    if (size < 3 || size > 5) {
        std::cout << "잘못된 입력입니다. 4x4로 기본 설정됩니다.\n";
        size = 4;
    }
    int rank = playFifteenPuzzle(size);
    printRanking();
    storeRanking("ranking.txt");
    return 0;
}