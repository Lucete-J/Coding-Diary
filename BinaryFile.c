#include <stdio.h>
#include <stdlib.h>

// 전처리를 통한 파일 이름 선언
#define BIN_FILE "binary.bin"
#define TRUE 1
#define FALSE 0
#define MAX_ID_SIZE 255
#define MAX_HP_SIZE 255
#define MAX_AGE_SIZE 127
#define MAX_FRIEND_SIZE 255

// 플레이어의 정보를 담는 구조체
typedef struct {
    char id[MAX_ID_SIZE];
    char age[MAX_AGE_SIZE];
    char hp[MAX_HP_SIZE];
    double xpos, ypos;
    int cnt;
    char friend[MAX_FRIEND_SIZE][MAX_ID_SIZE];
}PlayType;

void initSize(PlayType * p);
void printMenu();
void printInfo(PlayType * p);
void enterInfo(PlayType * p);
void calNumOfFriend(PlayType * p);

// 메인함수
int main(void)
{   
    int loop = TRUE, menu;
    PlayType myCharacter;

    // 구조체 변수 초기화
    initSize(&myCharacter);
    // while문을 통한 무한루프
    while (loop) {
        printMenu();
        scanf("%d", &menu);         // 사용자로 부터 메뉴를 입력
        switch (menu) {
            case 1 :                // menu가 1인 경우 
                enterInfo(&myCharacter);
                break;
            case 2 :                // menu가 2인 경우
                printInfo(&myCharacter);
                break;  
            case 3 :                // menu가 3인 경우
                printf("종료되었습니다.\n");
                loop = FALSE;
        }
    }

    return 0;
}

// 동맹의 수를 계산하는 함수
void calNumOfFriend(PlayType * p)
{   
    // BIN_FILE을 rb모드로 염
    FILE * fp = fopen(BIN_FILE, "rb");
    // 파일 포인터를 파일의 끝에서부터 4바이트 앞으로 이동
    fseek(fp, -4L, SEEK_END);
    // 파일에서 4바이트 만큼 읽어서 p->cnt에 저장
    fread(&p->cnt, sizeof(int), 1, fp);
    // 파일을 닫음
    fclose(fp);
}

// 구조체를 초기화하는 함수
void initSize(PlayType * p)
{
    p->id[0] = '\0';
    p->age[0] = '\0';
    p->hp[0] = '\0';
    p->xpos = 0;
    p->ypos = 0;
    p->friend[0][0] = '\0';
    p->cnt = 0;
}

// 메뉴를 출력하는 함수
void printMenu()
{
    printf("1. 플레이어 정보 기록\n2. 플레이어 정보확인\n3. 종료\n");
    printf("입력하세요> ");
}

// 파일에 저장된 정보를 출력하는 함수
void printInfo(PlayType * p)
{
    FILE * fp = fopen(BIN_FILE, "rb");

    int i;

    // 동맹의 수를 계산을 먼저 함
    calNumOfFriend(p);

    // 파일의 첫부분으로 포인터를 이동
    fseek(fp, 0, SEEK_SET);
    // MAX_ID_SIZE만큼 p->id에 저장
    fread(p->id, MAX_ID_SIZE, 1, fp);
    // p->id를 출력
    printf("ID : %s / ", p->id);

    // MAX_AGE_SIZE만큼 p->age에 저장
    fread(p->age, MAX_AGE_SIZE, 1, fp);
    // p->age를 출력
    printf("나이 : %s / ", p->age);

    // MAX_HP_SIZE만큼 p->hp에 저장
    fread(p->hp, MAX_HP_SIZE, 1, fp);
    // p->hp를 저장
    printf("HP : %s / ", p->hp);

    // p->xpos. p->ypos에 double사이즈 만큼 각각 읽어드림
    fread(&p->xpos, sizeof(double), 1, fp);
    fread(&p->ypos, sizeof(double), 1, fp);
    // p->xpos. p->ypos 출력
    printf("좌표 : %.3lf %.3lf\n", p->xpos, p->ypos);

    // 처음에 calNumOfFriend()함수로 받아드린 동맹의 수를 출력
    printf("등록된 동맹 수 : %d 명\n", p->cnt);
    
    // 만약 동맹의 수가 1명이면 / <- 없어야 함으로 출력을 구분
    if (p->cnt == 1) {
        fread(p->friend[p->cnt - 1], MAX_ID_SIZE, 1, fp);
        printf("%s\n", p->friend[p->cnt - 1]);
    } else {
        // for문을 통해 동맹의 수만큼 MAX_ID_SIZE만큼 p->friend[]에 저장하고 출력
        for (i = 0 ; i < p->cnt - 1; i ++) {
            fread(p->friend[i], MAX_ID_SIZE, 1, fp);
            printf("%s / ", p->friend[i]);
        }
        fread(p->friend[p->cnt - 1], MAX_ID_SIZE, 1, fp);
        printf("%s\n", p->friend[p->cnt - 1]);
    }   
    printf("완료되었습니다.\n");
}

// 정보를 입력하는 함수
void enterInfo(PlayType * p)
{
    char again = 'Y';
    int cnt = 0;
    // 파일을 wb모드로 염
    FILE * fp = fopen(BIN_FILE, "wb");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open %s file.\n", BIN_FILE);
        exit(1);
    }
    // 정보들을 사용자로부터 입력받고 파일에 쓰는 과정
    printf("ID를 입략하세요 : ");
    scanf("%s", p->id);
    fwrite(p->id, sizeof(char), MAX_ID_SIZE, fp);
    printf("나이를 입력하세요 : ");
    scanf("%s", p->age);
    fwrite(p->age, sizeof(char), MAX_AGE_SIZE, fp);
    printf("HP를 입력하세요 : ");
    scanf("%s", p->hp);
    fwrite(p->hp, sizeof(char), MAX_HP_SIZE, fp);
    printf("X 좌표를 입력하세요 : ");
    scanf("%lf", &p->xpos);
    fwrite(&p->xpos, sizeof(double), 1, fp);
    printf("Y 좌표를 입력하세요 : ");
    scanf("%lf", &p->ypos);
    fwrite(&p->ypos, sizeof(double), 1, fp);
    while (again == 'Y') {
       printf("동맹 ID를 입력하세요 : ");
       scanf("%s", p->friend[cnt]); 
       fwrite(p->friend[cnt], sizeof(char), MAX_ID_SIZE, fp);
       getchar();
       printf("동맹을 계속 추가할까요? : ");
       scanf("%c", &again);
       getchar();
       cnt ++;
    }
    p->cnt = cnt;
    fwrite(&p->cnt, sizeof(int), 1, fp);

    printf("완료되었습니다.\n");
    fclose(fp);
}
