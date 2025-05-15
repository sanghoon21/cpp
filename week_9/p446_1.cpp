//! 0-1. 2D 평면에서 점(Point)과 사각형(Rectangle)을 나타내는 클래스를 정의
//!    점이나 사각형의 정보를 출력하는 코드.

#include <iostream>


//! 0-2. Point 클래스: 특정 좌표 (x, y)에 점을 그리라는 메시지를 출력.
class Point 
{
protected:
    //! 1-1. 멤버 변수: 점의 좌표 저장, protected로 선언되어 파생 클래스에 접근 가능
    int x, y;

public:
    //! 1-2. 생성자: 멤버 초기화 리스트를 사용하여 x, y를 초기화함.
    Point(int xx, int yy) : x(xx), y(yy) { }

    //! 1-3. 멤버 함수: 점의 좌표 출력, virtual로 선언되어 파생 클래스에서 재정의 가능
    virtual void draw()  // virtual 추가
    {
        std::cout << x << "," << y << "에 점을 그려라.\n";
    }
};
    //* 기본 클래스의 함수를 재정의 가능하게 하려면 반 드 시 virtual 키워드를 붙여야 함.***
    //* virtual이 없으면 파생 클래스에서 해당 함수를 재정의하더라도 다형성이 적용되지 않음.
    //* (즉, 기본 클래스의 함수가 호출됨).
    //* virtual을 붙이면 해당 함수를 가상함수로 만들어줌(선언해줌). -> 자식 클래스에서 재정의가 가능하게 함.




// (1) Rectangle 클래스 정의
//     public 상속을 사용하여 point의 protected 멤버 (x,y)에 접근.
//! 0-3. Rectangle 클래스: Point를 상속받아 좌표 (x, y)에 가로(width)와 세로(height)를 가지는 사각형을 그리라는 메시지를 출력.
class Rectangle : public Point 
{
protected:
    //! 1-4. 멤버 변수: 사각형의 가로, 세로의 길이를 저장, 파생 클래스에서 접근 가능
    int width, height;



public:
    //! 1-5. 생성자: Point의 생성자를 호출하여 x, y를 초기화함, width와 height를 초기화.
    // (2) 생성자 정의 (멤버 초기화 리스트 사용)
    Rectangle(int xx, int yy, int w, int h) : Point(xx, yy), width(w), height(h) { }
                                  // 기본 클래스 Point의 생성자 Point(int xx, int yy)를 호출.
    //! 1-6. 멤버함수: Point의 draw()를 재정의하여 사각형의 좌표와 크기를 출력, override 키워드로 재정의 표시.
    // (3) draw() 함수 재정의
    void draw() override 
    {
        std::cout << x << "," << y << "에 가로 " << width << " 세로 " << height << "인 사각형을 그려라.\n";
    }
};
    //* 자식 클래스에서 부모 클래스의 (가상)함수를 재정의할 때 사용됨
    
    // (4) protected를 private로 바꾸면
    // Point 클래스의 x, y 멤버가 private이 되어 Rectangle 클래스에서 직접 접근할 수 없게 됨.
    // 따라서 Rectangle 클래스의 draw() 함수에서 x, y를 사용할 때 컴파일 에러가 발생함.
    // 이를 해결하려면 Point 클래스에 x, y를 반환하는 public getter 함수를 추가하거나,
    // protected로 유지해야 자식 클래스인 Rectangle에서 x, y에 접근할 수 있음.


int main()
{
    Point p(1, 2); //생성자에 1, 2를 인수로 전달
    Rectangle r(2, 3, 100, 200);  // 생성자에 2, 3, 100, 200을 인수로 전달

    p.draw(); // "1,2에 점을 그려라."
    r.draw(); // "2,3에 가로 100 세로 200인 사각형을 그려라."

    return 0;
}