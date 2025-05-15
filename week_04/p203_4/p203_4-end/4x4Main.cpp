// 이 프로그램은 사용자가 선택한 퍼즐 크기(3x3, 4x4, 5x5) 또는 하트 퍼즐(4x4)을 실행하고, 
// 게임 결과를 랭킹 시스템에 반영하여 저장 및 출력하는 기능을 수행한다.


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
    while (getchar() != '\n'); // 입력 버퍼 비우기 (잘못된 입력 방지)

    int size;
    bool isHeartPuzzle = false;
    const char* rankingFile;

    // 사용자가 하트 퍼즐을 선택한 경우
    if (choice == '2') {
        size = 4; // 하트 퍼즐은 4x4 고정
        isHeartPuzzle = true;
        rankingFile = "ranking_heart.bin"; // 하트 퍼즐 전용 랭킹 파일 사용
    } else {
        // 일반 퍼즐 선택 시 퍼즐 크기 입력 받기
        std::cout << "퍼즐 크기를 선택하세요 (3, 4, 5): ";
        std::cin >> size;

        // 입력값이 3~5 범위를 벗어나면 기본 4x4로 설정
        if (size < 3 || size > 5) {
            std::cout << "잘못된 입력입니다. 4x4로 기본 설정됩니다.\n";
            size = 4;
        }

        // 선택한 크기에 따라 랭킹 파일을 설정
        switch (size) {
            case 3: rankingFile = "ranking_3x3.bin"; break;
            case 4: rankingFile = "ranking_4x4.bin"; break;
            case 5: rankingFile = "ranking_5x5.bin"; break;
            default: rankingFile = "ranking_4x4.bin"; break; // 안전장치 (실제로 실행될 일 없음)
        }
    }

    // 해당 퍼즐에 맞는 랭킹 데이터 불러오기
    loadRanking(rankingFile);

    // 퍼즐 게임 실행 및 랭킹 점수 반환
    int rank = playFifteenPuzzle(size, isHeartPuzzle);

    // 랭킹 출력
    printRanking();

    // 랭킹 데이터 저장
    storeRanking(rankingFile);

    return 0;
}
