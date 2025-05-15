#include "Ranking.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#define MAX_DIM 5

enum Direction { Left = 'a', Right = 'd', Up = 'w', Down = 's' };
static int map[MAX_DIM][MAX_DIM];
static int x, y, DIM;
static int nMove;
static int finalMove; // 게임 종료 시 이동 횟수 저장
static std::chrono::time_point<std::chrono::high_resolution_clock> tStart, tLastMove;
static std::vector<char> moveHistory;

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
}

static bool move(char dir) {
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
    tLastMove = std::chrono::high_resolution_clock::now();
    moveHistory.push_back(dir);
    return true;
}

static void shuffle(int nShuffle) {
    for (int i = 0; i < nShuffle; i++) {
        char keys[] = {'w', 'a', 's', 'd'};
        char key = keys[rand() % 4];
        if (move(key) == false) { i--; continue; }
        display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
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

static char getDirKey() { return getchar(); }

static void replay() {
    printf("\n리플레이를 시작합니다...\n");
    for (char dir : moveHistory) {
        move(dir);
        display(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int playFifteenPuzzle(int size) {
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

    while (!isDone()) {
        move(getDirKey());
        display();
    }

    auto tEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = tEnd - tStart;
    finalMove = nMove; // 게임 종료 시 이동 횟수 고정
    printf("\n게임이 끝났습니다!\n");

    char replayChoice;
    printf("리플레이를 하시겠습니까? (y/n): ");
    std::cin >> replayChoice;
    if (replayChoice == 'y' || replayChoice == 'Y') {
        replay();
    }

    return addRanking(finalMove, elapsed.count());
}
