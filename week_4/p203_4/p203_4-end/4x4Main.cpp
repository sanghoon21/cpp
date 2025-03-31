#include "Ranking.h"
#include <iostream>

extern int playFifteenPuzzle(int size, bool isHeartPuzzle);

int main() {
    char choice;
    std::cout << "옵션을 선택하세요:\n";
    std::cout << "1. 퍼즐 크기 선택 (3, 4, 5)\n";
    std::cout << "2. 하트 그림 퍼즐 (4x4)\n";
    std::cout << "선택 (1/2): ";
    std::cin >> choice;
    while (getchar() != '\n'); // 입력 버퍼 비우기

    int size;
    bool isHeartPuzzle = false;
    const char* rankingFile;

    if (choice == '2') {
        size = 4; // 하트 그림은 4x4 고정
        isHeartPuzzle = true;
        rankingFile = "ranking_heart.bin"; // 하트 퍼즐 전용 랭킹 파일
    } else {
        std::cout << "퍼즐 크기를 선택하세요 (3, 4, 5): ";
        std::cin >> size;
        if (size < 3 || size > 5) {
            std::cout << "잘못된 입력입니다. 4x4로 기본 설정됩니다.\n";
            size = 4;
        }
        // 크기에 따라 랭킹 파일 선택
        switch (size) {
            case 3: rankingFile = "ranking_3x3.bin"; break;
            case 4: rankingFile = "ranking_4x4.bin"; break;
            case 5: rankingFile = "ranking_5x5.bin"; break;
            default: rankingFile = "ranking_4x4.bin"; break; // 안전장치
        }
    }

    loadRanking(rankingFile); // 선택된 게임에 맞는 랭킹 파일 로드
    int rank = playFifteenPuzzle(size, isHeartPuzzle);
    printRanking();
    storeRanking(rankingFile); // 선택된 게임에 맞는 랭킹 파일 저장

    return 0;
}