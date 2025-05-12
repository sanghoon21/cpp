#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#define MAXLINES 100
using namespace std;

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
    void clear(string val = ".") {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                draw(x, y, val);
    }
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