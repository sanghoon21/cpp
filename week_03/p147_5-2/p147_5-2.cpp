#include "p147_5-2.h"

//playRussianRoulette()함수를 정의.
//러시안 룰렛 게임의 실제 동작 구현
void playRussianRoulette(int nTurns, int nBullets, int nChambers)
{
    //게임을 시작할 플레이어를 랜덤하게 선택
    int start = rand() % nTurns;   //0부터 nTurns-1 사이의 랜덤한 숫자를 선택
    int alivePlayers[nTurns];  //아직 살아있는 사람 추적하는 배열
    int aliveCount = nTurns;   //현재 살아있는 사람 수를 추적

    // 모든 플레이어를 살아있는 상태로 초기화
    for (int i = 0; i < nTurns; i++)
        alivePlayers[i] = 1;

    printf("\n총을 돌렸습니다. %d번부터 시작합니다.\n", start + 1);
        //1번부터 시작하는 형식으로 출력.
    //플레이어 번호는 0부터 시작하는데, 실제 출력에서는 1부터 시작하는 것처럼 보이도록 하기 위해.


    while (nBullets > 0 && aliveCount > 1) {  // 총알이 남아 있고, 1명 초과 생존 시 진행 (마지막1명 남으면 게임 종료)
        while (alivePlayers[start] == 0) {  // 탈락한 사람이면 건너뛰기
            start = (start + 1) % nTurns;
        }

        //rand() % nChambers: 탄창에서 "탄창개수만큼의" 칸들 중 한 곳을 무작위로 선택 (0~N번)
        int pos = rand() % nChambers;
        printf("[%d번]\t탄창을 무작위로 돌렸습니다.\n", start + 1);
        
        //사용자가 엔터 키를 누르면 총 발사
        printf("\t엔터를 누르면 격발됩니다...");
        getchar();  //사용자가 엔터 키를 누를 때까지 대기


    //pos: 랜덤으로 주어진 총의 슬롯 번호  (1번 슬롯 = 2번째 슬롯)
    //nBullets: 총알 갯수 (2개면 0,1 슬롯에 총알 있음)
    //총알 슬롯 번호가 0번 or 1번이면 총알이 들어있는 슬롯.
    //pos < nBullets 성립하고 총알 발사(죽음)
        if (pos < nBullets) {
            printf("\t빵~~~~~!!!\n");
            printf("-----> %d번 참가자가 총에 맞았습니다.\n", start + 1);
            alivePlayers[start] = 0;  // 해당 참가자 탈락
            aliveCount--;  // 생존자 수 감소
            nBullets--;  // 남은 총알 감소
        } else {
            printf("\t휴~~~ 살았습니다!!!\n");
        }


        //총알이 없는 경우 다음 플레이어로 이동 (다음 생존자 찾기)
        do {
            start = (start + 1) % nTurns;   //플레이어 번호를 순환 (2->3->1->2->3->1...)
        } while (alivePlayers[start] == 0);
    }

    //게임이 끝났다는 것
    //총알이 모두 소진됨 or 생존자가 1명망 남음
    printf("\n게임 종료! 모든 총알이 발사되었고, 남은 사람은 생존입니다!\n");
}
