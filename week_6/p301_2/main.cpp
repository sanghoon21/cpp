// 프로그램 실행의 시작점. 클래스 사용 예시
// main()
//  ├─ dic.add(...) × 3           → 단어 등록
//  ├─ dic.print()                → 등록 단어 화면 출력
//  ├─ dic.store("dic.txt")       → 파일로 저장
//  ├─ MyDic dic2                 → 새 단어장 객체 생성
//  ├─ dic2.load("dic.txt")       → 파일에서 단어 읽기
//  ├─ dic2.print()               → 읽은 단어 화면 출력
//  └─ dic2.getEng(1), getKor(1)  → 단어 1개 조회

#include <iostream>
#include "MyDic.h"

using namespace std;

int main() {
// 1. 단어장 클래스 MyDic의 객체 dic 생성
    MyDic dic;
// 2. 단어 추가
    cout << "== 단어 등록 ==" << endl;
    dic.add("apple", "사과");   //MyDic 클래스의 객체인 dic, MyDic 클래스의 요소인 add()
    dic.add("banana", "바나나");
    dic.add("computer", "컴퓨터");
// 3. 추가된 단어 목록 출력
    cout << "\n[추가된 단어 목록]" << endl;
    dic.print();
// 4. 모든 단어가 dic.txt 파일에 저장됨 (한 줄당 단어쌍 하나)
    cout << "\n== 단어장을 파일에 저장 (dic.txt) ==" << endl;
    dic.store("dic.txt");
// 5. 새 객체로 단어 파일 불러오기
    cout << "\n== 새로운 객체로 파일에서 읽기 ==" << endl;
    MyDic dic2;
    dic2.load("dic.txt");
// 6. 불러온 단어 목록 출력
// 파일에서 읽은 단어들이 잘 반영되었는지 확인
    cout << "[파일에서 불러온 단어 목록]" << endl;
    dic2.print();
// 7. 단어 조회  (배열의 인덱스 기반)
    cout << "\n== 인덱스로 단어 조회 ==" << endl;
    int idx = 1;
    cout << idx + 1 << "번째 단어: " 
         << dic2.getEng(idx) << " - " 
         << dic2.getKor(idx) << endl;

    return 0;
}


