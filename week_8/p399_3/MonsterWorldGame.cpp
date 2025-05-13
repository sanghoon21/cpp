// 몬스터 추가, 총 이동 횟수와 대기시간, 게임 종료 메시지 출력

#include "MonsterWorld.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int main() {
    srand((unsigned int)time(NULL));
    int w = 16, h = 8;

    MonsterWorld game(w, h);
    
    game.add(new Monster("몬스터", "※", rand() % w, rand() % h));
    //! 1. 4개의 몬스터 모두 new Monster로 동적 할당된 몬스터 객체를 game.add()에 전달
    //! 몬스터가 동적 객체.
    game.add(new Monster("도깨비", "§", rand() % w, rand() % h));
    game.add(new Monster("별그대", "★", rand() % w, rand() % h));
    game.add(new Monster("고스트", "♥", rand() % w, rand() % h));
    //! 1. 영향: 메모리 누수가 없도록 delete가 필요함.(소멸자에서 처리)
    game.play(500, 200);
    cout << "------게임 종료-------------------" << endl;
    return 0;
}