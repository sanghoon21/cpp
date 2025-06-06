// 1.다양한 몬스터 클래스(Zombie, Vampire 등)를 정의하고, 각 몬스터의 고유한 이동 패턴을 구현.

#pragma once
#include "Monster.h"

//* 3-2. Zombie: 기본 이동 패턴을 따르며, 휴식 기능을 포함한 간단한 몬스터.
class Zombie : public Monster 
{
public:
// 4-12. 생성자 - 기본 몬스터 생성자 호출.
    Zombie(string n = "허접한좀비", string i = "§", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
// 4-13. 소멸자 - [Zombie] 출력.
    ~Zombie() { cout << " [Zombie]"; }

// 4-19. move() - 8방향 중 하나로 랜덤 이동, 휴식 여부 확인 후 clip, eat 호출.
    void move(int** map, int maxx, int maxy) 
    {
        if (!isSleep()) {
            int dir = rand() % 8;
            Point temp;
            switch (dir) 
            {
            case 0: temp = Point(0, -1); break;      // y--
            case 1: temp = Point(1, -1); break;      // x++, y--
            case 2: temp = Point(1, 0); break;       // x++
            case 3: temp = Point(1, 1); break;       // x++, y++
            case 4: temp = Point(0, 1); break;       // y++
            case 5: temp = Point(-1, 1); break;      // x--, y++
            case 6: temp = Point(-1, 0); break;      // x--
            case 7: temp = Point(-1, -1); break;     // x--, y--
            }
            p += temp;
            clip(maxx, maxy);
            eat(map);
        }
    }
};

//* 3-3. Vampire: 4방향(상하좌우) 중 하나로 이동하며, 휴식 기능을 포함.
class Vampire : public Monster 
{
public:
// 4-12. 생성자 - 기본 몬스터 생성자 호출.
    Vampire(string n = "뱀파이어", string i = "★", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
// 4-13. 소멸자 - [Vampire] 출력.
    ~Vampire() { cout << " [Vampire]"; }

// 4-19. move() - 4방향 중 하나로 랜덤 이동, 휴식 여부 확인 후 clip, eat 호출.
    void move(int** map, int maxx, int maxy) 
    {
        if (!isSleep()) {
            int dir = rand() % 4;
            if (dir == 0) p[0]--; // x--
            else if (dir == 1) p[0]++; // x++
            else if (dir == 2) p[1]--; // y--
            else p[1]++; // y++
            clip(maxx, maxy);
            eat(map);
        }
    }
};

//* 3-4. KGhost: 맵 내 랜덤 위치로 텔레포트하며, 휴식 기능을 포함.
class KGhost : public Monster 
{
public:
// 4-12. 생성자 - 기본 몬스터 생성자 호출.
    KGhost(string n = "처녀귀신", string i = "♥", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
// 4-13. 소멸자 - [KGhost] 출력.
    ~KGhost() { cout << " [KGhost]"; }

// 4-19. move() - 랜덤 위치로 텔레포트, 휴식 여부 확인 후 clip, eat 호출.
    void move(int** map, int maxx, int maxy) 
    {
        if (!isSleep()) {
            p = Point(rand() % maxx, rand() % maxy);
            clip(maxx, maxy);
            eat(map);
        }
    }
};

//* 3-5. Jiangshi: 수평/수직 방향으로 1~2칸 점프 이동하며, 휴식 기능을 포함.
class Jiangshi : public Monster 
{
protected:
// 4-14. bHori - 수평/수직 이동 여부.
    bool bHori;
public:
// 4-15. 생성자 - 기본 몬스터 생성자 호출, bHori 설정.
    Jiangshi(string n = "대륙강시", string i = "↔", int x = 0, int y = 0, bool bH = true)
        : Monster(n, i, x, y), bHori(bH) {}
// 4-13. 소멸자 - [Jiangshi] 출력.
    ~Jiangshi() { cout << " [Jiangshi]"; }

// 4-19. move() - 수평/수직으로 점프 이동, 휴식 여부 확인 후 clip, eat 호출.
    void move(int** map, int maxx, int maxy) 
    {
        if (!isSleep()) {
            int dir = rand() % 2;
            int jump = rand() % 2 + 1;
            if (bHori) p[0] += ((dir == 0) ? -jump : jump);
            else p[1] += ((dir == 0) ? -jump : jump);
            clip(maxx, maxy);
            eat(map);
        }
    }
};

//* 3-6. Smombi: 대각선 4방향 중 하나로 이동하며, 휴식 기능을 포함.
class Smombi : public Monster 
{
public:
// 4-12. 생성자 - 기본 몬스터 생성자 호출.
    Smombi(string n = "스몸비", string i = "↘", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
// 4-13. 소멸자 - [Smombi] 출력.
    ~Smombi() { cout << " [Smombi]"; }

// 4-19. move() - 대각선 4방향 중 하나로 이동, 휴식 여부 확인 후 clip, eat 호출.
    void move(int** map, int maxx, int maxy) 
    {
        if (!isSleep()) {
            int dir = rand() % 4;
            if (dir == 0) { p[0]--; p[1]--; } // x--, y--
            else if (dir == 1) { p[0]++; p[1]--; } // x++, y--
            else if (dir == 2) { p[0]--; p[1]++; } // x--, y++
            else { p[0]++; p[1]++; } // x++, y++
            clip(maxx, maxy);
            eat(map);
        }
    }
};

//* 3-7. Siangshi: 50번 이동마다 수평/수직 방향을 전환하며 점프, 휴식 기능을 포함.
class Siangshi : public Jiangshi 
{
    int moveCount;
    const int switchInterval = 50;
public:
// 4-15. 생성자 - Jiangshi 생성자 호출, moveCount 초기화.
    Siangshi(string n = "수퍼강시", string i = "⇄", int x = 0, int y = 0, bool bH = true)
        : Jiangshi(n, i, x, y, bH), moveCount(0) {}
// 4-13. 소멸자 - [Siangshi] 출력.
    ~Siangshi() { cout << " [Siangshi]"; }

// 4-18. move() - 50번마다 bHori 전환, 휴식 여부 확인 후 clip, eat 호출.
    void move(int** map, int maxx, int maxy) 
    {
        if (!isSleep()) {
            moveCount++;
            if (moveCount >= switchInterval) {
                bHori = !bHori;
                moveCount = 0;
            }
            int dir = rand() % 2;
            int jump = rand() % 2 + 1;
            if (bHori) p[0] += ((dir == 0) ? -jump : jump);
            else p[1] += ((dir == 0) ? -jump : jump);
            clip(maxx, maxy);
            eat(map);
        }
    }
};

//* 3-8. KGhostold: 2번 이동마다 랜덤 위치로 텔레포트하며, 휴식 기능을 포함.
class KGhostold : public KGhost 
{
    int moveCount;
public:
// 4-15. 생성자 - KGhost 생성자 호출, moveCount 초기화.
    KGhostold(string n = "노처녀귀신", string i = "♡", int x = 0, int y = 0)
        : KGhost(n, i, x, y), moveCount(0) {}
// 4-13. 소멸자 - [KGhostold] 출력.
    ~KGhostold() { cout << " [KGhostold]"; }

// 4-19. move() - 2번 이동마다 랜덤 텔레포트, 휴식 여부 확인 후 clip, eat 호출.
    void move(int** map, int maxx, int maxy) 
    {
        if (!isSleep()) {
            moveCount++;
            if (moveCount >= 2) {
                p = Point(rand() % maxx, rand() % maxy);
                moveCount = 0;
            }
            clip(maxx, maxy);
            eat(map);
        }
    }
};