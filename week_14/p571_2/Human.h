// 1. Human 클래스를 정의하고, 키보드 입력을 통한 플레이어 이동을 구현.

#pragma once
#include "Monster.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// 4-37. 키보드 입력을 비차단 방식으로 처리하기 위한 설정 (우분투에 맞게 kbhit() 만들기)
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

//* 3-11. Human: 키보드 입력으로 이동하며, Point 객체를 사용해 좌표를 관리하는 기본 플레이어 클래스.
class Human : public Monster {
public:
// 4-38. 생성자 - 기본 몬스터 생성자 호출.
    Human(string n = "미래인류", string i = "♀", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
// 4-38-1. 소멸자 - [Human] 출력.
    ~Human() { cout << " [Human]"; }  

// 4-39. move() - 화살표 키 입력으로 상하좌우 이동, Point 객체를 사용해 좌표 관리.
    void move(int** map, int maxx, int maxy) {
        if (kbhit()) {
            struct termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);

            int ch = getchar();
            if (ch == 27) { // ESC 키 (방향키는 ESC [ A/B/C/D 형태로 시작)
                getchar(); // '[' 건너뛰기
                ch = getchar();
                if (ch == 'A') p[1]--; // 위
                else if (ch == 'B') p[1]++; // 아래
                else if (ch == 'C') p[0]++; // 오른쪽
                else if (ch == 'D') p[0]--; // 왼쪽
            }

            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            clip(maxx, maxy);
            eat(map);
        }
    }
};

//* 3-12. Tuman: 두 플레이어(왼쪽: WASD, 오른쪽: 화살표 키)를 구분하며, Point 객체를 사용해 좌표를 관리.
class Tuman : public Human {   
    bool isRightPlayer; 

public:
// 4-40. 생성자 - Human 생성자 호출, isRightPlayer 설정.
    Tuman(string n = "미래의인류", string i = "♀", int px = 0, int py = 0, bool rightPlayer = false)
        : Human(n, i, px, py), isRightPlayer(rightPlayer) {}
// 4-40-1. 소멸자 - [Tuman] 출력.
    ~Tuman() { cout << " [Tuman]"; }

// 4-42. moveHuman() - isRightPlayer에 따라 화살표 키 또는 WASD로 이동, Point 객체를 사용.
    void moveHuman(int** map, int maxx, int maxy, unsigned char ch) {
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        if (isRightPlayer) {
            // 오른쪽 플레이어: 화살표 키 ('A', 'B', 'C', 'D')
            if (ch == 'A') p[1]--; // 위
            else if (ch == 'B') p[1]++; // 아래
            else if (ch == 'C') p[0]++; // 오른쪽
            else if (ch == 'D') p[0]--; // 왼쪽
        } else {
            // 왼쪽 플레이어: 'w', 's', 'a', 'd' 키
            if (ch == 'w' || ch == 'W') p[1]--;
            else if (ch == 's' || ch == 'S') p[1]++;
            else if (ch == 'a' || ch == 'A') p[0]--;
            else if (ch == 'd' || ch == 'D') p[0]++;
        }

        clip(maxx, maxy);
        eat(map);

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }

// 4-42-1. move() - 오버라이드하여 빈 구현으로 유지, moveHuman() 사용.
    void move(int** map, int maxx, int maxy) override 
    {
    }

// 4-42-2. getIsRightPlayer() - isRightPlayer 값 반환.
    bool getIsRightPlayer() const { return isRightPlayer; }
};