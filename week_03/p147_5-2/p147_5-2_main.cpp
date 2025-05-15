#include "p147_5-2.h"
//3발 장전하면 3발 다 소진해야만 끝

int main()
{
  int nTurns, nBullets, nChambers;
  //rand()의 시드를 설정하여 실행할 때마다 다른 난수 생성
  srand((unsigned)time(NULL));  //현재 시간을 기반으로 시드를 설정

  printf("게임 인원 (예: 2) ==> ");
  scanf("%d", &nTurns);   //사용자가 입력한 게임 인원을 저장

  printf("탄창 개수 (예: 6) ==> ");
  scanf("%d", &nChambers);   //탄창 개수를 사용자로부터 입력받음

  printf("총알 개수 (전체 탄창 개수보다 작게 입력) ==> ");
  scanf("%d", &nBullets);  //사용자가 입력한 총알 개수를 저장

  getchar();  //scanf() 이후 남아 있는 개행 문자 제거

  //playRussianRoulette() 함수를 호출하여 게임 실행
  playRussianRoulette(nTurns, nBullets, nChambers);

  return 0;
}
