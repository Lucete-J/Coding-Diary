// 1-dimension

#include <stdio.h>
#define ARY_SIZE 3

int main(void)
{   
    int i;
    int ary[ARY_SIZE] = {8, 2, 8};
    int * p = ary;

    puts("Output of ary\n");
    for(i = 0 ; i < ARY_SIZE ; i ++)
        printf("%d ", ary[i]);

    puts("\n");
    puts("Output of p\n");
    for(i = 0 ; i < ARY_SIZE ; i ++)
        printf("%d ", *(p + i));

    return 0;
}

// 2-dimension

#include <stdio.h>

int main(void)
{
    int i, j;
    int ary[2][3] = {4, 2, 3, 5, 2, 3};
    int * p = &ary[0][0];

    puts("Output of ary\n");
    for (i = 0 ; i < 2 ; i ++) {
        for (j = 0 ; j < 3 ; j ++)
            printf("%d ", ary[i][j]);
        printf("\n");
    }

    puts("Output of p\n");
    for (i = 0 ; i < 2 ; i ++) {
        for (j = 0 ; j < 3 ; j ++)
            printf("%d ", *(p + 3 * i + j));
        printf("\n");
    }
    return 0;
}

// 3-dimension

#include <stdio.h>

int main(void)
{
    int ary[2][2][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int * p = &ary[0][0][0];
    int i, j, k;

    printf("Output of ary\n");
    for (i = 0 ; i < 2 ; i ++){
        for (j = 0 ; j < 2 ; j ++){
            for (k = 0 ; k < 3 ; k ++) {
                printf("%d ", ary[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    printf("Output of p\n");
    for (i = 0 ; i < 2 ; i ++){
        for (j = 0 ; j < 2 ; j ++){
            for (k = 0 ; k < 3 ; k ++){
                printf("%d ", *(p + 6 * i + 3 * j + k));
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}
