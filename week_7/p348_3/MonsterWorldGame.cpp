// main() 함수가 들어있는 메인 파일. 실제 게임이 시작되는 지점.

#include "MonsterWorld.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


// 0. 메인 함수 실행으로 프로그램 시작
int main() {

// 1. 랜덤 시드 설정 후, MonsterWorld 객체를 만들고 몬스터를 추가한 뒤 play() 호출.
    srand((unsigned int)time(NULL));  // 난수 초기화
    int w = 16, h = 8;
    MonsterWorld game(w, h);          // MonsterWorld 객체 생성
    Monster m("몬스터", "※", rand() % w, rand() % h);
    // 몬스터들 추가
    game.add(m);
    game.add(Monster("도깨비", "§", rand() % w, rand() % h));
    game.add(Monster("별그대", "★", rand() % w, rand() % h));
    game.add(Monster("고스트", "♥", rand() % w, rand() % h));
    
    game.play(500, 10);  // 게임 플레이 시작
    cout << "------게임 종료-------------------" << endl;
    return 0;
}