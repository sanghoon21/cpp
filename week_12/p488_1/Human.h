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


//* 3-11. Human: 키보드 입력으로 이동하는 기본 플레이어 클래스.
class Human : public Monster {
public:
// 4-38. 생성자 - 기본 몬스터 생성자 호출.
    Human(string n = "미래인류", string i = "♀", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
    ~Human() { cout << " [Human]"; }  // 소멸자 - [Human] 출력

// 4-39. move()
// : 화살표 키 입력으로 상하좌우 이동.
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
                if (ch == 'A') y--; // 위
                else if (ch == 'B') y++; // 아래
                else if (ch == 'C') x++; // 오른쪽
                else if (ch == 'D') x--; // 왼쪽
            }

            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            clip(maxx, maxy);
            eat(map);
        }
    }
};

//! (1) Tuman 클래스에 isRightPlayer를 추가하여 플레이어를 구분함.
//!  오른쪽 플레이어(isRightPlayer == true)는 화살표 키 입력('A': 위, 'B': 아래, 'C': 오른쪽, 'D': 왼쪽)을 처리.
//!  왼쪽 플레이어(isRightPlayer == false)는 'w'(위), 's'(아래), 'a'(왼쪽), 'd'(오른쪽) 입력을 처리.
//!  입력 후 clip으로 맵 경계 체크, eat으로 아이템 소비 및 에너지 관리.

//* 3-12. Tuman: 두 플레이어(왼쪽: WASD, 오른쪽: 화살표 키)를 구분하여 이동하게 하는 클래스.
class Tuman : public Human {   //! (3) Tuman 클래스는 Human 클래스를 상속함.
// 4-40. isRightPlayer - 오른쪽 플레이어인지 여부를 나타냄.
    bool isRightPlayer; 

public:
// 4-41. 생성자 - Human 생성자 호출, isRightPlayer 설정.
    Tuman(string n = "미래의인류", string i = "♀", int px = 0, int py = 0, bool rightPlayer = false)
        : Human(n, i, px, py), isRightPlayer(rightPlayer) {}
    ~Tuman() { cout << " [Tuman]"; }

//! (3) moveHuman()은 입력 문자(ch)를 받아 isRightPlayer에 따라 적절한 이동을 수행.
//!  kbhit()는 사용하지 않으며, play 메서드에서 입력을 받아 전달.
//!  move는 오버라이드하여 빈 구현으로 두어, 일반 몬스터 이동 대신 moveHuman() 사용.
////  터미널 설정(termios)을 통해 비차단 입력을 처리. - 원래 윈도우에서 사용하던 방식을 우분투 방식으로 변형
// 4-42. moveHuman() - isRightPlayer에 따라 화살표 키 또는 WASD로 이동.
    void moveHuman(int** map, int maxx, int maxy, unsigned char ch) {
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        if (isRightPlayer) {
            // 오른쪽 플레이어: 화살표 키 ('A', 'B', 'C', 'D')
            if (ch == 'A') y--; // 위
            else if (ch == 'B') y++; // 아래
            else if (ch == 'C') x++; // 오른쪽
            else if (ch == 'D') x--; // 왼쪽
        } else {
            // 왼쪽 플레이어: 'w', 's', 'a', 'd' 키
            if (ch == 'w' || ch == 'W') y--;
            else if (ch == 's' || ch == 'S') y++;
            else if (ch == 'a' || ch == 'A') x--;
            else if (ch == 'd' || ch == 'D') x++;
        }

        clip(maxx, maxy);
        eat(map);

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }

// 4-43. 빈 구현 - 오버라이드용
    void move(int** map, int maxx, int maxy) override 
    {
    }
};