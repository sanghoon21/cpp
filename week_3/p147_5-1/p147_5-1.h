//헤더파일로, RussianRoulette.cpp에서 구현된 함수의 선언을 포함.

//#ifndef ~ #define을 추가해 헤더 파일 중복 포함 방지

#ifndef RUSSIANROULETTE_H
#define RUSSIANROULETTE_H

#include <stdio.h>   //printf, scanf 같은 입출력 기능 사용.
#include <stdlib.h>  //rand(), srand() 같은 난수 기능 사용.
#include <time.h>    //srand(time(NULL))로 난수 시드 초기화.

//playRussianRoulette() 함수 선언
//playRussianRoulette 함수의 인자에 탄창 크기(nChambers) 추가
extern int playRussianRoulette(int nTurns, int nBullets, int nChambers);
                //extern :함수가 다른 파일에 정의되어 있다.

#endif