// 1. 다양한 몬스터 클래스 정의.
//    Zombie, Vampire, KGhost, Jiangshi, Smombi, Siangshi, KGhostold 클래스가 Monster 클래스를 상속받아 각기 다른 이동 로직(move)을 구현함.
//    각 클래스마다 고유한 이름, 아이콘, 동작 특성을 가짐.
//    상속을 통해 특화된 기능을 제공.

#pragma once
#include "Monster.h"

// 2-10. 모든 몬스터의 move 내부에서..
// 위치 변경 후 clip으로 경계를 체크, eat으로 아이템을 먹음.
// eat은 Monster.h에 정의됨 2-10-1, world.Data()로 Matrix.h의 데이터를 참조.

class Zombie : public Monster {
public:
    Zombie(string n = "허접좀비", string i = "§", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Zombie() { cout << " Zombie"; }
};
    // Zombie 클래스에는 move()가 따로 없다? - 상속받은 Monster 클래스의 move()를 그대로 사용한다는 것.


class Vampire : public Monster {
public:
    Vampire(string n = "뱀파이어", string i = "★", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Vampire() { cout << " Vampire"; }

    void move(int** map, int maxx, int maxy) {
        int dir = rand() % 4;
        if (dir == 0) x--;
        else if (dir == 1) x++;
        else if (dir == 2) y--;
        else y++;
        clip(maxx, maxy);
        eat(map);
    }
};


class KGhost : public Monster {
public:
    KGhost(string n = "처녀귀신", string i = "♥", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~KGhost() { cout << " KGhost"; }

    void move(int** map, int maxx, int maxy) {
        x = rand() % maxx;
        y = rand() % maxy;
        clip(maxx, maxy);
        eat(map);
    }
};


class Jiangshi : public Monster {
protected:  //! 2
    bool bHori;
public:
    Jiangshi(string n = "대륙강시", string i = "↔", int x = 0, int y = 0, bool bH = true)
        : Monster(n, i, x, y), bHori(bH) {}
    ~Jiangshi() { cout << " Jiangshi"; }

    void move(int** map, int maxx, int maxy) {
        int dir = rand() % 2;
        int jump = rand() % 2 + 1;
        if (bHori) x += ((dir == 0) ? -jump : jump);
        else y += ((dir == 0) ? -jump : jump);
        clip(maxx, maxy);
        eat(map);
    }
};

//! 1. 변경 후: Smombi 클래스 추가됨 - Monster 클래스 상속받음
//! Smombi는 대각선 방향(상좌, 상우, 하좌, 하우)으로만 이동하는 새로운 몬스터.
//! 기존 몬스터들과 달리 4방향 대각선 이동을 구현함.
//! move() 함수가 재정의되어 rand() % 4로 4가지 대각선 방향을 선택하며, clip과 eat을 호출해 경계 체크와 아이템 먹기 수행.
class Smombi : public Monster {
public:
    Smombi(string n = "스몸비", string i = "↘", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Smombi() { cout << " Smombi"; }

    void move(int** map, int maxx, int maxy) {
        int dir = rand() % 4; // 4가지 대각선 방향
        if (dir == 0) { x--; y--; }    // 상좌
        else if (dir == 1) { x++; y--; } // 상우
        else if (dir == 2) { x--; y++; } // 하좌
        else { x++; y++; }             // 하우
        clip(maxx, maxy);
        eat(map);
    }
};

//! 2. 변경 후: Siangshi 클래스 추가 - Jiangshi를 상속받아 구현됨
//! 일정 시간마다 가로 세로 방향을 바꾸는 몬스터.
//! moveCount와 switchInterval을 사용해 50번 이동마다 방향(bHori)을 전환함. (가로/세로 -> 세로/가로)
//! 원래 Jiangshi 클래스는 고정된 방향(bHori)으로만 이동하였음. 방향 전환 기능 X
//! 변경 후, Jiangshi의 bHori가 private에서 protected로 변경됨 - Siangshi에서 접근 가능!
class Siangshi : public Jiangshi {
    int moveCount;
    const int switchInterval = 50; // 일정 시간(이동 횟수)마다 방향 전환, 이 값을 수정하면 변경 가능
public:
    Siangshi(string n = "수퍼강시", string i = "⇄", int x = 0, int y = 0, bool bH = true)
        : Jiangshi(n, i, x, y, bH), moveCount(0) {}
    ~Siangshi() { cout << " Siangshi"; }

    void move(int** map, int maxx, int maxy) {
        moveCount++;
        if (moveCount >= switchInterval) {
            bHori = !bHori; // 방향 전환
            moveCount = 0;  // 카운터 초기화
        }
        int dir = rand() % 2;
        int jump = rand() % 2 + 1;
        if (bHori) x += ((dir == 0) ? -jump : jump);
        else y += ((dir == 0) ? -jump : jump);
        clip(maxx, maxy);
        eat(map);
    }
};

//! 3. KGhostold 클래스 추가 - KGhost 클래스를 상속받아 구현됨.
//! KGhost의 순간이동 기능은 유지하되, moveCount를 사용하여 다른 몬스터가 2번 이동 시 1번만 순간이동하도록 함.
class KGhostold : public KGhost {
    int moveCount;
public:
    KGhostold(string n = "노처녀귀신", string i = "♡", int x = 0, int y = 0)
        : KGhost(n, i, x, y), moveCount(0) {}
    ~KGhostold() { cout << " KGhostold"; }

    void move(int** map, int maxx, int maxy) {
        moveCount++;
        if (moveCount >= 2) { // 2번 이동에 1번 순간이동
            x = rand() % maxx;
            y = rand() % maxy;
            moveCount = 0; // 카운터 초기화
        }
        clip(maxx, maxy);
        eat(map);
    }
};