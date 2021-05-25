// 프로그램에 필요한 헤더 파일
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// File name 등 전처리
#define DB_FILE "myDB.csv"
#define MAX_NAME_SIZE 255
#define MAX_AGE_SIZE 3
#define MAX_EMAIL_SIZE 255
#define ERROR_MALLOC 1
#define MAX_BUF_SIZE 514
#define TRUE 1
#define FALSE 0

#define MALLOC(p, s) \
if (!(p = malloc(s))) { \
    fprintf(stderr, "[Error] : MALLOC() error. exit code : 1\n"); \
    exit(ERROR_MALLOC); \
}

// 프로그램에 입력으로 사용될 이름, 나이, 이메일 구조체
typedef struct {
    char name[MAX_NAME_SIZE];
    char age[MAX_AGE_SIZE];
    char email[MAX_EMAIL_SIZE];
}Data;

Data * memDB  = NULL;
int capacity = 1;
int numOfData = 0;

// 사용된 함수 명세
void saveAry2File();
void printList();
void modifyMember();
void deleteMember();
void newMember();
void insertFile2Ary(char lineBuf[]);
void printMenu();
void createDB();
void insert(char lineBuf[]);
void doublingDB();
int checkEmailForm(char * str);

// 메인 함수
int main(void)
{
    // 파일포인터와 그 외에 사용된 변수 선언
    FILE * fp;
    int i, loop = TRUE, menu;
    char lineBuf[MAX_BUF_SIZE], * token, clearBuf, again;
    
    // 만약 파일을 읽어올 수 없는 경우에는 파일을 쓰기 모드로 열어 기존에 있는 두명의 정보를 입력한 후 파일을 닫음
    if (!(fp = fopen(DB_FILE, "r"))) {
        printf("First exection.\n");
        fp = fopen(DB_FILE, "w");
        fprintf(fp, "PARK GIL DONG,22,parkpark@hotmail.com\n");
        fprintf(fp, "LEE GIL DONG,23,gildonglee@naver.com\n");
        fclose(fp);
    }
    // createDB함수를 통해 동적할당을 시킴
    createDB();
    // 파일을 읽기 모드로 불러와서 파일에 있는 모든 정보들을 동적할당을 시킨 곳에 저장 후 파일을 닫음
    fp = fopen(DB_FILE, "r");
    while (fgets(lineBuf, MAX_BUF_SIZE, fp)) {
        insertFile2Ary(lineBuf);
    }
    fclose(fp);

    // while문을 통해 종료라는 명령이 오기전까지 무한루프
    while (loop)  {
        // printMenu()함수를 통해 기존의 메뉴들을 출력
        printMenu();
        // 사용자로부터 메뉴를 입력받음
        scanf("%d%c", &menu, &clearBuf);
        if (menu == 1) {                    // 입력받은 메뉴가 1번이라면 newMember()함수를 통해 새로운 사람의 정보를 입력받음
            do {                            // do ~ while 문을 사용해서 계속 입력받지 않을 경우에 탈출함
            newMember();
            printf("계속 입력 할까요? (Y/N) ");
            scanf("%c%c", &again, &clearBuf);
            } while (again == 'Y');
            printf("입력이 완료되었습니다.\n"); 
        } else if (menu == 2) {             // 입력받은 메뉴가 2번이라면 modifyMember()함수를 통해 기존의 사람의 정보를 수정
            modifyMember();
        } else if (menu == 3) {             // 입력받은 메뉴가 3번이라면 deleteMember()함수를 통해 기존의 사람의 정보를 삭제
            deleteMember();
        } else if (menu == 4) {             // 입력받은 메뉴가 4번이라면 printList()함수를 통해 기존의 사람의 정보를 모두 출력
            printList();                   
        } else if (menu == 5) {             // 입력받은 메뉴가 5번이라면 loop를 FALSE로 해주고 while문을 탈출
            printf("종료합니다.\n");
            loop = FALSE;
        } else {                            // 그외에 번호가 들어오게 되면 에러메시지 출력
            printf("잘못된 입력입니다.\n");
        }
    }

    // 동적할당을 한 포인터에 저장된 데이터를 파일에 옮김
    saveAry2File();

    // 동적할당 해제
    free(memDB);
    return 0;
}

// 메뉴들을 출력하는 함수
void printMenu()
{
    printf("1. 신규회원 저장\n2. 회원정보 수정\n3. 회원삭제\n4. 모든 회원 리스트\n5. 종료\n");
    printf("입력하세요 > ");
}

// 파일에 있던 정보들을 동적할당 받은 곳으로 저장하는 함수
void insertFile2Ary(char lineBuf[])
{
    char * token;

    // 만약 동적할당한 부분이 모자를 경우
    if (numOfData == capacity) doublingDB();
    // 파일에서 정보들이 ','를 기준으로 구분되어있기에 strtok를 사용해서 분리시킨 후 strncpy를 통해 token에 있는 정보를 각 name, age, email에 저장
    token = strtok(lineBuf, ",");
    strncpy(memDB[numOfData].name, token, MAX_NAME_SIZE);
    token = strtok(NULL, ",");
    strncpy(memDB[numOfData].age, token, MAX_AGE_SIZE);
    token = strtok(NULL, "\n");
    strncpy(memDB[numOfData].email, token, MAX_EMAIL_SIZE);
    // 위의 코드가 전부 실행되고 나면 사이즈를 늘려준다
    numOfData ++;
}

// 동적할당을 해주는 함수
void createDB()
{
    MALLOC(memDB, sizeof(*memDB));
}

// 동적할당을 한 곳이 모자를 경우 realloc을 통해 사이즈를 늘려줌
void doublingDB()
{
    capacity *= 2;
    memDB = (Data *)realloc(memDB, sizeof(*memDB) * capacity);
}

