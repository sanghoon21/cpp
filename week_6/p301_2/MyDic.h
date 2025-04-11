// 단어장 클래스 선언 (MyDic)


#ifndef MYDIC_H
#define MYDIC_H

#include "WordPair.h"
#include <string>

const int MAXWORDS = 100;

class MyDic {
    WordPair words[MAXWORDS];  // 단어 저장 배열
    int nWords;                // 현재 단어 수

public:
    MyDic();  // 생성자

    void add(string eng, string kor);         // 단어 추가
    void load(string filename);               // 파일에서 불러오기
    void store(string filename);              // 파일에 저장
    void print();                             // 단어장 출력
    string getEng(int id);                    // 영어 단어 반환
    string getKor(int id);                    // 한글 설명 반환
};

#endif
