#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomMap(int map[5][5]) {
    srand(time(NULL)); // 난수 생성기 초기화
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            map[i][j] = rand() % 2; // 0 또는 1 할당
        }
    }
}

void printMap(int map[5][5]) {
    printf("+---+---+---+---+---+\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("| %d ", map[i][j]);
        }
        printf("|\n+---+---+---+---+---+\n");
    }
}

// 테스트용 메인 함수
int main() {
    int map[5][5];
    randomMap(map);
    printMap(map);
    return 0;
}