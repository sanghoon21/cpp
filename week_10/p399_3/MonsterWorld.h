// 게임의 핵심 로직과 상태 관리.

#pragma once
#include "Canvas.h"
#include "Monster.h"
#include "Matrix.h"
//! 1. Matrix.h를 포함해서 동적 할당된 2차원 맵을 사용
#include <unistd.h>
#define DIM  40
#define MAXMONS 5

class MonsterWorld {
    Matrix world;
    int xMax, yMax, nMon, nMove;
    Monster* pMon[MAXMONS];
    //! 3. 포인터 배열 사용.
    Canvas canvas;
    

    int& Map(int x, int y) { return world.elem(y, x); }
    //! 4. 맵이 Matrix 기반, world.elem(y, x)로 Matrix에서 요소 접근.
    bool isDone() { return countItems() == 0; }
    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }

    //! 5. 아사 처리 기능 추가
    //! 에너지가 0인 몬스터를 동적 해제하고 배열 조정, 메시지 출력 후 0.5초 대기
    void checkStarvation() {
        for (int k = 0; k < nMon; k++) {
            if (pMon[k]->getEnergy() == 0) {
                cout << "Monster 하나가 굶어죽습니다" << endl;
                cout.flush(); // 출력 버퍼 강제 플러시
                delete pMon[k]; // 동적 해제 (소멸자 호출)
                cout.flush(); // 소멸자 출력 후 플러시
                pMon[k] = pMon[nMon - 1]; // 마지막 몬스터를 k 위치로 이동
                nMon--; // 몬스터 수 감소
                k--; // k번째 다시 검사
                usleep(500000); // 0.5초 대기 (메시지 확인 용이)
            }
        }
    }

    void print() {
        canvas.clear();
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "■");
        for (int i = 0; i < nMon; i++)
            pMon[i]->draw(canvas);
        canvas.print("[ Monster World (Dynamic) ]");

        cout << " 전체 이동 횟수 = " << nMove << endl;
        cout << " 남은 아이템 수 = " << countItems() << endl;
        for (int i = 0; i < nMon; i++)
            pMon[i]->print();
        Monster::printCount(); // 몬스터 수 출력
        //! 6. 몬스터 수 출력 기능 있고 없고의 차이
    }

public:
    MonsterWorld(int w, int h) : world(h, w), canvas(w, h), xMax(w), yMax(h), nMon(0), nMove(0) {
        //! 7. 생성자: 동적 배열 초기화 - Matrix world(h, w) 초기화.
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                Map(x, y) = 1;
    }
    ~MonsterWorld() {
        for (int i = 0; i < nMon; i++)
            delete pMon[i];
            //! 8. 소멸자: 동적 해제. - 동적 할당된 pMon 해제
    }
    void add(Monster* m) {
        if (nMon < MAXMONS) pMon[nMon++] = m;
        //! 9. add(): 포인터로 몬스터 추가
    }
    void play(int maxwalk, int wait) {
        print();
        cout << " 엔터를 누르세요...";
        getchar();
        for (int i = 0; i < maxwalk; i++) {
            for (int k = 0; k < nMon; k++)
                pMon[k]->move(world.Data(), xMax, yMax);
            nMove++;
            checkStarvation(); // 에너지 확인 및 몬스터 제거
            print();
            if (isDone() || nMon == 0) break; // 아이템 0개 또는 몬스터 0개면 종료
            usleep(wait * 1000);
        }
    }
    //! 10. play(): 아사 체크와 몬스터 수 0일 때 종료 조건 추가
};