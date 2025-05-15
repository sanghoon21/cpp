+---------------------+
|      MyTime         |
+---------------------+
| - hour : int        |
| - min  : int        |
| - sec  : int        |
| - msec : int        |
+---------------------+
| + MyTime()          |
| + void convert(d)   |
| + void print()      |
| + MyTime add(t)     |
| + void reset()      |
| + void read()       |
+---------------------+

+ : public 멤버

- : private 멤버



- 함수 변경 이유

  기능              구조체 기반 일반 함수                          클래스 기반 멤버 함수                                  변경 이유
시간변환      MyTime convertTime(double duration)	  -> void convert(double duration)	        클래스 내부 상태를 직접 수정하므로 반환 필요 없음
출력         void printTime(MyTime duration)	     -> void print()	                       클래스 내부 값만 출력하므로 매개변수 불필요
시간 덧셈     MyTime addTime(MyTime t1, MyTime t2)    -> MyTime add(MyTime t)	                객체 자신(this)에 다른 객체를 더하는 방식이 자연스럽고 직관적 (두 개 받을 필요 X)
초기화        void resetTime(MyTime *t)	              -> void reset()	                        자기 자신 초기화에 포인터 필요 없음
사용자        입력(없었음)	                            -> void read()	                          클래스 내부 값 직접 설정이므로 반환 불필요

=>캡슐화: 클래스 내부 상태(hour, min 등)를 외부 함수가 직접 조작하지 않도록 멤버 함수로 관리.
=>자기 자신(this) 활용: 구조체 기반 함수는 항상 MyTime을 전달받아야 했지만, 클래스는 자신의 데이터에 직접 접근할 수 있음.

MyTime convertTime(double duration);  // 값을 받아서 새로 만든 MyTime 돌려줌
void convert(double duration);  // 내 요소(hour, min, ...)를 직접 바꿈
-> 클래스 안에 값이 있으니까, 돌려줄 필요가 없음. 그냥 자기 자신 값을 바꾸면 끝
   이미 클래스 안에서 선언된 변수인 hour, min 등에 값 대입 후 이를 그대로 출력만 함. print()
   print(time 1)과 같이 값을 받지 않음

void printTime(MyTime t);  // 출력할 MyTime을 받아야 했음
void print();  // 내 값만 출력하면 됨
-> 클래스 안에 값이 있으니까, 외부에서 전달받지 않아도 됨.

