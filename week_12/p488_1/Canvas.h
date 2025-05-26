// 1. 게임 맵을 시각적으로 표현하기 위한 캔버스 관리 및 출력 기능 제공.

#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#define MAXLINES 100
using namespace std;


//* Canvas: 게임 맵을 문자열 배열로 관리하고 시각적으로 출력.
class Canvas {
    string grid[MAXLINES][MAXLINES]; // 2차원 배열로 각 칸에 문자열 저장
    int xMax, yMax;                  // 맵의 크기

public:

// 4-44. 생성자 - grid를 "."으로 초기화.
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) 
    {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                grid[y][x] = "."; // 각 칸을 "."으로 초기화
    }

// 4-45. draw() - 지정된 위치에 문자열(val) 저장.
    void draw(int x, int y, string val) 
    {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax)
            grid[y][x] = val; // 유니코드 문자열 전체를 저장
    }

// 4-46. clear() - 모든 칸을 지정된 문자열(기본 ".")로 초기화.
    void clear(string val = ".") 
    {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                draw(x, y, val);
    }

// 4-47. print() - 화면 지우고 제목, 맵 출력.
    void print(const char *title = "<My Canvas>") 
    {
        system("clear");
        cout << title << endl;
        for (int y = 0; y < yMax; y++) 
        {
            for (int x = 0; x < xMax; x++) 
            {
                cout << grid[y][x] << " "; // 각 칸을 그대로 출력하고 공백 추가
            }
            cout << endl;
        }
        cout << endl;
    }
};