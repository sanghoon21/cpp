// 게임의 기능들이 포함된 핵심 소스 파일 (핵심 게임 로직)

#include "MineSweeper.h"

#define MAX_WIDTH  80
#define MAX_HEIGHT 40

enum LabelType { Empty = 0, Bomb = 9 };
enum MaskType { Hide = 0, Open, Flag };

	//전역변수에 static 더해서 공간적인 제한을 두었음
static int MineMapMask[MAX_HEIGHT][MAX_WIDTH];   // 숨김, 열림, 깃발
static int MineMapLabel[MAX_HEIGHT][MAX_WIDTH];  // 0~8, 9(지뢰)
static int nx, ny, nBomb;  // 현재 맵 크기 및 지뢰 개수

inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); }
inline bool isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }
inline bool isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }


// 6. 빈 칸(0)이면 주변도 자동으로 파짐
static void dig(int x, int y) {
    if (isValid(x, y) && mask(x, y) != Open) {
        mask(x, y) = Open;
        if (label(x, y) == 0) {
            for (int dy = -1; dy <= 1; dy++)
                for (int dx = -1; dx <= 1; dx++)
                    if (dx || dy) dig(x + dx, y + dy);
        }
    }
}
  //깃발
static void mark(int x, int y) {
    if (isValid(x, y) && mask(x, y) == Hide)
        mask(x, y) = Flag;
}


static int getBombCount() {
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (mask(x, y) == Flag) count++;
    return count;
}


// 4. 터미널 화면을 clear 후 맵 형태를 출력
static void print() {                    
    system("clear");  // Linux, macOS에서는 "clear", Windows에서는 "cls"
    
    // 상단 열 번호 출력
    printf("    ");
    for (int x = 0; x < nx; x++)
        printf(" %2d ", x + 1);
    printf("\n");

    // 윗줄 테두리
    printf("   ┌");
    for (int x = 0; x < nx - 1; x++)
        printf("───┬");
    printf("───┐\n");

    // 보드 출력
    for (int y = 0; y < ny; y++) {
        printf("%2d │", y + 1);  // 왼쪽 행 번호
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) == Hide)        printf(" ■ │");  // 숨겨진 칸
            else if (mask(x, y) == Flag)   printf(" ⚑ │");  // 깃발
            else if (isBomb(x, y))         printf(" * │");  // 지뢰
            else if (label(x, y) == 0)     printf("   │");  // 빈 칸
            else                           printf(" %d │", label(x, y));  // 숫자
        }
        printf("\n");

        // 가로 구분선
        if (y < ny - 1) {
            printf("   ├");
            for (int x = 0; x < nx - 1; x++)
                printf("───┼");
            printf("───┤\n");
        }
    }

    // 아랫줄 테두리
    printf("   └");
    for (int x = 0; x < nx - 1; x++)
        printf("───┴");
    printf("───┘\n");
}


// 해당 칸 주위에 몇 개의 지뢰가 있는지 세는 역할 (지뢰찾기 숫자 1,2,3.. 담당)
static int countNbrBombs(int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++)
        for (int dx = -1; dx <= 1; dx++)
            if (isValid(x + dx, y + dy) && label(x + dx, y + dy) == Bomb)
                count++;
    return count;
}


// 3. 맵 구성요소 결정
static void init() {
    srand((unsigned int)time(NULL));  //게임 실행시마다 다른 위치에 지뢰 배치

	//모든 칸을 숨김 상태로 설정
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            mask(x, y) = Hide;    //모든 칸을 숨김 상태로 설정
            label(x, y) = Empty;  //빈칸으로 초기화
        }
	// 랜덤으로 nBomb 개수만큼 지뢰 배치
    for (int i = 0; i < nBomb; i++) {
        int x, y;
        do {
            x = rand() % nx;
            y = rand() % ny;
        } while (label(x, y) != Empty);
        label(x, y) = Bomb;
    }
	// 빈칸인 곳에는 주변 지뢰 개수 계산 후 저장
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (label(x, y) == Empty)
                label(x, y) = countNbrBombs(x, y);
}


// 5. 입력 형식이 "열 행 enter" 또는 "p 열 행 enter"
static bool getPos(int& x, int& y, bool& isFlag) {
    char input[10];
    printf("\n입력 (열 행 또는 P 열 행) --> ");
    fgets(input, sizeof(input), stdin);

    if (tolower(input[0]) == 'p') {
        isFlag = true;
        sscanf(input + 1, "%d %d", &x, &y);
    } else {
        isFlag = false;
        sscanf(input, "%d %d", &x, &y);
    }

    x--; y--;  // 입력된 값(1~N)을 배열 인덱스(0~N-1)로 변환
    return isValid(x, y);
}


// 7. 게임 종료 조건 확인
// 지뢰를 밟으면 게임 종료 (-1 반환)
// 모든 안전한 칸을 열면 게임 클리어 (1 반환)
static int checkDone() {
    int covered = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) != Open) covered++;
            else if (isBomb(x, y)) return -1;
        }
    return (covered == nBomb) ? 1 : 0;
	//닫힌 칸 개수 = 남은 지뢰 수 같으면 승리 (1 반환), 아직 '닫힌칸 > 폭탄개수'라면 계속 진행 (0 반환)
}


// 2. 실행 (게임 루프 시작)
void playMineSweeper() {
    printf("지뢰찾기 게임 시작!\n");
    do {
        printf("맵 크기 입력 (가로 세로, 최대 80x40): ");
        scanf("%d %d", &nx, &ny);
        getchar();
    } while (nx < 1 || nx > MAX_WIDTH || ny < 1 || ny > MAX_HEIGHT);  //80*40 초과하면 다시 입력

    do {
        printf("지뢰 개수 입력: ");
        scanf("%d", &nBomb);  //nBomb = 지뢰 개수
        getchar();
    } while (nBomb < 1 || nBomb >= nx * ny);

    init();
    int status;
    do {
        // 현재 맵을 터미널에 출력 -> 4
		print();  
        
		// 사용자 입력 받기 -> 5
		int x, y;   
        bool isFlag;  //깃발
        if (!getPos(x, y, isFlag)) continue;
		
		// 깃발 입력시(p) mark(x,y); 실행
		// 일반 입력시 dig(x,y); 실행 -> 6
        if (isFlag) mark(x, y);
        else dig(x, y);

		// 게임 종료 조건 확인 -> 7
        status = checkDone(); //checkDone 함수 실행 후 결과값을 status에 넣음
    } while (status == 0);  
	// status는 playMineSweeper 함수의 지역 변수이기에,
	// {}에서 나와도 do-while 반복문 실행동안 값 유지됨

    print();
    if (status < 0) printf("\n게임 오버! 지뢰를 밟았습니다.\n\n");
    else printf("\n축하합니다! 모든 안전한 칸을 찾았습니다.\n\n");
}
