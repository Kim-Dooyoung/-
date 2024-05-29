#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 2-2
#define LEN_MIN 15 // 기차 길이
#define LEN_MAX 50
#define STM_MIN 0 // 마동석 체력
#define STM_MAX 5
#define PROB_MIN 10 // 확률
#define PROB_MAX 90
#define AGGRO_MIN 0 // 어그로 범위
#define AGGRO_MAX 5
// 마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0
// 좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2
// 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

// 2-1
int len_train, p, stmMadongseok;
int C, Z, M;
int turn;
int move_p, move_m;
int aggroC, aggroM;
int behaviorM;

void readyTrain();
void readyMadongseok();
void readyProbability();
void trainState();
void move();
void printState();
void outtro();
void printMadongseok();
void stateMadongseok();
void phasesBehaviorZ();
void phasesBehaviorM();

int main(void) {
    // 1-1 준비
    srand((unsigned)time(NULL)); // 난수 초기화

    printf("=======게임 시작=======\n"); // 인트로 작성

    // 유효한 값 입력받기
    readyTrain();
    readyMadongseok();
    readyProbability();

    C = len_train - 7; // 시민 위치
    Z = len_train - 4; // 좀비 위치
    M = len_train - 3; // 마동석 위치

    turn = 1; // 현재 턴

    trainState();

    // 프로그램 구성
    while (C > 2 && C + 1 != Z) {

        move_p = rand() % 100; // 난수 설정

        // First Phase 이동
        move();
        trainState(); // 열차 상태 출력
        printState(); // 시민 좀비 이동 현황 출력
        printMadongseok(); // 마동석 이동 입력받고 상태 출력

        // Second Phase 행동
        phasesBehaviorZ();


        // 게임오버 조건들 추가 break;
        turn++; // 턴 증가
    }

    outtro();

    return 0;
}

void readyTrain() {
    printf("train length(15~50)>> ");
    scanf_s("%d", &len_train); //기차 길이 입력받음
    if (len_train < LEN_MIN || len_train > LEN_MAX) {
        readyTrain();
    }
}

void readyMadongseok() {
    printf("madongseok stamina(0~5)>> ");
    scanf_s("%d", &stmMadongseok); //마동석 체력 입력받음
    if (stmMadongseok < STM_MIN || stmMadongseok > STM_MAX) {
        readyMadongseok();
    }
}

void readyProbability() {
    printf("percentile probability 'p' (10~90)>> ");
    scanf_s("%d", &p); //확률 입력받음
    if (p < PROB_MIN || p > PROB_MAX) {
        readyProbability();
    }
}

void trainState() {
    // 열차의 초기 상태 출력
    printf("\n");
    for (int i = 0; i < len_train; i++) printf("#");
    printf("\n#");
    for (int i = 0; i < len_train - 2; ++i) {
        if (i == C) printf("C"); // 시민 위치
        else if (i == Z) printf("Z"); // 좀비 위치
        else if (i == M) printf("M"); // 마동석 위치
        else printf(" "); // 공백
    }
    printf("#\n");
    for (int i = 0; i < len_train; i++) printf("#");
    printf("\n");
}

void move() {
    // 1-4 시민 이동 2-3 이동
    if (move_p < (100 - p)) {
        C--;
        if (aggroC < AGGRO_MAX) {
            aggroC++;
        }
    }
    else {
        if (aggroC > AGGRO_MIN) {
            aggroC--;
        }
    }

    // 1-5 좀비 이동
    if (turn % 2 == 1) { // 홀수 턴에만 이동
        // 2-3 이동
        // 마동석 붙들기 추가
        // 어그로 수치쪽으로 이동하는 것 추가
        if (M == Z + 1 && turn >= 2) {

        }
        else {
            if (aggroC >= aggroM) {
                    Z--;
            }
            else {
                Z++;
            }
        }
    }
}

void printState() {
    // 1-3 시민 상태 출력
    if (move_p < (100 - p)) {
        printf("\ncitizen: %d -> %d (aggro: %d)\n", C + 1, C, aggroC); // 시민이 이동할 경우
    }
    else {
        printf("\ncitizen does nothing.\n"); // 시민이 머무를 경우
    }

    // 1-3 좀비 상태 출력
    if (turn % 2 == 1) {
        if (aggroC >= aggroM) {
            printf("zombie: %d -> %d\n", Z + 1, Z); // 좀비가 시민 쪽으로 이동했을 경우
        }
        else if (aggroC < aggroM) {
            printf("zombie: %d -> %d\n", Z - 1, Z); // 좀비가 마동석 쪽으로 이동했을 경우
        }
    }
    else {
        printf("zombie: stay %d (cannot move)\n", Z); // 좀비가 짝수 턴일 경우
    }
}

