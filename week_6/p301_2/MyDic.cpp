// MyDic 클래스 구현 (add, print, store 등)


#include "MyDic.h"
#include <iostream>
#include <fstream>

using namespace std;

// 1. 자동으로 MyDic의 생성자(MyDic::MyDic()) 호출 → nWords = 0으로 초기화됨
MyDic::MyDic() {
    nWords = 0;
}

// 2. 단어 직접 추가
void MyDic::add(string eng, string kor) {
    if (nWords < MAXWORDS) {
        words[nWords].eng = eng;  // 각 단어가 내부 배열 words[]에 저장됨
        words[nWords].kor = kor;  //WordPair 구조체의 객체인 words 배열, 
                                  //WordPair 구조체의 요소인 eng, kor
        nWords++;   // 단어수 1씩 증가
    }
}


// 3. 단어장 로드 함수 (불러오기)
// 파일로부터 단어를 읽어 add()로 등록
void MyDic::load(string filename) {
    ifstream fin(filename);
    nWords = 0;

    string eng, kor;
    while (fin >> eng >> kor) {
        add(eng, kor);
    }
    fin.close();

    cout << nWords << "개의 단어를 로드했습니다." << endl;
}


// 4. 단어장 저장 함수
// 단어들을 한 줄씩 파일에 저장 (저장 형태: 영어 한글설명)
void MyDic::store(string filename) {
    ofstream fout(filename);
    for (int i = 0; i < nWords; i++) {
        fout << words[i].eng << " " << words[i].kor << endl;
    }
    fout.close();

    cout << nWords << "개의 단어를 저장했습니다." << endl;
}


// 5. 단어장 출력 함수
// 사용자에게 현재 등록된 단어를 시각적으로 보여줌
// words[] 배열을 순회하면서 단어 목록을 출력
void MyDic::print() {
    for (int i = 0; i < nWords; i++) {
        cout << i + 1 << ". " << words[i].eng << " - " << words[i].kor << endl;
    }
}


// 6. 단어 조회 함수
// 배열의 인덱스를 이용해 특정 단어 조회
// dic2.getEng(1) => 2번째 단어인 banana - 바나나 출력
string MyDic::getEng(int id) {
    if (id >= 0 && id < nWords) return words[id].eng;
    return "";
}

string MyDic::getKor(int id) {
    if (id >= 0 && id < nWords) return words[id].kor;
    return "";
}
