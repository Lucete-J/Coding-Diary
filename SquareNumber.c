#include <stdio.h>

// Main function
int main(int argc, char * argv[])
{
    int i, j, total, start, end, range;         // 프로그램을 실행하기 위해 필요한 변수 선언 (i = row, j = col)

    // Range 변수는 argv로부터 ASCII코드값을 받아 - '0'을 한 뒤 저장. 쉽게 말해 입력된 숫자
    range = *argv[1] - '0';
    // Total 변수는 출력을 해서 1행부터 range행까지의 index의 갯수 (공백 제외)
    total = 4 * (range - 1);

    // Total이 9보다 작을경우 (1, 2, 3)
    if (total < 9) {
        start = total;                                  // Start -> 각 행의 첫번째 인덱스를 가리킴
        if (range != 9) end = range + 1;                // End -> i = 각 행의 마지막 인덱스를 가리킴
        else end = 1;   
    } else if (total > 9 && total < 18) {               // Total이 9보다 크고 18보다 작을경우 (4, 5)
        start = total - 9;                              // Total에서 9를 빼줌. (문제에서 규칙을 찾으면 됨)
        if (range != 9) end = range + 1;                // range가 9가 아니면 마지막 인덱스는 range + 1
        else end = 1;
    } else if (total - 18 && total < 27) {              // Total이 18보다 크고 27보다 작을경우 (6, 7)
        start = total - 18;                             // Total에서 18를 빼줌. (문제에서 규칙을 찾으면 됨)
        if (range != 9) end = range + 1;
        else end = 1;
    } else if (total> 27 && total < 36) {               // Total이 27보다 크고 36보다 작을경우 (8, 9)
        start = total - 27;                             // Total에서 27를 빼줌. (문제에서 규칙을 찾으면 됨)
        if (range != 9) end = range + 1;
        else end = 1;
    }

    // for loop (i = row, j = col)
    for (i = 1 ; i <= range ; i ++) {
        for (j = 1 ; j <= range ; j ++) {
            if (i > 1 && i < range) {                   // i가 1행과 마지막행이 아니면 if문 실행
                if (j == 1) {                           // j가 1열일 경우 
                    printf("%d ", start);               
                    if (start == 1) start = 9;          // start가 1이면 다음에 0이 될 수 없으므로 9로 초기화
                    else start --;
                } else if (j == range) {                // j가 마지막 열일 경우
                    printf("%d ", end);                 
                    if (end == 9) end = 1;              // end가 9이면 다음에 10이 될 수 없으므로 9로 초기화
                    else end ++;                        
                } else {                                // j가 1열과 마지막열이 아니라면 공백 출력
                    printf("  ");
                }
            } else if (i == 1) {                        // 1행일 경우 그대로 오름차순 출력
                printf("%d ", j);
            } else if (i == range) {                    // 마지막행일 경우 start가 1열부터 내림차순으로 출력되다가 1이 출력된 뒤 9를 출력해야함을 9로 초기화
                if (start != 0) {
                    printf("%d ", start --);
                } else {                                
                    start = 9;
                    printf("%d ", start --);
                }
            }
        }
        printf("\n");
    }

    return 0;
}
