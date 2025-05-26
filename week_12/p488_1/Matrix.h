// 1. 2차원 행렬을 관리하여 게임 맵을 표현하고, 아이템 배치 및 데이터 접근 기능을 제공.

#pragma once
#include <iostream>
#include <iomanip>
using namespace std;


//* 3-9. Matrix: 2차원 행렬로 게임 맵을 관리, 데이터 접근 및 출력 기능 제공하는 클래스.
class Matrix 
{
    int rows, cols;        // 행, 열의 크기
    int** mat;             // 실제 행렬 데이터 (2D 배열)

public:

// 4-20. 생성자
// : 행렬 크기 설정, mat 동적 할당 및 0으로 초기화.
    Matrix(int r = 0, int c = 0) : rows(r), cols(c), mat(NULL) 
    {
        if (rows <= 0 || cols <= 0) 
        {
            rows = cols = 0;
            return;
        }
        mat = new int*[rows];
        for (int i = 0; i < rows; i++)
            mat[i] = new int[cols](); // 0으로 초기화
    }

// 4-21. 소멸자
// : mat 메모리 해제.
    ~Matrix() 
    {
        if (mat != NULL) 
        {
            for (int i = 0; i < rows; i++)
                delete[] mat[i];
            delete[] mat;
        }
    }

// 4-22. elem() - mat[x][y]에 대한 참조 변환
    int& elem(int x, int y) { return mat[x][y]; }

// 4-23. Rows(), Cols() - 행렬의 행/열 크기 반환.
    int Rows() { return rows; }
    int Cols() { return cols; }

// 4-24. data() - mat 배열 포인터 반환.
    int** Data() { return mat; }

// 4-25. print() - 행렬 크기와 내용 출력.
    void print(const char *str = "Mat") 
    {
        cout << str << " " << rows << "x" << cols << endl;
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++)
                cout << setw(4) << mat[i][j];
            cout << "\n";
        }
    }

// 4-26. setRand() - 행렬을 0 ~ val 사이의 랜덤 값으로 채움.
    void setRand(int val = 100) 
    {
        if (mat != NULL) 
        {
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    mat[i][j] = (rand() % val);
        }
    }
};