void printMadongseok() {
    // 2-2 마동석 이동 입력 받음
    if (M == Z + 1) {
        printf("\nMadongseok move(%d:stay)\n", M);
    }
    else {
        printf("\nmadongseok move(0:stay, 1:left)>> ");
        scanf_s("%d", &move_m);
        if (move_m != 0 && move_m != 1) {
            printMadongseok();
            return;
        }
    }

    // 마동석  이동
    if (move_m == MOVE_LEFT) {
        M--;
        if (aggroM < AGGRO_MAX) {
            aggroM++;
        }
    }
    else if (move_m == MOVE_STAY) {
        if (aggroM > AGGRO_MIN) {
            aggroM--;
        }
    }
    else {
        if (aggroM > AGGRO_MIN) {
            aggroM--;
        }
    }

    // 2-2 마동석 이동 현황 출력
    if (move_m == MOVE_LEFT) {
        printf("\nmadongseok move %d -> %d (aggro: %d, stamina: %d)\n", M + 1, M, aggroM, stmMadongseok); // 마동석이 움직일 경우
    }
    else {
        printf("\nmadongseok: stay %d (aggro: %d, stamina: %d)\n", M, aggroM, stmMadongseok); // 마동석이 머무를 경우
    }
}

void phasesBehaviorZ() {
    if (C == Z + 1 && Z == M + 1) {
        if (aggroC > aggroM) {
            printf("GAME OVER! citizen dead..."); // 게임 종료
        }
        else if (aggroC <= aggroM) {
            stmMadongseok--;
        }
    }
    else if (C == Z + 1 && Z > M + 1) {
        printf("GAME OVER! citizen dead..."); // 게임 종료
    } else if (C > Z + 1 && Z == M + 1) {
        stmMadongseok--;
    }
}

void phasesBehaviorM() {
    if (Z != M + 1) {
        printf("madongseok action(0.rest, 1.provoke)>>");
        scanf_s("%d", &behaviorM);

        // 좀비와 인접하지 않은 경우
        // 휴식할 때
        if (behaviorM == ACTION_REST) {
            printf("modongseko rests...\n");
            if (aggroM > AGGRO_MIN) {
                aggroM--;
            }
            if (stmMadongseok < STM_MAX) {
                stmMadongseok++;
            }
            printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", M, aggroM + 1, aggroM, stmMadongseok - 1, stmMadongseok);
        }
        else if (behaviorM == ACTION_PROVOKE) {
            // 도발할 때
            printf("madongseok provoked zombie...\n");
            aggroM == AGGRO_MAX;
            printf("madongseok : %d (aggro: %d -> 5, stamina: %d\n", M, aggroM, stateMadongseok);
        }
    }
    else {
        printf("madongseok action(0.rest, 1.provoke, 2.pull)>>");
        scanf_s("%d", &behaviorM);


        // 좀비와 인접한 경우
        // 휴식할 때
        if (behaviorM == ACTION_REST) {
            printf("modongseko rests...\n");
            if (aggroM > AGGRO_MIN) {
                aggroM--;
            }
            if (stmMadongseok < STM_MAX) {
                stmMadongseok++;
            }
            printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", M, aggroM + 1, aggroM, stmMadongseok - 1, stmMadongseok);
        }
        else if (behaviorM == ACTION_PROVOKE) {
            // 도발할 때
            printf("madongseok provoked zombie...\n");
            aggroM == AGGRO_MAX;
            printf("madongseok : %d (aggro: %d -> 5, stamina: %d\n", M, aggroM, stateMadongseok);
        }
        else if (behaviorM == ACTION_PULL) {
            printf("madongseok pulled zombie... Next turn, it can't move");
            
        }

    }


    
}

void outtro() {
    // 아웃트로 작성
    if (C + 1 == Z) {
        printf("\nYOU WIN!...\n");
    }
    else {
        printf("GAME OVER");
    }
}
