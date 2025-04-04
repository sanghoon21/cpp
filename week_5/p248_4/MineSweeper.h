#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

extern void playMineSweeper();

// extern 명령어를 통해 다른 파일에서 해당 함수를 호출 가능하도록 함.
// 다른 파일에서 해당 헤더 파일을 포함시킨다면, 함수 호출시 따로 extern을 명시할 필요 X