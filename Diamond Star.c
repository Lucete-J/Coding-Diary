#include <stdio.h>

int main(void)
{
    int i, j, n, mid;

    printf("Enter the odd number : ");
    scanf("%d", &n);

    mid = (n + 1) / 2;

    for (i = 1 ; i <= n ; i ++) {
        if (i < mid) {
            for (j = 1 ; j <= n ; j ++) {
                if (j <= mid - i || j >= mid + i) printf(" ");
                else  printf("*");
            }
            printf("\n");
        } else if (i == mid) {
            for (j = 1 ; j <= n ; j ++) printf("*");
            printf("\n");
        } else {    
            for (j = 1 ; j <= n ; j ++) {
                if (j <= i - mid || j > n + mid - i) printf(" ");
                else printf("*");
            }
            printf("\n");
        }
    }

    return 0;
}
