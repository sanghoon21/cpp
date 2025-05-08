// 클래스 정의 부분
// Sample이라는 이름의 클래스
class Sample {
    // 멤버 변수
    char *name;  // 문자열(문자배열)을 가리키는 용도
                 // 실제로 메모리 할당 안되어있음
public:
    //2개의 생성자
    Sample(){ }   //기본 생성자.
    Sample(const char * name){ }  //
};
void main() {
    Sample a("sample");
    Sample b(a);
}