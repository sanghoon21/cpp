#include "Ranking.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

#define MAX_DIM 5

enum Direction { Left = 'a', Right = 'd', Up = 'w', Down = 's' };
static int map[MAX_DIM][MAX_DIM];
static int x, y, DIM;
static int nMove;
static int finalMove;
static std::chrono::time_point<std::chrono::high_resolution_clock> tStart, tLastMove;
static std::vector<char> moveHistory;
static int shuffledMap[MAX_DIM][MAX_DIM]; // 최초 섞인 맵 저장
static int shuffledX, shuffledY;          // 최초 섞인 상태의 빈칸 위치 저장

static void init(int size) {
    DIM = size;
    for (int i = 0; i < DIM * DIM - 1; i++) 
        map[i / DIM][i % DIM] = i + 1;
    map[DIM - 1][DIM - 1] = 0;
    x = DIM - 1; y = DIM - 1;
    srand(time(NULL));
    tStart = std::chrono::high_resolution_clock::now();
    tLastMove = tStart;
    nMove = 0;
    finalMove = 0;
    moveHistory.clear();
}

static void display(bool isReplay = false) {
    system("clear");
    printf("\tFifteen Puzzle (%dx%d)\n\t", DIM, DIM);
    printf("--------------\n\t");
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] > 0)
                printf("%3d", map[r][c]);
            else printf("   ");
        }
        printf("\n\t");
    }
    printf("--------------\n\t");
    
    auto tNow = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = tNow - tStart;
    printf("\n\t이동 횟수:%6d\n\t소요 시간:%6.1f초\n\n", isReplay ? finalMove : nMove, elapsed.count());
    if (!isReplay) {
        printf("이동: w(위), a(왼쪽), s(아래), d(오른쪽), q(저장 후 종료)\n");
    }
}

static bool move(char dir, bool record = true) {
    if (dir == 'd' && x > 0) {
        map[y][x] = map[y][x - 1];
        map[y][--x] = 0;
    } 
    else if (dir == 'a' && x < DIM - 1) {
        map[y][x] = map[y][x + 1];
        map[y][++x] = 0;
    } 
    else if (dir == 'w' && y < DIM - 1) {
        map[y][x] = map[y + 1][x];
        map[++y][x] = 0;
    } 
    else if (dir == 's' && y > 0) {
        map[y][x] = map[y - 1][x];
        map[--y][x] = 0;
    } 
    else return false;

    nMove++;
    if (record) {
        moveHistory.push_back(dir); // 사용자의 이동만 기록
    }
    tLastMove = std::chrono::high_resolution_clock::now();
    return true;
}

static void shuffle(int nShuffle) {
    for (int i = 0; i < nShuffle; i++) {
        char keys[] = {'w', 'a', 's', 'd'};
        char key = keys[rand() % 4];
        if (move(key, false) == false) { i--; continue; } // shuffle 이동은 기록 안 함
        display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    // 섞기가 끝난 후 맵과 빈칸 위치 저장
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            shuffledMap[r][c] = map[r][c];
        }
    }
    shuffledX = x;
    shuffledY = y;
}

static bool isDone() {
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] != r * DIM + c + 1)
                return (r == DIM - 1) && (c == DIM - 1);
        }
    }
    return true;
}

static char getDirKey() { 
    char c = getchar();
    while (getchar() != '\n'); // 입력 버퍼 비우기
    return c;
}

static void replay() {
    printf("\n리플레이를 시작합니다...\n");
    // 최초 섞인 상태로 복원
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            map[r][c] = shuffledMap[r][c];
        }
    }
    x = shuffledX;
    y = shuffledY;
    nMove = 0;

    // 섞인 상태를 먼저 보여줌
    display(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1초 대기

    // 사용자의 이동 히스토리를 순차적으로 적용, 퍼즐이 맞춰지면 중단
    for (char dir : moveHistory) {
        move(dir, false); // 리플레이 시 기록하지 않음
        display(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (isDone()) {
            break; // 퍼즐이 맞춰지면 리플레이 종료
        }
    }
}

static void saveGame(const char* filename) {
    std::ofstream out(filename);
    if (!out) {
        printf("저장 실패!\n");
        return;
    }
    out << DIM << "\n";
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            out << map[r][c] << " ";
        }
        out << "\n";
    }
    out << x << " " << y << "\n";
    out << nMove << "\n";
    auto elapsed = std::chrono::duration<double>(tLastMove - tStart).count();
    out << elapsed << "\n";
    out << moveHistory.size() << "\n";
    for (char dir : moveHistory) {
        out << dir << " ";
    }
    out << "\n";
    out.close();
    printf("게임이 저장되었습니다.\n");
}

static bool loadGame(const char* filename) {
    std::ifstream in(filename);
    if (!in) {
        return false;
    }
    in >> DIM;
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            in >> map[r][c];
        }
    }
    in >> x >> y;
    in >> nMove;
    double elapsed;
    in >> elapsed;
    tStart = std::chrono::high_resolution_clock::now() - std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(std::chrono::duration<double>(elapsed));
    tLastMove = tStart; // tLastMove도 저장된 시간 기준으로 설정
    int moveCount;
    in >> moveCount;
    moveHistory.clear();
    for (int i = 0; i < moveCount; i++) {
        char dir;
        in >> dir;
        moveHistory.push_back(dir);
    }
    in.close();
    // 저장된 게임의 섞인 상태를 복원
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            shuffledMap[r][c] = map[r][c];
        }
    }
    shuffledX = x;
    shuffledY = y;
    return true;
}

int playFifteenPuzzle(int size) {
    char choice;
    printf("새 게임(n) 또는 저장된 게임 이어하기(l)? (n/l): ");
    std::cin >> choice;
    while (getchar() != '\n'); // 입력 버퍼 비우기

    if (choice == 'l' || choice == 'L') {
        if (!loadGame("savegame.txt")) {
            printf("저장된 게임이 없습니다. 새 게임을 시작합니다.\n");
            init(size);
        } else {
            // 저장된 상태를 유지하며 표시
            display();
            printRanking();
            printf("\n 엔터 키를 눌러 게임을 이어하세요...");
            getchar();
            moveHistory.clear(); // 저장 이후의 이동만 기록
            // nMove, tStart, tLastMove는 loadGame에서 읽어온 값 유지
        }
    } else {
        init(size);
        display();
        printRanking();
        printf("\n 엔터 키를 눌러 섞기를 시작하세요...");
        getchar();
        shuffle(100);
        printf("\n 엔터 키를 눌러 게임을 시작하세요...");
        getchar();
        tStart = std::chrono::high_resolution_clock::now();
        tLastMove = tStart;
        nMove = 0;
        moveHistory.clear(); // 게임 시작 전 moveHistory 초기화
    }

    while (!isDone()) {
        char dir = getDirKey();
        if (dir == 'q' || dir == 'Q') {
            saveGame("savegame.txt");
            return 0; // 게임 종료
        }
        move(dir, true); // 사용자의 이동 기록
        display();
    }

    auto tEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = tEnd - tStart;
    finalMove = nMove;
    printf("\n게임이 끝났습니다!\n");

    char replayChoice;
    printf("리플레이를 하시겠습니까? (y/n): ");
    std::cin >> replayChoice;
    if (replayChoice == 'y' || replayChoice == 'Y') {
        replay();
    }

    return addRanking(finalMove, elapsed.count());
}