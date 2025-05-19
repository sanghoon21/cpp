// 1. MonsterWorld 클래스 - 게임의 주 엔진
//    맵(world), 몬스터 배열(pMon), 캔버스(canvas)를 관리함.
//    아이템 수 계산(countItems), 게임 상태 체크(isDone), 화면 출력(print),
//     몬스터 추가(add), 게임 실행(play) 같은 기능도 포함.
//    play는 몬스터 이동과 화면 갱신을 반복하며 게임을 진행함.

#pragma once
#include "Canvas.h"
#include "Monster.h"
#include "Matrix.h"
#include "VariousMonsters.h"
#include <unistd.h>
#define DIM  40
#define MAXMONS 8  //! 변경 후: 5 -> 8로 늘려 더 많은 몬스터를 처리할 수 있게 함.

class MonsterWorld {

// MonsterWorld가 world 객체를 생성하며 맵의 아이템 상태를 초기화함.
    Matrix world;
    int xMax, yMax, nMon, nMove;
    Monster* pMon[MAXMONS];

// MonsterWorld가 생성될 때 Canvas 객체가 만들어져 맵을 초기화함.
//      이후 print와 draw를 통해 게임 화면이 지속적으로 갱신됨.
    Canvas canvas;

    int& Map(int x, int y) { return world.elem(y, x); } // x, y 순서 반대로
// 2-12. countItems() 호출해 남은 아이템 0이면 루프 종료.
    bool isDone() { return countItems() == 0; }

  // 2-9-4. (남은) 아이템 수를 계산해서 출력하는 함수.
    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }

// 2-9. 초기 화면 출력 print()
    void print() {
   // 2-9-1. Canvas.h의 clear 함수, 그리드를 "."으로 초기화함. 2-9-1
        canvas.clear();
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
   // 2-9-2. 외부 for 루프에서 Map(x, y)>0 조건으로 아이템 위치에 네모를 그림.
                if (Map(x, y) > 0) canvas.draw(x, y, "■");
        for (int i = 0; i < nMon; i++)
            pMon[i]->draw(canvas);
   // 2-9-3. 화면에 아래 문구 출력.  2-9-3
        canvas.print("[ Monster World (Inheritance) ]");
        cout << " 전체 이동 횟수 = " << nMove << endl;
   // 2-9-4. countItems() - 아이템 수를 계산해서 출력 2-9-4
        cout << " 남은 아이템 수 = " << countItems() << endl;
        for (int i = 0; i < nMon; i++)
   // 2-9-5. 각 몬스터의 상태를 출력함. print()는 Monster.h에 정의됨. 2-9-5
            pMon[i]->print();
    }


public:

// 2-4. MonsterWorld 생성자가 호출되며 world와 canvas 객체를 생성함.
//  world(h, w) - Matrix.h에 정의된 Matrix 클래스의 객체. 8*16 크기의 2차원 배열을 생성함.
//  canvas(w, h) - Camvas.h에 정의된 Canvas 클래스의 객체. 16*8 크기의 문자열 그리드를 "."으로 초기화함.
//  for 루프에서 Map(x, y) = 1을 호출해 맵의 모든 위치에 아이템(값1)을 배치함. 2-5 main.cpp
    MonsterWorld(int w, int h) : world(h, w), canvas(w, h), xMax(w), yMax(h), nMon(0), nMove(0) {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                Map(x, y) = 1;
    }


// 2-14. 게임 루프 종료 후 MonsterWorld 객체가 소멸되며 ~MonsterWorld()가 호출됨.
// for 루프에서 pMon[i]의 동적 객체를 delete로 해제함.
// 각 몬스터의 소멸자가 호출됨.
//   Monster의 ~Monster()가 이름과 아이콘을 출력하고, 자식 클래스의 소멸자(예: ~Zombie())가 추가 메시지를 출력함. -> main 2-15
    ~MonsterWorld() {
        for (int i = 0; i < nMon; i++)
            delete pMon[i];
    }


// 2-6. pMon 배열에 몬스터 포인터 저장 후, nMon을 증가시킴. main 2-7
    void add(Monster* m) {
        if (nMon < MAXMONS) pMon[nMon++] = m;
    }


// 2-8.
    void play(int maxwalk, int wait) 
    {

// 2-9. print()가 호출되며 초기 화면 출력됨. 2-9
        print();

        cout << " 엔터를 누르세요...";
        getchar();

// 2-10. for 루프가 500번 반복하며 게임을 진행. 각 반복마다 8개 몬스터의 move를 강제 형 변환으로 호출함.
// ex) ((Zombie*)pMon[0])->move(...)는 VariousMonsters.h의 Zombie 클래스 move를 실행함. 기본 8방향 이동 후 clip과 eat 호출.
// 각자의 move는 VariousMonsters.h에 정의됨. 2-10
        for (int i = 0; i < maxwalk; i++) {
            // 각 몬스터의 move()를 강제 형 변환으로 호출
        //! 5. 변경 후: play()에서 새로운 몬스터의 move를 호출하도록 확장되어 모든 몬스터가 게임에 참여 가능하게 됨
        //! 새로운 3가지 몬스터를 여기에 추가하지 않으면, 실행 시 새로운 3개의 몬스터가 존재는 하지만, 동작을 안 함.
            ((Zombie*)pMon[0])->move(world.Data(), xMax, yMax);
            ((Vampire*)pMon[1])->move(world.Data(), xMax, yMax);
            ((KGhost*)pMon[2])->move(world.Data(), xMax, yMax);
            ((Jiangshi*)pMon[3])->move(world.Data(), xMax, yMax);
            ((Jiangshi*)pMon[4])->move(world.Data(), xMax, yMax);
            ((Smombi*)pMon[5])->move(world.Data(), xMax, yMax);
            ((Siangshi*)pMon[6])->move(world.Data(), xMax, yMax);
            ((KGhostold*)pMon[7])->move(world.Data(), xMax, yMax);

// 2-11. 이동 횟수 증가시킴, print()로 화면 갱신
            nMove++;
            print();

// 2-12. 아이템이 모두 먹혔는지 확인. 남은 아이템 0이면 종료. isDone() 2-12
            if (isDone()) break;
// 2-13. 400ms 대기. -> 2-14
            usleep(wait * 1000);
        }
    }
};