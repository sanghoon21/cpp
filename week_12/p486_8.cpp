#include <iostream>
using namespace std;

class Sample1 {
public:
    Sample1() { }
    void play() { cout << "1\ubc88 sample" << endl; }
};

class Sample2 : public Sample1 {
public:
    Sample2() { }
    void play() { cout << "2\ubc88 sample" << endl; }
};

class Sample3 : public Sample1 {
public:
    Sample3() { }
    void play() { cout << "3\ubc88 sample" << endl; }
};

class Sample4 : public Sample1 {
public:
    Sample4() { }
    void play() { cout << "4\ubc88 sample" << endl; }
};

void main() {
    Sample1* arr[4];
    Sample1* a = new Sample1();
    Sample2* b = new Sample2();
    Sample3* c = new Sample3();
    Sample4* d = new Sample4();

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;

    for (int i = 0; i < 4; i++) arr[i]->play();
} 


/*
(1) 이 프로그램의 출력 결과를 적어라.
1번 sample
1번 sample
1번 sample
1번 sample
=> 각 클래스마다 play() 함수가 모두 있지만 기본 클래스인 Sample1에서 play() 함수에 virtual 키워드를 붙이지 않았기 때문에, 자식 클래스가  play() 함수를 재정의하여도 다형성이 적용되지 않음.
배열 arr의 타입도 Sample1*이기에,컴파일 타임에서 Sample1의 play() 함수를 호출함.
 기본 클래스인 Sample1 클래스의 play() 함수만 호출되어 위와 같은 출력 결과가 나오게 됨. (정적 바인딩)
 문제(1) 같은 경우는 업캐스팅이 적용(부모->자식)되었지만, 동적바인딩이 안되었기에
1번 sample
1번 sample
1번 sample
1번 sample
이렇게 모두 똑같이 나오게 됨(p14와 비슷) (한 배열 안에 네모, 선, 동그라미를 다 집어넣기는 함)

(2) 6행의 play() 함수를 가상 함수로 수정한다면 어떤 결과가 출력될지 예상하라.
virtual 키워드를 붙였기 때문에, 자식 클래스인 Sample2, Sample3, Sample4 에서 play()함수 재정의가 가능하게 함.
이 때는 virtual을 이용한 동적 바인딩이 적용되어, 런타임에서 Sample 1, 2, 3, 4 중에서 어떤 play() 함수를 사용할 것인지 결정할 수 있게 되고, 결국 실제 객체의 타입에 따라 Sample2, Sample3, Sample4의 play() 함수가 각각 호출됨.

(3) 
원래 코드에서는 
Sample1* arr[4];
Sample1* a = new Sample1();
Sample2* b = new Sample2();
Sample3* c = new Sample3();
Sample4* d = new Sample4();

arr[0] = a;
arr[1] = b;
arr[2] = c;
arr[3] = d;

for (int i = 0; i < 4; i++) arr[i]->play();
부모 클래스로 찍어낸 포인터가 자식을 가리키는 업캐스팅이 3번 발생함. (1은 그냥 동일한 타입.)
b, c, d는 Sample2, 3, 4의 객체이지만, arr 배열은 Sample1*형 배열이므로 자식-> 부모 방향의 업캐스팅이 발생함.

그러나 배열이 Sample2* 형이라면?
Sample3, Sample4는 Sample1의 자식이지, Sample2의 자식이 아님(상속받지 x).
즉, Sample2*는 Sample3*, Sample4*를 가리킬 수 없음. 그러므로 업캐스팅이 성립되지 않는다.
업캐스팅은 부모 클래스로 찍어낸 포인터가 자식을 가리키는 것이기 때문에.
결국 컴파일 오류가 생기게 됨.
(또한 Sample1에 대해서도 Sample2* a = new Sample1(); 이런 식으로 자식이 부모를 가리키게 되어버리는 다운캐스팅이 발생하여 오류가 생긴다.)
동적 바인딩은 virtual 키워드가 있기에 가능하긴 하지만, 업캐스팅이 발생하지 못하는 것.
---------

---------

