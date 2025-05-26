// 1. 게임 초기화, 몬스터 추가, 게임 루프 실행을 통해 전체 게임을 시작하고 관리.

// 2. 프로그램의 전체 동작 과정
//? 2-1. 게임 초기화 - (2), (4)
//  MonsterWorldGame.cpp에서 MonsterWorld 객체를 생성.
//  16x8 크기의 게임 맵(Matrix)을 초기화, 모든 칸을 아이템으로 채움.
//  이후 다양한 몬스터와 두 플레이어(Tuman)를 추가.
//? 2-2. 게임 루프 시작
//  MonsterWorld::play 메서드가 호출되어 초기 맵과 몬스터 상태를 출력 후, 사용자 입력(엔터)을 기다림.
//  이후 몬스터 최대 500번의 이동 또는 종료 조건(아이템 소진 또는 플레이어 1명 이하)까지 루프를 실행.
//? 2-3. 몬스터 이동
//  일반 몬스터(플레이어 제외)는 각자의 move 메서드를 호출하여 맵 위를 고유한 패턴으로 이동.
//  이동 후 맵 경계를 체크(clip)하고 아이템을 먹거나 에너지를 소모(eat).
//? 2-4. 플레이어 이동 - (1), (3), (5)
//  두 Tuman 객체가 키보드 입력에 따라 이동.
//  왼쪽 플레이어는 'w', 's', 'a', 'd' 키로, 오른쪽 플레이어는 화살표 키로 이동.
//  입력은 MonsterWorld::play에서 처리됨.
//? 2-5. 아사 확인
//  checkStarvation에서 일반 몬스터의 에너지가 0이면 제거하고 배열을 재정렬함.
//  플레이어(pMon[nMon-2], pMon[nMon-1])는 제외.
//? 2-6. 게임 상태 출력
//  Canvas를 통해 맵을 시각화함. 이동 횟수, 남은 아이템 수, 몬스터별 상태를 출력. 
//? 2-7. 종료 조건
//  아이템이 모두 소진되거나(countItems() == 0), 플레이어가 1명 이하(nMon < 2)면 게임이 종료됩니다.

#include "MonsterWorld.h"
#include "VariousMonsters.h"
#include "Human.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


// 4-27. 16*8 크기의 MonsterWorld 객체 생성.
//       play() 함수 호출로 게임 시작.
int main() {
    srand((unsigned int)time(NULL));
    int w = 16, h = 8;
    MonsterWorld game(w, h);

//! (2) Tuman 생성자에서 icon 파라미터를 통해 "☜" (왼쪽 플레이어)와 "☞" (오른쪽 플레이어)를 설정.
//!  "좌", "우"로 설정 시 맵이 흔들려서 문자표를 사용해서 손가락 모양으로 구현.
//!  이 아이콘은 Canvas의 draw()를 통해 게임 맵에 출력
    game.add(new Zombie("허접한좀비", "§", rand() % w, rand() % h));
    game.add(new Vampire("뱀파이어짱", "★", rand() % w, rand() % h));
    game.add(new KGhost("어쩌다귀신", "♥", rand() % w, rand() % h));
    game.add(new Jiangshi("못먹어도고", "↔", rand() % w, rand() % h, true));
    game.add(new Jiangshi("못먹어세로", "↕", rand() % w, rand() % h, false));
    game.add(new Smombi("나는스몸비", "↘", rand() % w, rand() % h));
    game.add(new Siangshi("난수퍼강시", "⇄", rand() % w, rand() % h, true));
    game.add(new KGhostold("노처녀귀신", "♡", rand() % w, rand() % h));
    game.add(new Tuman("미래의좌파", "☜", rand() % w, rand() % h, false)); // 왼쪽 플레이어
    game.add(new Tuman("미래의우파", "☞", rand() % w, rand() % h, true));  // 오른쪽 플레이어
    game.play(500, 300); // 게임 시작.
    cout << "------게임 종료-------------------" << endl;
    return 0;
}
//! (4) add()를 통해 8개의 일반 몬스터를 먼저 배열(pMon)에 추가.
//!  그 후 두 Tuman 객체를 추가하여 pMon[nMon-2](왼쪽, isRightPlayer=false)와,
//!  pMon[nMon-1](오른쪽, isRightPlayer=true)로 설정.
//!  MonsterWorld::add()가 pMon 배열에 몬스터를 순차적으로 추가하며 nMon을 증가시킴.