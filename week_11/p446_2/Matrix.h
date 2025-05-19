// 1. Matrix 클래스 - 2차원 정수 배열을 다룸.
//    맵의 아이템 상태 저장, 동적 메모리 할당으로 크기 조절 가능
//    게임의 논리적 데이터 관리
//      => 데이터 접근(elem, Data), 크기 조회(Rows, Cols), 출력(print), 무작위 값 설정(setRand) 같은 기능을 제공


#pragma once
#include <iostream>
#include <iomanip>
using namespace std;


class Matrix {
    int rows, cols;        // 행과 열의 크기
    int** mat;             // 실제 행렬 데이터
public:
    Matrix(int r = 0, int c = 0) : rows(r), cols(c), mat(NULL) {
        if (rows <= 0 || cols <= 0) {
            rows = cols = 0;
            return;
        }
        mat = new int*[rows];
        for (int i = 0; i < rows; i++)
            mat[i] = new int[cols](); // 0으로 초기화
    }
    ~Matrix() {
        if (mat != NULL) {
            for (int i = 0; i < rows; i++)
                delete[] mat[i];
            delete[] mat;
        }
    }
    int& elem(int x, int y) { return mat[x][y]; } // x, y 순서 변경
    int Rows() { return rows; }
    int Cols() { return cols; }
    int** Data() { return mat; }
    void print(const char *str = "Mat") {
        cout << str << " " << rows << "x" << cols << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << setw(4) << mat[i][j];
            cout << "\n";
        }
    }
    void setRand(int val = 100) {
        if (mat != NULL) {
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    mat[i][j] = (rand() % val);
        }
    }
};