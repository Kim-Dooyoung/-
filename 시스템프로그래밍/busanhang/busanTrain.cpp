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

void readyTrain();
void readyMadongseok();
void readyPerbability();
void trainState();
void move();
void printState();
void outtro();
void printMadongseok();
void StateMadongseok();
void phasesBehavior();

int main(void) {
    // 1-1 준비
    srand((unsigned)time(NULL)); // 난수 초기화

    printf("=======게임 시작=======\n"); // 인트로 작성

    // 유효한 값 입력받기
    readyTrain();
    readyMadongseok();
    readyPerbability();

    int C = len_train - 7; // 시민 위치
    int Z = len_train - 4; // 좀비 위치

    int turn = 1; // 현재 턴

    trainState();

    // 프로그램 구성
    while (C > 2 && C + 1 != Z) {

        int move_p = rand() % 100; // 난수 설정

        // One Phase turn
        move();
        trainState(); // 열차 상태 출력
        printState(); // 시민 좀비 이동 현황 출력
        printMadongseok(); // 마동석 이동 입력받음
        trainState(); // 열차 상태 출력(마동석 이동 반영)
        phasesBehavior();

        turn++; // 턴 증가
    }

    outtro();

    return 0;
}

void readyTrain() {
    scanf_s_s("train length(15~50) %d", &len_train); //기차 길이 입력받음
    if (len_train < 15 || len_train > 50) {
        readyTrain();
    }
}

void readyMadongseok() {
    scanf_s_s("madongseok stamina(0~5) %d", &stmMadongseok); //마동석 체력 입력받음
    if (stmMadongseok < 0 || stmMadongseok > 5) {
        readyMadongseok();
    }
}

void readyPerbability() {
    scanf_s_s("percentile probability 'p' (10~90) %d", &p); //확률 입력받음
    if (p < 10 || p > 90) {
        readyPerbability();
    }
}

void trainState() {
    // 열차의 초기 상태 출력
    printf("\n");
    for (int i = 0; i < len_train; i++) printf("#");
    printf("\n#");
    for (int i = 0; i < len_train - 3; ++i) {
        if (i == C) printf("C"); // 시민 위치
        else if (i == Z) printf("Z"); // 좀비 위치
        // 마동석 위치도 추가
        else printf(" "); // 공백
    }
    printf("M#\n");
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
        if (aggroC > AGGRO_MAX) {
            aggroC--;
        }
    }

    // 1-5 좀비 이동
    if (turn % 2 == 1 && move_p < p) { // 홀수 턴에만 이동
        // 2-3 이동
        // 마동석 붙들기 추가
        if (aggroC > aggroM) {
            Z--;
        }
        else if (aggroC < aggroM) {
            Z++;
        }
    }

}

void printState() {
    // 1-3 시민 상태 출력
    if (move_p < (100 - p)) {
        printf("citizen: %d -> %d (aggro: %d)\n", C + 1, C, aggroC); // 시민이 이동할 경우
    }
    else {
        printf("citizen does noting.\n"); // 시민이 머무를 경우
    }

    // 1-3 좀비 상태 출력
    if (turn % 2 == 1 && move_p < p) {
        printf("zombie: %d -> %d\n", Z + 1, Z); // 좀비가 이동했을 경우
    }
    else if (turn % 2 == 1 && move_p >= p) { // 좀비가 홀수 턴에서 머무를 경우
        printf("zombie: stay %d\n", Z);
    }
    else if (turn % 2 == 0) {
        printf("zombie: stay %d(cannot move)\n", Z); // 좀비가 짝수턴일 경우
    }

}

void printMadongseok() {
    // 2-2 마동석 이동 및 상태 출력
    printf("madongseok move(0:stay, 1:left)>>");
    scanf_s_s("%d", &move_m);
    if (move_m != 0 || move_m != 1) {
        printMadongseok();
    }

    // 2-3 마동석 어그로
    if (move_m == 0) {
        aggroM--;
    }
    else {
        aggroM++;
    }
}

void StateMadongseok() {
    if (move_p < (100 - p)) {
        printf("citizen: %d -> %d (aggro: %d)\n", C + 1, C, aggroM); // 시민이 이동할 경우
    }
    else {
        printf("madongseok: stay %d(aggro: %d, stamina:%d).\n", M, aggroM, stmMadongseok); // 시민이 머무를 경우
    }
}

void phasesBehavior() {
    // 시민
    // 좀비
    // 마동석
}

void outtro() {
    // 아웃트로 작성
    if (C + 1 == Z) {

    }
    else if (C == 2) {
        printf("\nYOU WIN!...\n");
    }
}