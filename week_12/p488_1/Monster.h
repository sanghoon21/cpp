// 1. 몬스터의 기본 속성과 동작(이동, 아이템 먹기, 에너지 관리)을 정의하며, 상속을 위한 기반 클래스 제공.

#pragma once
#include "Canvas.h"
#define DIM 40


//* 3-1. Monster: 몬스터의 기본 속성(이름, 아이콘, 위치, 아이템 수, 에너지)과
//*               동작(이동, 아이템 먹기, 출력)을 정의하는 클래스.
class Monster 
{

protected:
// 4-1. protected 멤버
// :몬스터의 기본 속성과 정적 카운터 정의.
    string name, icon; // 몬스터 이름, 화면 출력용 아이콘
    int x, y, nItem;   // 현재 위치, 먹은 아이템 수
    int nEnergy;       // 에너지 속성
    static int nMonsters; // 정적 멤버: 몬스터 수


// 4-2. clip()
// :맵 경계 내로 몬스터 위치를 제한(x, y를 0~maxx-1, 0~maxy-1로 조정).
    void clip(int maxx, int maxy) 
    {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }


// 4-3. eat()
// :현재 위치의 아이템(map[y][x] == 1)을 먹으면 nItem++  nEnergy += 8, 아니면 nEnergy--.
    void eat(int** map) 
    {
        if (map[y][x] == 1) 
        {
            map[y][x] = 0;
            nItem++;
            nEnergy += 8; // 아이템 먹으면 에너지 +8
        } else 
        {
            nEnergy = max(0, nEnergy - 1); // 먹지 못하면 에너지 -1
        }
    }


public:

// 4-4. 생성자 Monster()
// : 이름, 아이콘, 초기 위치, 에너지(100) 설정, nMonsters 증가.
    Monster(string n = "나괴물", string i = "※", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) { // 에너지 100 초기화
        nMonsters++; // 몬스터 수 증가
    }


// 4-5. 가상 소멸자
// : 몬스터 이름, 아이콘 출력 후 nMonsters 감소.
    virtual ~Monster() 
    {
        cout << "\t" << name << icon << " 물러갑니다~~~\n";
        nMonsters--; // 몬스터 수 감소
    }


// 4-6. draw()
// : Canvas에 몬스터의 아이콘을 그림.
    void draw(Canvas &canvas) { canvas.draw(x, y, icon); }


// 4-7. move() - 가상
// : 8방향 중 하나로 랜덤 이동, clip, eat 호출.
    virtual void move(int** map, int maxx, int maxy) 
    {
        switch (rand() % 8) 
        {
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


// 4-8. print()
// : 몬스터 이름, 아이콘, 아이템 수, 에너지 출력.
    void print()
    {
        cout << "\t" << name << icon << " :" << nItem << " E:" << nEnergy << endl; // 에너지 출력
    }

// 4-9. getEnergy()
// : 현재 에너지 반환.
    int getEnergy() { return nEnergy; }

// 4-10. printCount() - 정적 함수
// : 전체 몬스터 수 출력.
    static void printCount() { cout << "  전체 몬스터의 수:" << nMonsters << endl; } // "프로그램 2"에서 추가: 정적 함수
};

// 4-11. 정적 멤버 초기화
int Monster::nMonsters = 0;