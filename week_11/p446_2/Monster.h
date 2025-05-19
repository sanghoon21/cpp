// 1. Monster 클래스 - 모든 몬스터의 기본 클래스.
//    이름(name), 아이콘(icon), 위치(x, y), 먹은 아이템 수(nItem)를 관리함
//    맵 경계 체크(clip), 아이템 먹기(eat) 같은 기능 포함.
//    기본 이동 로직(move)은 8방향으로 무작위 이동을 구현함.
//    draw와 print로 화면에 표시하고 상태를 출력함.


#pragma once
#include "Canvas.h"
#define DIM 40

// 2-1. 프로그램 시작 시 모든 몬스터의 기본 클래스 역할을 함.
//      MonsterWorld가 pMon에 저장할 때 이 클래스의 포인터로 관리됨
//      초기화와 기본 이동 로직이 실행의 기초가 됨.
class Monster {
protected:
    string name, icon; // 몬스터 이름과 화면 출력용 아이콘
    int x, y, nItem;   // 현재 위치와 먹은 아이템 수

    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }

// 2-10-1. 
    void eat(int** map) {
        if (map[y][x] == 1) {
            map[y][x] = 0;
            nItem++;
        }
    }
public:
    Monster(string n = "나괴물", string i = "※", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0) {}
    ~Monster() { cout << "\t" << name << icon << "물러갑니다~~~\n"; }

    void draw(Canvas &canvas) { canvas.draw(x, y, icon); }
    void move(int** map, int maxx, int maxy) {
        switch (rand() % 8) {
        case 0: y--; break;
        case 1: x++; y--; break;
        case 2: x++; break;
        case 3: x++; y++; break;
        case 4: y++; break;
        case 5: x--; y++; break;
        case 6: x--; break;
        case 7: x--; y--; break;
        }
        clip(maxx, maxy);
        eat(map);
    }

   // 2-9-5. 각 몬스터의 상태 출력
    void print() { cout << "\t" << name << icon << ":" << nItem << endl; }
};