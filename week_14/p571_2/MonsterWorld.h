// 1. 게임 세계를 관리하며, 몬스터와 맵의 상호작용, 게임 상태 출력, 아사 체크 등을 처리.

#pragma once
#include "Canvas.h"
#include "Monster.h"
#include "Matrix.h"
#include "VariousMonsters.h"
#include "Human.h"
#include <unistd.h>
#define DIM  40
#define MAXMONS 10 // 8개 일반 몬스터 + 2개 Tuman

//* 3-10. MonsterWorld: 게임 세계를 관리.
//*        몬스터와 맵의 상호작용, 출력, 아사 체크, 휴식 상태 관리를 포함.
class MonsterWorld 
{
    Matrix world;  // world 객체를 생성하며 맵의 아이템 상태를 초기화함.
    int xMax, yMax, nMon, nMove;
    Monster* pMon[MAXMONS];  // 몬스터 배열.
    Canvas canvas; // MonsterWorld가 생성될 때 Canvas 객체가 만들어져 맵을 초기화함.
                   //      이후 print와 draw를 통해 게임 화면이 지속적으로 갱신됨.

// 4-28. Map() - world.elem(y, x) 반환.
    int& Map(int x, int y) { return world.elem(y, x); } // x, y 순서 반대로

// 4-29. isDone() - 남은 아이템이 0이면 true 반환.
    bool isDone() { return countItems() == 0; }

// 4-30. countItems() - 맵에서 아이템 개수(Map(x, y) > 0) 계산.
    int countItems() 
    {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }

// 4-31. checkStarvation() - 에너지가 0인 일반 몬스터 제거, 배열 재정렬.
    void checkStarvation() 
    {
        for (int k = 0; k < nMon - 2; k++) 
        { // 플레이어 제외
            if (pMon[k]->getEnergy() == 0) 
            {
                cout << "Monster 하나가 굶어죽습니다" << endl;
                cout.flush(); // 출력 버퍼 강제 플러시
                delete pMon[k]; // 동적 해제 (소멸자 호출)
                cout.flush(); // 소멸자 출력 후 플러시
                pMon[k] = pMon[nMon - 3]; // 마지막 일반 몬스터를 k 위치로 이동
                pMon[nMon - 3] = pMon[nMon - 2]; // 일반 몬스터와 플레이어 재배열
                pMon[nMon - 2] = pMon[nMon - 1]; // 플레이어 순서 유지
                nMon--; // 몬스터 수 감소
                k--; // k번째 다시 검사
                usleep(500000); // 0.5초 대기
            }
        }
    }

// 4-32. print() - Canvas로 맵과 몬스터 그리기, 이동 횟수, 아이템 수, 몬스터 수, 휴식 시간 출력.
    void print() 
    {
        canvas.clear();
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "■");
        for (int i = 0; i < nMon; i++)
            pMon[i]->draw(canvas);
        canvas.print("[ Monster World (여유있는 삶) ]");
        cout << " 전체 이동 횟수 = " << nMove << endl;
        cout << " 남은 아이템 수 = " << countItems() << endl;
        for (int i = 0; i < nMon; i++)
            pMon[i]->print();
        Monster::printCount(); // 몬스터 수 출력
    }

public:
// 4-33. 생성자 - Matrix, Canvas 초기화, 맵을 아이템으로 채움.
    MonsterWorld(int w, int h) : world(h, w), canvas(w, h), xMax(w), yMax(h), nMon(0), nMove(0) 
    {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                Map(x, y) = 1;
    }

// 4-34. 소멸자 - 모든 몬스터 메모리 해제.
    ~MonsterWorld() 
    {
        for (int i = 0; i < nMon; i++)
            delete pMon[i];
    }

// 4-35. add() - 몬스터를 pMon 배열에 추가.
    void add(Monster* m) 
    {
        if (nMon < MAXMONS) pMon[nMon++] = m;
    }

// 4-36. play() - 게임 루프: 몬스터 이동, 플레이어 입력 처리, 아사 체크, 상태 출력, 종료 조건 체크.
    void play(int maxwalk, int wait) 
    {
        print();
        cout << " 엔터를 누르세요...";
        getchar();
        for (int i = 0; i < maxwalk; i++) 
        {
            if (nMon >= 2) 
            { 
                for (int k = 0; k < nMon - 2; k++) // 일반 몬스터 이동
                    pMon[k]->move(world.Data(), xMax, yMax);

                if (kbhit()) 
                {
                    struct termios oldt, newt;
                    tcgetattr(STDIN_FILENO, &oldt);
                    newt = oldt;
                    newt.c_lflag &= ~(ICANON | ECHO);
                    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

                    unsigned char ch = getchar();
                    if (ch == 27 && nMon > 1) { // 오른쪽 플레이어 (화살표 키)
                        getchar(); // '[' 건너뛰기
                        ch = getchar();
                        ((Tuman*)(pMon[nMon - 1]))->moveHuman(world.Data(), xMax, yMax, ch);
                    } else if (nMon > 0) { // 왼쪽 플레이어 ('w', 's', 'a', 'd')
                        ((Tuman*)(pMon[nMon - 2]))->moveHuman(world.Data(), xMax, yMax, ch);
                    }

                    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                }
            }

            nMove++;
            checkStarvation(); // 아사 체크
            print();
            if (isDone() || nMon < 2) break; // 아이템 0개 또는 플레이어 1명 이하로 종료
            usleep(wait * 1000);
        }
    }

// 4-63. getMonster() - 지정된 인덱스의 몬스터 포인터 반환.
    Monster* getMonster(int index) const { return pMon[index]; }

// 4-64. getNMon() - 현재 몬스터 수 반환.
    int getNMon() const { return nMon; }
};