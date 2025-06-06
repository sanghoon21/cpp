// 1. 몬스터의 기본 속성과 동작(이동, 아이템 먹기, 에너지 관리, 이동 거리 및 휴식 관리)을 정의하며, 상속을 위한 기반 클래스 제공.

#pragma once
#include "Canvas.h"
#include "Point.h"
#define DIM 40

//* 3-1. Monster: 몬스터의 기본 속성(이름, 아이콘, 위치, 아이템 수, 에너지)과
//*               동작(이동, 아이템 먹기, 출력, 휴식 관리)을 정의하는 클래스.
class Monster 
{
protected:
// 4-1. protected 멤버
// :몬스터의 기본 속성과 정적 카운터 정의.
    string name, icon; // 몬스터 이름, 화면 출력용 아이콘
    Point q, p;        // 현재 위치(p)와 이전 위치(q)로 변경
    int nItem;         // 먹은 아이템 수
    int nEnergy;       // 에너지 속성
    int nSleep;        // 추가: 쉬어야 하는 횟수
    double dist;       // 추가: 쉬고 난 다음 움직인 거리
    double total;      // 추가: 총 움직인 거리
    static int nMonsters; // 정적 멤버: 몬스터 수

// 4-2. clip()
// :맵 경계 내로 몬스터 위치를 제한(x, y를 0~maxx-1, 0~maxy-1로 조정).
    void clip(int maxx, int maxy) 
    {
        p(maxx, maxy);
    }

// 4-3. eat()
// :현재 위치의 아이템(map[y][x] == 1)을 먹으면 nItem++  nEnergy += 8, 아니면 nEnergy--.
// :이동 거리를 계산하고, 20 이상 이동 시 휴식 시작.
    void eat(int** map) 
    {
        if (map[p[1]][p[0]] == 1) 
        {
            map[p[1]][p[0]] = 0;
            nItem++;
            nEnergy += 8; // 아이템 먹으면 에너지 +8
        } else 
        {
            nEnergy = max(0, nEnergy - 1); // 먹지 못하면 에너지 -1
        }
        dist += (double)(p - q);  // 이동 거리 계산
        total += (double)(p - q); // 총 이동 거리 누적
        q = p;                    // 이전 위치 업데이트
        if (dist > 20) {          // 20 이상 이동 시 휴식
            dist = 0;
            nSleep = 10;
        }
    }

// 4-20. isSleep()
// :몬스터가 휴식 중인지 확인하고, nSleep을 감소시켜 휴식 종료를 관리.
    bool isSleep() {
        if (nSleep > 0) {
            nSleep--;
            return true;
        }
        else return false;
    }

public:
// 4-4. 생성자 Monster()
// : 이름, 아이콘, 초기 위치, 에너지(100) 설정, nMonsters 증가.
    Monster(string n = "나괴물", string i = "※", int px = 0, int py = 0)
        : name(n), icon(i), p(px, py), q(px, py), nItem(0), nEnergy(100), nSleep(0), dist(0.0), total(0.0) 
    {
        nMonsters++; // 몬스터 수 증가
    }

// 4-5. 가상 소멸자
// : 몬스터 이름, 아이콘, 먹은 아이템 수, 에너지, 총 이동 거리 출력 후 nMonsters 감소.
    virtual ~Monster() 
    {
        cout << "\t" << name << icon << " " << nItem << " E:" << nEnergy << "\t거리:" << total << endl;
        nMonsters--; // 몬스터 수 감소
    }

// 4-6. draw()
// : Canvas에 몬스터의 아이콘을 그림.
    void draw(Canvas &canvas) { canvas.draw(p, icon); }

// 4-7. move() - 가상
// : 8방향 중 하나로 랜덤 이동, 휴식 여부 확인 후 clip, eat 호출.
    virtual void move(int** map, int maxx, int maxy) 
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

// 4-8. print()
// : 몬스터 이름, 아이콘, 아이템 수, 에너지, 휴식 시간 출력.
    void print()
    {
        cout << "\t" << name << icon << " :" << nItem << " E:" << nEnergy << " Sleep:" << nSleep << endl; // 휴식 시간 추가
    }

// 4-9. getEnergy()
// : 현재 에너지 반환.
    int getEnergy() { return nEnergy; }

// 4-10. printCount() - 정적 함수
// : 전체 몬스터 수 출력.
    static void printCount() { cout << "  전체 몬스터의 수:" << nMonsters << endl; } // "프로그램 2"에서 추가: 정적 함수

// Getter 함수 추가: 랭킹 계산을 위해 nItem과 total에 접근
    int getNItem() const { return nItem; }
    double getTotal() const { return total; }
};

// 4-11. 정적 멤버 초기화
int Monster::nMonsters = 0;