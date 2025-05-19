// 1. 메인 프로그램
//    main 함수에서 랜덤 시드 설정, 게임 객체 생성, 8개의 몬스터 추가.
//    play 호출로 게임을 시작함.
//    몬스터 초기 위치는 무작위로 설정됨.
//    게임 종료 후 메시지 출력

// 2. 프로그램 전체 동작 순서
//    2-1 ~ 2-4 : 프로그램 시작 및 초기화
//    2-5 ~ 2-6 : 몬스터 객체 생성 및 추가 (MonsterWorldGame.cpp)
//    2-7 ~ 2-9 : 게임 시작 및 초기 화면 출력
//    2-10 ~ 2-13 : 게임 루프 실행 (MonsterWorld.h)
//    2-14 ~ 2-15 : 게임 종료 (MonsterWorldGaem.cpp, MonsterWorld.h)

#include "MonsterWorld.h"
#include "VariousMonsters.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int main()
{
// 2-1. 랜덤 시드를 설정.
    srand((unsigned int)time(NULL));

// 2-2. 맵의 크기 정의하는 변수. 가로 세로
    int w = 16, h = 8;

// 2-3. 객체 생성: MonsterWorld game(w,h) 객체. MonsterWorld.h에 해당 클래스 정의됨.
//      이 과정에서 생성자 호출됨 2-4
    MonsterWorld game(w, h);

// 2-5. 8개의 new 연산자로 동적 객체 생성
// ex) new Zombie(...)는 VariousMonsters.h에 정의된 Zombie 클래스의 객체를 생성함.
//   각 생성자는 Monster.h에 정의된 Monster 클래스의 생성자를 호출하며 이름, 아이콘, 무작위 위치를 설정함.
//   Jiangshi와 Siangshi는 추가로 bHori 플래그를 받음.
// game.add(new...)는 MonsterWorld.h의 add()를 호출함 2-6
//! 4. 변경 후: 3개의 새로운 몬스터가 추가됨.
    game.add(new Zombie("허접한좀비", "§", rand() % w, rand() % h));
    game.add(new Vampire("뱀파이어짱", "★", rand() % w, rand() % h));
    game.add(new KGhost("어쩌다귀신", "♥", rand() % w, rand() % h));
    game.add(new Jiangshi("못먹어도고", "↔", rand() % w, rand() % h, true));
    game.add(new Jiangshi("못먹어세로", "↕", rand() % w, rand() % h, false));
    game.add(new Smombi("스몸비", "↘", rand() % w, rand() % h));
    game.add(new Siangshi("수퍼강시", "⇄", rand() % w, rand() % h, true));
    game.add(new KGhostold("노처녀귀신", "♡", rand() % w, rand() % h));

// 2-7. play() 호출됨. MonsterWorld.h 2-8
    game.play(500, 400);

// 2-15. 종료 메시지 출력 후 프로그램 종료.
    cout << "------게임 종료-------------------" << endl;
    return 0;
}