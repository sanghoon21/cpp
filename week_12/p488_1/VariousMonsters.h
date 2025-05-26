// 1.다양한 몬스터 클래스(Zombie, Vampire 등)를 정의하고, 각 몬스터의 고유한 이동 패턴을 구현.

#pragma once
#include "Monster.h"

//* 3-2. Zombie: 기본 이동 패턴을 따르는 간단한 몬스터.
class Zombie : public Monster 
{
public:
// 4-12. 생성자 (각 몬스터마다)
    Zombie(string n = "허접한좀비", string i = "§", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
// 4-13. 소멸자 (각 몬스터마다)  [Monster의 자식 클래스 이름 출력]
    ~Zombie() { cout << " [Zombie]"; }
};


//* 3-3. Vampire: 4방향(상하좌우) 중 하나로 이동.
class Vampire : public Monster 
{
public:
    Vampire(string n = "뱀파이어", string i = "★", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Vampire() { cout << " [Vampire]"; }

    void move(int** map, int maxx, int maxy) 
    {
        int dir = rand() % 4;
        if (dir == 0) x--;
        else if (dir == 1) x++;
        else if (dir == 2) y--;
        else y++;
        clip(maxx, maxy);
        eat(map);
    }
};


//* 3-4. KGhost: 맵 내 랜덤 위치로 텔레포트.
class KGhost : public Monster 
{
public:
    KGhost(string n = "처녀귀신", string i = "♥", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~KGhost() { cout << " [KGhost]"; }

    void move(int** map, int maxx, int maxy) 
    {
        x = rand() % maxx;
        y = rand() % maxy;
        clip(maxx, maxy);
        eat(map);
    }
};


//* 3-5. Jiangshi: 수평/수직 방향으로 1~2칸 점프 이동.
class Jiangshi : public Monster 
{
protected:
// 4-14. bHori: 수평/수직 이동 여부
    bool bHori;
public:
// 4-15. 생성자에 bHori 설정 포함
    Jiangshi(string n = "대륙강시", string i = "↔", int x = 0, int y = 0, bool bH = true)
        : Monster(n, i, x, y), bHori(bH) {}
    ~Jiangshi() { cout << " [Jiangshi]"; }

    void move(int** map, int maxx, int maxy) 
    {
        int dir = rand() % 2;
        int jump = rand() % 2 + 1;
        if (bHori) x += ((dir == 0) ? -jump : jump);
        else y += ((dir == 0) ? -jump : jump);
        clip(maxx, maxy);
        eat(map);
    }
};


//* 3-6. Smombi: 대각선 4방향 중 하나로 이동.
class Smombi : public Monster 
{
public:
    Smombi(string n = "스몸비", string i = "↘", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Smombi() { cout << " [Smombi]"; }

    void move(int** map, int maxx, int maxy) 
    {
        int dir = rand() % 4;
        if (dir == 0) { x--; y--; }
        else if (dir == 1) { x++; y--; }
        else if (dir == 2) { x--; y++; }
        else { x++; y++; }
        clip(maxx, maxy);
        eat(map);
    }
};


//* 3-7. Siangshi: 50번 이동마다 수평/수직 방향을 전환하며 점프.
class Siangshi : public Jiangshi 
{
// 4-16. moveCount, switchInterval (50번 이동 후 방향 전환)
    int moveCount;
    const int switchInterval = 50;
public:
// 4-17. Monster()가 아닌 Jiangshi 생성자 호출. moveCount 초기화.
    Siangshi(string n = "수퍼강시", string i = "⇄", int x = 0, int y = 0, bool bH = true)
        : Jiangshi(n, i, x, y, bH), moveCount(0) {}
    ~Siangshi() { cout << " [Siangshi]"; }
// 4-18. 50번마다 bHori 전환.
    void move(int** map, int maxx, int maxy) 
    {
        moveCount++;
        if (moveCount >= switchInterval) {
            bHori = !bHori;
            moveCount = 0;
        }
        int dir = rand() % 2;
        int jump = rand() % 2 + 1;
        if (bHori) x += ((dir == 0) ? -jump : jump);
        else y += ((dir == 0) ? -jump : jump);
        clip(maxx, maxy);
        eat(map);
    }
};


//* 3-8. KGhostold: 2번 이동마다 랜덤 위치로 텔레포트.
class KGhostold : public KGhost 
{
    int moveCount;
public:
    KGhostold(string n = "노처녀귀신", string i = "♡", int x = 0, int y = 0)
        : KGhost(n, i, x, y), moveCount(0) {}
    ~KGhostold() { cout << " [KGhostold]"; }
// 4-19. 2번 이동마다 랜덤 텔레포트.
    void move(int** map, int maxx, int maxy) 
    {
        moveCount++;
        if (moveCount >= 2) {
            x = rand() % maxx;
            y = rand() % maxy;
            moveCount = 0;
        }
        clip(maxx, maxy);
        eat(map);
    }
};