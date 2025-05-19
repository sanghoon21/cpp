// 1. Canvas 클래스 - 게임 화면을 시각적으로 표현함.
//    2차원 맵을 관리하는 역할
//    최대 100 * 100 크기의 문자열 배열(grid)를 사용하여 각 칸에 아이콘, 문자 표시 가능
//    초기화, 그리기(draw), 지우기(clear), 출력(print) 기능 제공.


#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#define MAXLINES 100
using namespace std;

// 2-2.
class Canvas {
    string grid[MAXLINES][MAXLINES]; // 2차원 배열로 각 칸에 문자열 저장
    int xMax, yMax;                  // 맵의 크기
public:
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                grid[y][x] = "."; // 각 칸을 "."으로 초기화
    }
    void draw(int x, int y, string val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax)
            grid[y][x] = val; // 유니코드 문자열 전체를 저장
    }

// 2-9-1. 그리드를 "."으로 초기화함. MonsterWorld.h 2-9-2
    void clear(string val = ".") {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                draw(x, y, val);
    }

// 2-9-3. 
    void print(const char *title = "<My Canvas>") {
        system("clear");
        cout << title << endl;
        for (int y = 0; y < yMax; y++) {
            for (int x = 0; x < xMax; x++) {
                cout << grid[y][x] << " "; // 각 칸을 그대로 출력하고 공백 추가
            }
            cout << endl;
        }
        cout << endl;
    }
};