// 새로운 사람의 정보를 입력받는 함수
void newMember()
{
    int loop = TRUE;
    char str[MAX_EMAIL_SIZE];
    printf("이름 : ");
    fscanf(stdin, "%[^\n]s", memDB[numOfData].name);            // 띄어쓰기까지 포함된 문자열을 입력 받기위해 [^\n]을 포함
    getchar();
    printf("나이 : ");
    fscanf(stdin, "%[^\n]s", memDB[numOfData].age);
    getchar();
    while (loop) {                                              // 무한루프를 돌려 이메일의 양식이 맞지 않는 경우 다시 실행 
        printf("이메일 : ");
        fscanf(stdin, "%[^\n]s", memDB[numOfData].email);
        getchar();
        strcpy(str, memDB[numOfData].email);                    // 입력받은 이메일을 strcpy를 통해 str배열에  copy
        if (checkEmailForm(str) == TRUE) loop = FALSE;          // 만약 이메일의 양식에 맞을 경우 loop = FALSE를 통해 무한루프 탈출
        else printf("이메일 양식이 잘못되었습니다.\n");
    }
    numOfData ++;
}

// 기존의 사람 정보를 삭제하는 함수
void deleteMember()
{
    char delName[MAX_NAME_SIZE];
    int check = 0, pos;   
    printf("삭제할 사람 이름을 입력해주세요 : ");
    fgets(delName, MAX_NAME_SIZE, stdin);
    delName[strlen(delName) - 1] = '\0';                        // 문자열 마지막의 개행을 널값으로 초기화
    for (int i = 0 ; i < numOfData ; i ++) {                    // 삭제할 이름을 모든 데이터와 비교
        if (strcmp(delName, memDB[i].name) == 0) {
            check ++;
            pos = i;
        }   
    }
    if (check == 0) printf("사용자 %s 은(는) 없습니다.\n", delName);      // 데이터가 없는 경우
    else {                                                      // 삭제할 이름이 있는 경우 그 위치를 없애기 위해 뒤에 있는 데이터를 한칸씩 땡김
        for (int i = pos ; i < numOfData ; i ++) {
            memDB[i] = memDB[i + 1];
        }
        numOfData --;                                           // 데이터 하나가 빠졌기 때문에 데이터 사이즈를 줄여줌
    }
    printf("수정 완료 되었습니다.\n");
}

// 기존의 데이터를 수정하는 함수
void modifyMember()                     
{
    int check = 0, pos, loop = TRUE;
    char modName[MAX_NAME_SIZE], str[MAX_EMAIL_SIZE];
    printf("수정할 사람 이름을 입력해주세요 : ");
    fgets(modName, MAX_NAME_SIZE, stdin);
    modName[strlen(modName) - 1] = '\0';
    for (int i = 0 ; i < numOfData ; i ++) {                    // 위의 deleteMember()함수와 마찬가지로 수정할 사람이 있는 지 확인
        if (strcmp(modName, memDB[i].name) == 0) {
            check ++;
            pos = i;
        }   
    }
    if (check == 0) printf("사용자 %s 은(는) 없습니다.\n", modName);    // 없는 경우
    else {                                              // 수정할 사람이 있을 경우 이름과 나이, 이메일을 새로 받음
        printf("사용자 %s 을(를) 수정합니다.\n", modName);
        printf("이름 : ");
        scanf("%[^\n]s", memDB[pos].name);
        getchar();
        printf("나이 : ");
        scanf("%[^\n]s", memDB[pos].age);
        getchar();
        while (loop) {                                  // newMember()함수의 이메일 입력 방식과 동일
            printf("이메일 : ");
            scanf("%[^\n]s", memDB[pos].email);
            getchar();
            strcpy(str, memDB[pos].email);
            if (checkEmailForm(str) == TRUE) loop = FALSE;
            else printf("이메일 양식이 잘못되었습니다.\n");
        }
    }
    printf("수정 완료 되었습니다.\n");
}

// 모든 사람의 정보를 출력하는 함수
void printList()
{
    for (int i = 0 ; i < numOfData ; i ++) {
        printf("%s / %s / %s\n", memDB[i].name, memDB[i].age, memDB[i].email);
    }
}

// 동적할당을 받은 포인터에 있는 모든 정보를 파일에 쓰는 함수
void saveAry2File()
{
    FILE * fp;
    // fp를 읽기모드로 불러와 기존 데이터가 있으면 덮어씀
    fp = fopen(DB_FILE, "w");

    if (fp == NULL) {
        fprintf(stderr, "Cannot open %s file.\n", DB_FILE);
        exit(EXIT_FAILURE);
    }
    for (int i = 0 ; i < numOfData ; i ++) {
        fprintf(fp, "%s,%s,%s\n", memDB[i].name, memDB[i].age, memDB[i].email);
    }
    fclose(fp);
}

// 이메일의 양식을 확인하는 함수
int checkEmailForm(char * str)
{
    int i, checkPos1, checkPos2, cnt1 = 0, cnt2 = 0;

    // 파라미터로 받은 str에 저장된 문자열의 길이 만큼 반복문을 돌림
    // 만약 @, .인경우를 나누어 각각이 나온 횟수를 카운팅하고 @, .의 위치를 저장
    for (i = 0 ; i < strlen(str) ; i ++) {
        if (str[i] == '@') {
            checkPos1 = i; 
            cnt1 ++;
        }
        if (str[i] == '.') {
            checkPos2 = i; 
            cnt2 ++;
        }
    }
    // @, .이 나온 횟수가 각각 1이고 @의 위치가 .위치보다 앞에 있을 경우 참
    if ((checkPos1 < checkPos2) && cnt1 == 1 && cnt2 == 1) return TRUE;
    else return FALSE;
}
