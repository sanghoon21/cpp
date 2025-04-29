// 여러 몬스터와 아이템을 가진 게임 월드를 구성.
// 아이템 맵을 만들고, 몬스터를 등록하고, 몬스터를 움직이며 게임을 진행함.

#pragma once
#include "Canvas.h"
#include "Monster.h"
#include <unistd.h>
#define DIM  40
#define MAXMONS 5

class MonsterWorld {
    int map[DIM][DIM];
    int xMax, yMax, nMon, nMove;
    Monster mon[MAXMONS];
    Canvas canvas;

    int& Map(int x, int y) { return map[y][x]; }
    bool isDone() { return countItems() == 0; }
    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }

    void print() {
        canvas.clear();
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "■"); // 유니코드 문자 유지
        for (int i = 0; i < nMon; i++)
            mon[i].draw(canvas);
        canvas.print("[ Monster World (Basic) ]");

        cout << " 전체 이동 횟수 = " << nMove << endl;
        cout << " 남은 아이템 수 = " << countItems() << endl;
        for (int i = 0; i < nMon; i++)
            mon[i].print();
    }

public:
// 2. MonsterWorld 생성자 및 초기화
    // 맵의 크기 설정, Canvas 객체 초기화됨
    MonsterWorld(int w, int h) : canvas(w, h), xMax(w), yMax(h) {
        nMon = 0;
        nMove = 0;
        for (int y = 0; y < yMax; y++)
            // 전체 위치에 아이템(1)을 배치함
            for (int x = 0; x < xMax; x++) Map(x, y) = 1;
    }

// 3. add() 함수 - 몬스터 배열(mon[])에 새 몬스터 추가
    ~MonsterWorld() { }
    void add(const Monster& m) {
        if (nMon < MAXMONS) mon[nMon++] = m;
    }

    
// 4. play() 함수 - 몬스터가 maxwalk만큼 움직이는 메인 루프
    // 이동할 때마다 print()로 상태를 화면에 보여줌.
    void play(int maxwalk, int wait) {
        print();   // 맵 출력
        cout << " 엔터를 누르세요...";
        getchar();
        for (int i = 0; i < maxwalk; i++) {
            for (int k = 0; k < nMon; k++)
                mon[k].move(map, xMax, yMax);  // 몬스터 이동
            nMove++;          
            print();    // 다시 출력
            if (isDone()) break;  // 아이템이 모두 없어지면 종료
            usleep(wait * 1000); // 잠시 대기
        }   //이동이 끝나거나, 모든 아이템을 먹으면 종료.

    }
};