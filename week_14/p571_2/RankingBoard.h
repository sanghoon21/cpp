// 1. 게임의 랭킹 시스템 구현, 플레이어의 성과?를 파일에 저장하고 로드.
//    게임시작/종료 시 랭킹 표시하고 갱신하는 기능 제공.

#pragma once
#include <iostream>
#include <fstream>
#include "FileException.h"
using namespace std;
#define NUM_MVP 5 // 최대 랭킹 수

// 게임 플레이어 정보를 저장하는 구조체
struct PlayInfo {
    string name;        // 플레이어 이름
    int nItem;          // 먹은 아이템 수
    double itemPerMove; // 이동 거리당 아이템 수 (효율성)
    PlayInfo(string na = "신인류", int ni = 0, double ipm = 0.0)
        : name(na), nItem(ni), itemPerMove(ipm) {}
};

//* 3-15. RankingBoard: 게임 플레이어의 랭킹 정보를 관리하고, 파일 입출력 및 랭킹 갱신 기능을 제공.
class RankingBoard {
    PlayInfo MVP[NUM_MVP]; // 상위 5명의 랭킹 정보
    int nMVP = NUM_MVP;    // 랭킹 수 (고정: 5)

public:

//TODO^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// 4-59. load() - 지정된 파일에서 랭킹 정보를 읽어옴, 실패 시 FileException 발생.
    void load(string filename) {
        ifstream is;
        is.open(filename);
        if (!is)
        //! 예외 처리: 파일 읽기 위해 열지 못했음(파일 없음), 예외 -> FileExceptipn (filename, true)을 throw하여 읽기 실패라는 예외 던짐
            throw FileException(filename, true); // 읽기 실패 예외
        for (int i = 0; i < nMVP; i++)  // 파일에 저장된 정보들을 읽음. (1등~5등)
            is >> MVP[i].nItem >> MVP[i].name >> MVP[i].itemPerMove;
        is.close();
    }

// 4-60. store() - 랭킹 정보를 지정된 파일에 저장, 실패 시(예외 발생시) FileException (예외) 던짐.
    void store(string filename) {
        ofstream os;
        os.open(filename);
        if (!os)
        //! 예외 처리: 파일 열지 못함(읽기 전용 파일) -> FileException (")을 throw하여 쓰기 실패라는 예외 던짐
            throw FileException(filename, false); // 쓰기 실패 예외
        for (int i = 0; i < nMVP; i++)
            os << MVP[i].nItem << " " << MVP[i].name << " "
               << MVP[i].itemPerMove << "\n";
        os.close();
    }
//Todo+++++++++++++++++++++++++++++++++++++++++

// 4-61. print() - 랭킹 정보를 출력하고 사용자 입력 대기.
    void print(string title = "게임 랭킹") {
        cout << endl << title << endl;
        for (int i = 0; i < nMVP; i++)
            cout << "[" << i + 1 << "위] " << MVP[i].name << "\t"
                 << MVP[i].nItem << " " << MVP[i].itemPerMove << "\n";
        cout << "엔터를 입력하세요.";
        getchar();
        cout << endl;
    }

// 4-62. add() - 새로운 플레이어 점수를 추가하고 랭킹 갱신, 추가된 위치 반환.
    int add(int nItem, double ipm, bool isRightPlayer) {
        if (nItem <= MVP[nMVP - 1].nItem) return 0; // 최하위보다 낮으면 추가 안 함

        int pos = nMVP - 1;
        for (; pos > 0; pos--) {
            if (nItem <= MVP[pos - 1].nItem) break;
            MVP[pos] = MVP[pos - 1]; // 한 칸씩 밀기
        }
        MVP[pos].nItem = nItem;
        MVP[pos].itemPerMove = ipm;
        cout << "\n[" << pos + 1 << "위] " << (isRightPlayer ? "☞" : "☜") << " 이름을 입력하세요: ";
        getline(cin, MVP[pos].name); // 공백 포함 이름 입력
        return pos + 1;
    }
};