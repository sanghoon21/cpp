#include "p147_5-1.h"

//playRussianRoulette()함수를 정의.
//러시안 룰렛 게임의 실제 동작 구현
int playRussianRoulette(int nTurns, int nBullets, int nChambers)
{
    //게임을 시작할 플레이어를 랜덤하게 선택
    int start = rand() % nTurns;   //0부터 nTurns-1 사이의 랜덤한 숫자를 선택
    printf("\n총을 돌렸습니다. %d번부터 시작합니다.\n", start + 1);
        //1번부터 시작하는 형식으로 출력.
    //플레이어 번호는 0부터 시작하는데, 실제 출력에서는 1부터 시작하는 것처럼 보이도록 하기 위해.

    //러시안 룰렛 게임 진행(무한 루프)
    while (true) {
        
        //rand() % nChambers: 탄창에서 "탄창개수만큼의" 칸들 중 한 곳을 무작위로 선택 (0~N번)
        int pos = rand() % nChambers;
        printf("[%d번]\t탄창을 무작위로 돌렸습니다.\n", start + 1);
        
        //사용자가 엔터 키를 누르면 총 발사
        printf("\t엔터를 누르면 격발됩니다...");
        getchar();  //사용자가 엔터 키를 누를 때까지 대기

        if (pos < nBullets) break;   //총알이 있는 칸이면 게임 종료.
            //pos: 랜덤으로 주어진 총의 슬롯 번호  (1번 슬롯 = 2번째 슬롯)
            //nBullets: 총알 갯수 (2개면 0,1 슬롯에 총알 있음)
            //총알 슬롯 번호가 0번 or 1번이면 총알이 들어있는 슬롯.
            //pos < nBullets 성립하고 게임 종료.(죽음)


        //총알이 없는 경우 다음 플레이어로 이동
        printf("\t휴~~~ 살았습니다!!!\n");
        start = (start + 1) % nTurns;   //플레이어 번호를 순환 (2->3->1->2->3->1...)
    }
    
    //게임이 종료되면 최종 출력
    printf("\t빵~~~~~!!!\n");
    return start+1;  //총에 맞은 플레이어 번호 반환
}
