#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARY_SIZE 100000

int binSearch(int ary[], int from, int to, int value);

int main(void)
{
    int n, i;
    int ary[MAX_ARY_SIZE] = {0, };
    FILE * fp = NULL;

    fp = fopen("input_sorted.txt", "r");

    fscanf(fp, "%d", &n);

    for(i = 0 ; i < n ; i++){
        fscanf(fp, "%d", &ary[i]);
    }
    fclose(fp);
    printf("%d에 있습니다. \n", binSearch(ary, 0, n - 1, 1424238767));
}

int binSearch(int ary[], int from, int to, int value)
{
    int pivot = from + rand()%(to - from);
    static int count = 0;

    count ++;

    if (from > to) {
        return -1;
    }

    printf("[DEBUG] : %d's function call : from = %d, to =%d \n", count, from, to);

    if (ary[pivot] == value) {
        return pivot;
    }
    else if (ary[pivot] > value) {
        return binSearch(ary, from, pivot - 1, value);
    }
    else {
        return binSearch(ary, pivot + 1, to, value);
    }
}
