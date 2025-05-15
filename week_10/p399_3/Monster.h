// 개별 몬스터의 동작과 상태 정의

#pragma once
#include "Canvas.h"
#define DIM 40

class Monster {
    string name, icon; // 몬스터 이름과 화면 출력용 아이콘
    int x, y, nItem;   // 현재 위치와 먹은 아이템 수
    int nEnergy;       // 에너지 속성 추가
    static int nMonsters; // 정적 멤버: 몬스터 수
        //! 1. 정적 멤버 변수로 몬스터 수 관리

    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }
    void eat(int** map) {
    //! 2. 최신: 동적 할당용
        if (map[y][x] == 1) {
            map[y][x] = 0;
            nItem++;
            nEnergy += 8; // 아이템 먹으면 에너지 +8
        } else {
            nEnergy = max(0, nEnergy - 1); // 먹지 못하면 에너지 -1, 최소 0
            //! 에너지 감소 로직을 한 줄로 처리
        }
    }
public:
    Monster(string n = "나괴물", string i = "※", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) { // 에너지 100으로 초기화
        nMonsters++; // 몬스터 수 증가
    }   //! 3. 생성자 소멸자 차이: nMonsters로 몬스터 수 갱신 과정 추가
    ~Monster() {
        cout << "\t" << name << icon << "물러갑니다~~~\n";
        nMonsters--; // 몬스터 수 감소
    }


    void draw(Canvas &canvas) { canvas.draw(x, y, icon); }
    void move(int** map, int maxx, int maxy) {
    //! 4. move() 매개변수가 동적 배열(int**) 기반
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
    void print() { cout << "\t" << name << icon << ":" << nItem << " E:" << nEnergy << endl; }
    int getEnergy() { return nEnergy; } // 에너지 반환 함수
    static void printCount() { cout << "  전체 몬스터의 수:" << nMonsters << endl; } // 정적 함수
};
    //! 5. getEnergy()와 printCount()가 있어 에너지 관리와 몬스터 수 출력 가능.

int Monster::nMonsters = 0; // 정적 멤버 초기화
    //! 6. nMonsters를 0으로 초기화하여 몬스터 수를 전역적으로 관리


    //! 동적 할당(Matrix 호환), 몬스터 수 관리, 에너지 조회 기능이 추가됨