// 1. 파일 입출력에서 발생하는 예외 정보를 저장.
//  파일 입출력 오류가 발생했을 때, 어떤 파일에서 어떤 작업(읽기/쓰기) 중 오류가 발생했는지 구체적인 정보를 제공.

#pragma once
#include <string>

// 파일 입출력 예외를 처리하는 구조체
struct FileException 
{
    std::string filename; // 예외가 발생한 파일 이름
    bool bRead;           // 예외가 읽기 모드(true)인지 쓰기 모드(false)인지 나타냄
    FileException(std::string name, bool b) : filename(name), bRead(b) {}
};