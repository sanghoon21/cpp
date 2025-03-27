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

void checkMap(int map[5][5]) {
    int i, j;
    int found = 0;
    
    // 가로 검사
    for (i = 0; i < 5; i++) {
        if (map[i][0] == map[i][1] && map[i][1] == map[i][2] && map[i][2] == map[i][3] && map[i][3] == map[i][4]) {
            printf("가로 %d번째 줄이 모두 %d입니다.\n", i + 1, map[i][0]);
            found = 1;
        }
    }
    
    // 세로 검사
    for (j = 0; j < 5; j++) {
        if (map[0][j] == map[1][j] && map[1][j] == map[2][j] && map[2][j] == map[3][j] && map[3][j] == map[4][j]) {
            printf("세로 %d번째 열이 모두 %d입니다.\n", j + 1, map[0][j]);
            found = 1;
        }
    }
    
    // 대각선 검사 (좌상단 -> 우하단)
    if (map[0][0] == map[1][1] && map[1][1] == map[2][2] && map[2][2] == map[3][3] && map[3][3] == map[4][4]) {
        printf("왼쪽 위에서 오른쪽 아래로 내려가는 대각선이 모두 %d입니다.\n", map[0][0]);
        found = 1;
    }
    
    // 대각선 검사 (우상단 -> 좌하단)
    if (map[0][4] == map[1][3] && map[1][3] == map[2][2] && map[2][2] == map[3][1] && map[3][1] == map[4][0]) {
        printf("오른쪽 위에서 왼쪽 아래로 내려가는 대각선이 모두 %d입니다.\n", map[0][4]);
        found = 1;
    }
    
    if (!found) {
        printf("가로나 세로 또는 대각선이 모두 같은 값인 경우가 없습니다.\n");
    }
}

// 테스트용 메인 함수
int main() {
    int map[5][5];
    randomMap(map);
    printMap(map);
    checkMap(map);
    return 0;
}