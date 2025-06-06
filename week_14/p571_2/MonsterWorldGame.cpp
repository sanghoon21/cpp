// 1. 게임 초기화, 몬스터 추가, 게임 루프 실행을 통해 전체 게임을 시작하고 관리.

// 2. 프로그램의 전체 동작 과정
//? 2-1. 게임 초기화
//  MonsterWorldGame.cpp에서 MonsterWorld 객체를 생성.
//  16x8 크기의 게임 맵(Matrix)을 초기화, 모든 칸을 아이템으로 채움.
//  이후 다양한 몬스터와 두 플레이어(Tuman)를 추가.
//? 2-2. 게임 루프 시작
//  MonsterWorld::play 메서드가 호출되어 초기 맵과 몬스터 상태를 출력 후, 사용자 입력(엔터)을 기다림.
//  이후 몬스터 최대 500번의 이동 또는 종료 조건(아이템 소진 또는 플레이어 1명 이하)까지 루프를 실행.
//? 2-3. 몬스터 이동
//  일반 몬스터(플레이어 제외)는 각자의 move 메서드를 호출하여 맵 위를 고유한 패턴으로 이동.
//  이동 후 맵 경계 체크(clip)하고 아이템을 먹거나 에너지를 소모(eat), 휴식 여부 확인.
//? 2-4. 플레이어 이동
//  두 Tuman 객체가 키보드 입력에 따라 이동.
//  왼쪽 플레이어는 'w', 's', 'a', 'd' 키로, 오른쪽 플레이어는 화살표 키로 이동.
//  입력은 MonsterWorld::play에서 처리됨.
//? 2-5. 아사 확인
//  checkStarvation에서 일반 몬스터의 에너지가 0이면 제거하고 배열을 재정렬함.
//  플레이어(pMon[nMon-2], pMon[nMon-1])는 제외.
//? 2-6. 게임 상태 출력
//  Canvas를 통해 맵을 시각화함. 이동 횟수, 남은 아이템 수, 몬스터별 상태(에너지, 휴식 시간)를 출력. 
//? 2-7. 종료 조건
//  아이템이 모두 소진되거나(countItems() == 0), 플레이어가 1명 이하(nMon < 2)면 게임이 종료됨.
//? 2-8. 랭킹 관리 - 실습문제 2번
//  게임 시작 전 RankingBoard 객체를 생성하고, 파일에서 랭킹을 로드(실패 시 비밀번호 입력 요구).
//  게임 종료 후 두 플레이어의 아이템 수와 이동 효율성을 계산하여 랭킹에 추가하고, 결과를 파일에 저장.

// +Ch 08 - 에너지 아사 기능.
// +Ch 09 - 여러 몬스터 추가.
// +Ch 10 - Tuman 클래스로 2명의 플레이어 가능.
// +Ch 11 - 좌표상의 이동 거리에 따라 휴식.
// +Ch 12 - 예외처리 사용한 랭킹 파일 관리.

#include "MonsterWorld.h"
#include "VariousMonsters.h"
#include "Human.h"
#include "RankingBoard.h" // 랭킹 보드 추가
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <termios.h> // 비밀번호 입력 처리를 위해 추가
#include <unistd.h>  // 비밀번호 입력 처리를 위해 추가
using namespace std;

