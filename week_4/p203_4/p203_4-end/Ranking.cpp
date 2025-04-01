#include "Ranking.h"
#include <cstdio>
#include <cstring>

#define NUM_MVP 10 // 상위 10개 유지
static PlayInfo MVP[NUM_MVP];  
static int nMVP = NUM_MVP;  

static void initRanking() {
    PlayInfo noname = { "C++ Player", 1000, 1000.0 };
    for (int i = 0; i < nMVP; i++)
        MVP[i] = noname;
}

//랭킹 데이터를 파일에서 불러옴
void loadRanking(const char* fname) {
    FILE* fp = fopen(fname, "rb"); // 이진 읽기 모드
    if (fp == NULL) {
        initRanking();
    } else {
        for (int i = 0; i < nMVP; i++) {
            fread(&MVP[i].nMove, sizeof(int), 1, fp);
            fread(MVP[i].name, sizeof(char), 200, fp); // 최대 200자
            fread(&MVP[i].tElapsed, sizeof(double), 1, fp);
        }
        fclose(fp);
    }
}

//랭킹 데이터 파일에 저장
void storeRanking(const char* fname) {
    FILE* fp = fopen(fname, "wb"); // 이진 쓰기 모드
    if (fp == NULL) return;
    for (int i = 0; i < nMVP; i++) {
        fwrite(&MVP[i].nMove, sizeof(int), 1, fp);
        fwrite(MVP[i].name, sizeof(char), 200, fp); // 최대 200자 고정
        fwrite(&MVP[i].tElapsed, sizeof(double), 1, fp);
    }
    fclose(fp);
}


//랭킹 출력
void printRanking() {
    for (int i = 0; i < nMVP; i++)
        printf("[%2d위] %4d  %-16s %5.1f\n", i + 1, MVP[i].nMove, MVP[i].name, MVP[i].tElapsed);
}


//새로운 기록을 랭킹에 추가하는 함수
int addRanking(int nMove, double tElap) {
    // 만약 새로운 기록이 현재 최하위 랭킹보다 좋으면 추가
    if (nMove < MVP[nMVP - 1].nMove) {
        int pos = nMVP - 1;
        // 새로운 기록을 삽입할 위치를 찾음 (오름차순 정렬)
        for (; pos > 0; pos--) {
            if (nMove >= MVP[pos - 1].nMove) break;
            MVP[pos] = MVP[pos - 1];
        }

        // 새로운 기록을 찾은 위치에 삽입
        MVP[pos].nMove = nMove;
        MVP[pos].tElapsed = tElap;
        printf(" %d위입니다. 이름을 입력하세요: ", pos + 1);
        scanf("%s", MVP[pos].name);
        return pos + 1;
    }
    return 0;
}