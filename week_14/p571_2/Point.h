// 1. Point 클래스를 정의하여 게임 내 좌표를 관리하고, 연산자 중복을 활용해 좌표 연산을 지원.

#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//* 3-14. Point: 게임 내 좌표를 객체로 관리하며, 연산자 중복(+, -, += 등)을 통해 좌표 연산을 지원.
//*          Monster와 Canvas가 프렌드 클래스이므로 직접 접근 가능.
class Point {
    int x, y;        // 점의 x와 y 좌표 값
    friend class Monster;    // Monster를 친구 클래스로 등록
    friend class Canvas;    // Canvas를 친구 클래스로 등록
public:
// 4-48. 생성자 - x, y 좌표를 초기화.
    Point(int xx = 0, int yy = 0) : x(xx), y(yy) { }

// 4-49. operator[] - 인덱스(0: x, 1: y)에 따라 좌표 값을 반환.
    int& operator[] (int id) {    
        if (id == 0) return x;
        else if (id == 1) return y;
        else exit(0);
    }

// 4-50. operator double - 좌표의 원점으로부터의 거리(유클리드 거리)를 반환.
    operator double() { return sqrt((double)x*x + y*y); }

// 4-51. operator() - 좌표를 맵 경계 내로 제한.
    void operator()(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }

// 4-52. operator- (단항) - 좌표의 부호를 반전시킨 새 Point 객체 반환.
    Point operator- () { return Point(-x, -y); }

// 4-53. operator== - 두 Point 객체의 좌표가 같은지 비교.
    bool operator== (Point &p) { return x == p.x && y == p.y; }

// 4-54. operator!= - 두 Point 객체의 좌표가 다른지 비교.
    bool operator!= (Point &p) { return x != p.x || y != p.y; }

// 4-55. operator- (이항) - 두 Point 객체의 차이를 계산하여 새 Point 객체 반환.
    Point operator- (Point &p) { return Point(x - p.x, y - p.y); }

// 4-56. operator+ - 두 Point 객체의 합을 계산하여 새 Point 객체 반환.
    Point operator+ (Point &p) { return Point(x + p.x, y + p.y); }

// 4-57. operator+= - 현재 Point 객체에 다른 Point 객체의 좌표를 더함.
    void operator+= (Point &p) { x += p.x, y += p.y; }

// 4-58. operator-= - 현재 Point 객체에서 다른 Point 객체의 좌표를 뺌.
    void operator-= (Point &p) { x -= p.x, y -= p.y; }
};