// 우분투 환경에서 getch() 구현 (즉시 입력을 위해)
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// 4-27. 16*8 크기의 MonsterWorld 객체 생성.
//       play() 함수 호출로 게임 시작.
int main() {
    RankingBoard rank; // 랭킹 보드 객체 생성
    try {
        //! 예외가 발생할 수 있는 코드
        rank.load("MonsterWorld.rnk"); // 랭킹 파일 읽기 시도 -> RankingBoard.h
        // 파일 열기 성공하면 MVP 배열에 랭킹 정보를 로드함. 근데 실패하면? 예외.
    }
    //! 던진 예외를 받아서 처리.
    //!  -처리 방식
    //!    사용자에게 관리자 비밀번호 입력 요청
    //!    비밀번호 맞으면 - 기본 랭킹으로 진행
    //!    비밀번호 틀리면 - 게임 종료. (exit(0))
    //!해당 예외 처리를 통해 파일이 없거나 읽을 수 없는 경우(예: 파일 손상, 권한 문제)
    //!게임이 비정상 종료되지 않고 적절히 대응하도록 함.
    catch (FileException e) {
        char str[80];
        string passwd, correct = "123456"; // 관리자 비밀번호
        cout << "관리자 비밀번호를 입력하세요: ";
        for (int i = 0;; i++) {
            str[i] = getch();
            if (str[i] == '\n') { // 엔터 입력 시 종료
                str[i] = '\0';
                passwd = str;
                cout << "\n";
                break;
            }
            putchar('*'); // 입력된 문자 대신 * 출력
        }
        if (passwd != correct) {
            cout << "비밀번호가 맞지 않습니다. 게임 종료.\n\n";
            exit(0);
        }
        // 비밀번호가 맞으면 기본 랭킹으로 진행 (이미 RankingBoard 생성자에서 기본값 설정됨)
    }
    rank.print("[게임 랭킹: 시작]"); // 게임 시작 전 랭킹 출력

    srand((unsigned int)time(NULL));
    int w = 16, h = 8;
    MonsterWorld game(w, h);

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

    game.play(500, 50); // 게임 시작.
    cout << "------게임 종료-------------------" << endl;

    // 게임 종료 후 두 플레이어의 랭킹 갱신 및 저장
    Tuman* leftPlayer = (Tuman*)game.getMonster(game.getNMon() - 2);  // 왼쪽 플레이어
    Tuman* rightPlayer = (Tuman*)game.getMonster(game.getNMon() - 1); // 오른쪽 플레이어
    double leftIpm = (leftPlayer->getTotal() > 0) ? leftPlayer->getNItem() / leftPlayer->getTotal() : 0.0;
    double rightIpm = (rightPlayer->getTotal() > 0) ? rightPlayer->getNItem() / rightPlayer->getTotal() : 0.0;

    // 두 플레이어의 성과 비교 후 더 높은 순위 플레이어에게 먼저 이름 입력 요청
    if (leftPlayer->getNItem() >= rightPlayer->getNItem()) {
        rank.add(leftPlayer->getNItem(), leftIpm, leftPlayer->getIsRightPlayer());   // 왼쪽 플레이어 먼저
        rank.add(rightPlayer->getNItem(), rightIpm, rightPlayer->getIsRightPlayer()); // 오른쪽 플레이어 나중에
    } else {
        rank.add(rightPlayer->getNItem(), rightIpm, rightPlayer->getIsRightPlayer()); // 오른쪽 플레이어 먼저
        rank.add(leftPlayer->getNItem(), leftIpm, leftPlayer->getIsRightPlayer());   // 왼쪽 플레이어 나중에
    }
    rank.print("[게임 랭킹: 종료]");

    // 랭킹 저장 시 예외 처리 추가 - 실숩문제 2번
    try {
        rank.store("MonsterWorld.rnk"); // 랭킹 파일 저장 시도
    }

    //!해당 예외 처리를 통해 파일에 새 랭킹을 쓰지 못하는 경우(쓰기권한X)
    //!게임이 비정상 종료되지 않고 적절히 대응하도록 함.
    //! 파일에 쓰지 못하는 예외가 발생함
    //! -> 비밀번호 입력받아서 맞으면 새로운 파일에 랭킹을 저장할 수 있도록 예외 처리.
    catch (FileException e) {
        char str[80];
        string passwd, correct = "123456"; // 관리자 비밀번호
        cout << "랭킹 저장 실패. 관리자 비밀번호를 입력하세요: ";
        for (int i = 0;; i++) 
        {
            str[i] = getch();
            if (str[i] == '\n') { // 엔터 입력 시 종료
                str[i] = '\0';
                passwd = str;
                cout << "\n";
                break;
            }
            putchar('*'); // 입력된 문자 대신 * 출력
        }
        if (passwd != correct) {
            cout << "비밀번호가 맞지 않습니다. 랭킹 저장 없이 게임 종료.\n\n";
            exit(0);
        }
        // 비밀번호가 맞으면 새 파일 이름 입력받아 저장
        string newFilename;
        cout << "새로운 랭킹 파일 이름을 입력하세요: ";
        getline(cin, newFilename);
        rank.store(newFilename); // 새 파일에 랭킹 저장
    }

    return 0;
}

// 테스트 - 파일의 쓰기 권한 제거해보기.
// 원래라면 파일 저장에 실패하면 '오류'이기에 더 이상 어떤 것도 진행X
// 그러나 파일 쓰기 실패시의 '예외'를 지정했기에 예외 처리 코드가 실행됨.
//   => 비밀번호를 쳐서 맞으면 새 파일에 랭킹 저장. 틀리면 그냥 저장 없이 종료.
// touch MonsterWorld.rnk
// chmod -w MonsterWorld.rnk